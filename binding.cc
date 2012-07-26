#include "iconv.h"
#include "config.h" // for ICONV_CONST

#include <v8.h>
#include <node.h>
#include <node_buffer.h>

#include <stdlib.h>
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

  Iconv(iconv_t conv);
  ~Iconv(); // destructor may not run if program is short-lived or aborted

  // the actual conversion happens here
  Handle<Value> Convert(char* data, size_t length);

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
 * This function will clobber `output` and `outlen` on both success and error.
 */
int convert(iconv_t iv, char* input, size_t inlen, char** output, size_t* outlen) {
  char* inbuf;
  char* outbuf;
  size_t outbufsz;
  size_t inbufsz;
  size_t rv;

  inbufsz = inlen;
  inbuf = input;

  *outlen = outbufsz = 0;
  *output = outbuf = 0;

  // reset to initial state
  iconv(iv, 0, 0, 0, 0);

  // convert input
  do {
    if (grow(output, outlen, &outbuf, &outbufsz)) {
      rv = iconv(iv, (ICONV_CONST char **) &inbuf, &inbufsz, &outbuf, &outbufsz);
    }
    else {
      goto error;
    }
  }
  while (rv == (size_t) -1 && errno == E2BIG);

  if (rv == (size_t) -1) {
    goto error;
  }

  // write out shift sequence
  rv = iconv(iv, 0, 0, &outbuf, &outbufsz);

  if (rv == (size_t) -1) {
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

  return 1;

error:
  free(*output);
  *output = 0;
  *outlen = 0;
  return 0;
}

void FreeMemory(char *data, void *hint) {
  free(data);
  V8::AdjustAmountOfExternalAllocatedMemory(-(sizeof(Buffer) + (size_t) hint));
}

// the actual conversion happens here
Handle<Value> Iconv::Convert(char* input, size_t inlen) {
  size_t outlen;
  char *output;

  outlen = 0;
  output = 0;

  if (convert(conv_, input, inlen, &output, &outlen)) {
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

  Iconv* self = ObjectWrap::Unwrap<Iconv>(args.This());
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

// workaround for shortcoming in libiconv: "UTF-8" is recognized but "UTF8" isn't
Handle<String> FixEncodingName(Handle<String> name) {
  String::AsciiValue str(name);
  const char* s = *str;

  if ((s[0] == 'U' || s[0] == 'u') &&
      (s[1] == 'T' || s[1] == 't') &&
      (s[2] == 'F' || s[2] == 'f') &&
      (s[3] != '-'))
  {
    std::string rv = std::string("UTF-") + &s[3];
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

  target->Set(String::NewSymbol("Iconv"), t->GetFunction());
}

extern "C" void init(Handle<Object> target) {
  Iconv::Initialize(target);
}
NODE_MODULE(iconv, init);
} // namespace
