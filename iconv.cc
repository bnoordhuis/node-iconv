#include "iconv.h"

#include <v8.h>
#include <node.h>
#include <node_buffer.h>

#include <stdlib.h>
#include <strings.h>  // strcasecmp + strncasecmp
#include <string.h>
#include <errno.h>

#include <string>

using namespace v8;
using namespace node;

namespace {

class Iconv: public ObjectWrap {
public:
  static void Initialize(Handle<Object>& target);
  static Handle<Value> New(const Arguments& args);
  static Handle<Value> Convert(const Arguments& args);
  static Handle<Value> Convert2(const Arguments& args);

  Iconv(iconv_t conv);
  ~Iconv(); // destructor may not run if program is short-lived or aborted

  // the actual conversion happens here
  Handle<Value> Convert(char* data, size_t length);
  Handle<Value> Convert2(char* data, size_t length);

private:
  iconv_t conv_;
};

Iconv::Iconv(iconv_t conv): conv_(conv) {
  assert(conv_ != (iconv_t) -1);
}

Iconv::~Iconv() {
  iconv_close(conv_);
}

int grow(char** output, size_t* outlen, char** outbuf, size_t* outbufsz) {
  size_t newlen;
  char *newptr;

  newlen = *outlen ? (*outlen * 2) : 16;
  if ((newptr = (char*) realloc(*output, newlen))) {
    *outbufsz = newlen - *outlen;
    *outbuf = newptr + (*outbuf - *output);

    *outlen = newlen;
    *output = newptr;

    return 1;
  }

  return 0;
}

/**
 * This function sets `errno` on error. `*output` and `*outlen` will be set to NULL and zero respectively.
 */
bool convert(iconv_t iv, char** input, size_t* inlen, char** output, size_t* outlen, bool free_on_error = true) {
  char* inbuf;
  char* outbuf;
  size_t outbufsz;
  size_t inbufsz;
  size_t status;

  // return value
  bool rv = false;

  inbufsz = *inlen;
  inbuf = *input;

  *outlen = outbufsz = 0;
  *output = outbuf = 0;

  // reset to initial state
  iconv(iv, 0, 0, 0, 0);

  // convert input
  do {
    if (grow(output, outlen, &outbuf, &outbufsz)) {
      status = iconv(iv, &inbuf, &inbufsz, &outbuf, &outbufsz);
    }
    else {
      goto error;
    }
  }
  while (status == (size_t) -1 && errno == E2BIG);

  if (status == (size_t) -1) {
    goto error;
  }

  // write out shift sequence
  status = iconv(iv, 0, 0, &outbuf, &outbufsz);

  if (status == (size_t) -1) {
    if (errno != E2BIG) {
      goto error;
    }
    if (!grow(output, outlen, &outbuf, &outbufsz)) {
      goto error;
    }
    if (iconv(iv, 0, 0, &outbuf, &outbufsz) == (size_t) -1) {
      goto error;
    }
  }

  rv = true;

error:
  if (rv == true || free_on_error == false) {
    // store length
    *outlen = outbuf - *output;

    // release unused trailing memory; this can't conceivably fail
    // because newlen <= oldlen but let's take the safe route anyway
    //
    // realloc() may free the memory and return NULL if *outlen == 0
    // but that's not an error, the caller should (and does) handle it
    // graciously
    //
    if ((outbuf = (char*) realloc(*output, *outlen)) || *outlen == 0) {
      *output = outbuf;
    }
  }
  else {
    // an error happened and the caller wants us to free the memory
    free(*output);
    *output = 0;
    *outlen = 0;
  }

  *input = inbuf;
  *inlen = inbufsz;

  return rv;
}

void FreeMemory(char *data, void *hint) {
  free(data);
  V8::AdjustAmountOfExternalAllocatedMemory(-(sizeof(Buffer) + (size_t) hint));
}

// the actual conversion happens here
Handle<Value> Iconv::Convert(char* input, size_t inlen) {
  size_t outlen = 0;
  char *output = 0;

  if (convert(conv_, &input, &inlen, &output, &outlen, /* free_on_error= */ true)) {
    V8::AdjustAmountOfExternalAllocatedMemory(sizeof(Buffer) + outlen);
    return Buffer::New(output, outlen, FreeMemory, (void *) outlen)->handle_;
  }
  else if (errno == EINVAL) {
    return ThrowException(ErrnoException(EINVAL, "iconv", "Incomplete character sequence."));
  }
  else if (errno == EILSEQ) {
    return ThrowException(ErrnoException(errno, "iconv", "Illegal character sequence."));
  }
  else if (errno == ENOMEM) {
    V8::LowMemoryNotification();
    return ThrowException(ErrnoException(errno, "iconv", "Out of memory."));
  }
  else {
    return ThrowException(ErrnoException(errno, "iconv"));
  }
}

Handle<Value> Iconv::Convert(const Arguments& args) {
  HandleScope scope;

  Iconv* const self = ObjectWrap::Unwrap<Iconv>(args.This());
  Local<Value> arg = args[0];

  if (arg->IsString()) {
    String::Utf8Value string(arg->ToString());
    return self->Convert(*string, string.length());
  }

  if (arg->IsObject()) {
    Local<Object> object = arg->ToObject();
    if (Buffer::HasInstance(object)) {
      //Buffer& buffer = *ObjectWrap::Unwrap<Buffer>(object);
      return self->Convert(Buffer::Data(object), Buffer::Length(object));
    }
  }

  return Undefined();
}

Handle<Value> Iconv::Convert2(char* input, size_t inlen) {
  HandleScope scope;

  size_t outlen = 0;
  char *output = 0;

  Buffer* converted = 0;
  Buffer* unconverted = 0;

  if (convert(conv_, &input, &inlen, &output, &outlen, /* free_on_error= */ false)) {
    V8::AdjustAmountOfExternalAllocatedMemory(sizeof(Buffer) + outlen);
    converted = Buffer::New(output, outlen, FreeMemory, (void *) outlen);
  }
  else if (errno == EINVAL) {
    V8::AdjustAmountOfExternalAllocatedMemory(sizeof(Buffer) + outlen);
    converted = Buffer::New(output, outlen, FreeMemory, (void *) outlen);
    unconverted = Buffer::New(input, inlen); // make a copy
  }
  else if (errno == EILSEQ) {
    return ThrowException(ErrnoException(errno, "iconv", "Illegal character sequence."));
  }
  else if (errno == ENOMEM) {
    V8::LowMemoryNotification();
    return ThrowException(ErrnoException(errno, "iconv", "Out of memory."));
  }
  else {
    return ThrowException(ErrnoException(errno, "iconv"));
  }

  // TODO make zero-length buffer a singleton
  Local<Object> rv = Object::New();
  rv->Set(String::NewSymbol("unconverted"), (unconverted ? unconverted : Buffer::New(0))->handle_);
  rv->Set(String::NewSymbol("converted"), (converted ? converted : Buffer::New(0))->handle_);
  rv->Set(String::NewSymbol("errno"), Integer::New(errno));

  return scope.Close(rv);
}

Handle<Value> Iconv::Convert2(const Arguments& args) {
  HandleScope scope;

  Iconv* const self = ObjectWrap::Unwrap<Iconv>(args.This());
  Local<Value> arg = args[0];

  if (arg->IsString()) {
    String::Utf8Value string(arg->ToString());
    return self->Convert2(*string, string.length());
  }

  if (arg->IsObject()) {
    Local<Object> object = arg->ToObject();
    if (Buffer::HasInstance(object)) {
      return self->Convert2(Buffer::Data(object), Buffer::Length(object));
    }
  }

  return Undefined();
}

// workaround for shortcoming in libiconv: "UTF-8" is recognized but "UTF8" isn't
Handle<String> FixEncodingName(Handle<String> name) {
  String::AsciiValue s(name);

  if (!strncasecmp(*s, "UTF", 3) && (*s)[3] != '-') {
    std::string rv = std::string("UTF-") + (*s + 3);
    return String::New(rv.c_str());
  }

  return name;
}

Handle<Value> Iconv::New(const Arguments& args) {
  HandleScope scope;

  // inconsistency: node-iconv expects (source, target) while native iconv expects (target, source)
  // wontfix for now, node-iconv's approach feels more intuitive
  String::AsciiValue sourceEncoding(FixEncodingName(args[0]->ToString()));
  String::AsciiValue targetEncoding(FixEncodingName(args[1]->ToString()));

  iconv_t conv = iconv_open(*targetEncoding, *sourceEncoding);
  if (conv == (iconv_t) -1) {
    return ThrowException(ErrnoException(errno, "iconv_open", "Conversion not supported."));
  }

  Iconv* instance = new Iconv(conv);
  instance->Wrap(args.Holder());

  return args.This();
}

void Iconv::Initialize(Handle<Object>& target) {
  HandleScope scope;

  Local<FunctionTemplate> t = FunctionTemplate::New(Iconv::New);
  t->InstanceTemplate()->SetInternalFieldCount(1);
  NODE_SET_PROTOTYPE_METHOD(t, "convert", Iconv::Convert);
  NODE_SET_PROTOTYPE_METHOD(t, "convert2", Iconv::Convert2);
  target->Set(String::NewSymbol("Iconv"), t->GetFunction());
}

extern "C" void init(Handle<Object> target) {
  Iconv::Initialize(target);
}

} // namespace
