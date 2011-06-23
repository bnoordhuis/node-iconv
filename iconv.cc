#include "iconv.h"

#include <v8.h>
#include <node.h>
#include <node_buffer.h>

#include <stdlib.h>
#include <strings.h>  // strcasecmp + strncasecmp
#include <string.h>
#include <errno.h>

#include <string>

#define F_PARTIAL   1   // allow partial conversion

using namespace v8;
using namespace node;

namespace {

Persistent<ObjectTemplate> handleTemplate;
Persistent<String> unconvertedSymbol;
Persistent<String> convertedSymbol;
Persistent<String> errnoSymbol;

struct Iconv: public ObjectWrap {
  Iconv(iconv_t iv, Handle<Object> target): iv_(iv) {
    assert(iv_ != (iconv_t) -1);
    Wrap(target);
  }

  virtual ~Iconv() {
    iconv_close(iv_);
  }

  iconv_t iv_;
};

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

  // we restore errno on success
  const int saved_errno = errno;

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

  // restore errno but not on error, we want the caller to know what went wrong
  if (rv == true) {
    errno = saved_errno;
  }

  return rv;
}

void FreeMemory(char *data, void *hint) {
  free(data);
  V8::AdjustAmountOfExternalAllocatedMemory(-(sizeof(Buffer) + (size_t) hint));
}

Handle<Value> iconv_open_g(const Arguments& args) {
  HandleScope scope;

  iconv_t iv = iconv_open(
      *String::Utf8Value(args[1]),  // targetEncoding
      *String::Utf8Value(args[0])); // sourceEncoding

  if (iv == (iconv_t) -1) {
    assert(errno == EINVAL);
    return ThrowException(ErrnoException(errno, "iconv_open", "Conversion not supported."));
  }
  else {
    Iconv* w = new Iconv(iv, handleTemplate->NewInstance());
    return scope.Close(w->handle_);
  }
}

Handle<Value> convert(iconv_t iv, char* input, size_t inlen, int flags) {
  HandleScope scope;

  size_t outlen = 0;
  char *output = 0;

  Buffer* converted = 0;
  Buffer* unconverted = 0;

  const bool free_on_error = !(flags & F_PARTIAL);

  errno = 0;

  if (convert(iv, &input, &inlen, &output, &outlen, free_on_error)) {
    V8::AdjustAmountOfExternalAllocatedMemory(sizeof(Buffer) + outlen);
    converted = Buffer::New(output, outlen, FreeMemory, (void *) outlen);
  }
  else if (errno == EINVAL) {
    V8::AdjustAmountOfExternalAllocatedMemory(sizeof(Buffer) + outlen);
    converted = Buffer::New(output, outlen, FreeMemory, (void *) outlen);
    unconverted = Buffer::New(input, inlen); // make a copy
  }
  else if (errno == ENOMEM) {
    V8::LowMemoryNotification();
  }

  // stuff the result into a JS object
  Local<Object> rv = Object::New();
  rv->Set(errnoSymbol, Integer::New(errno));
  if (converted) rv->Set(convertedSymbol, converted->handle_);
  if (unconverted) rv->Set(unconvertedSymbol, unconverted->handle_);

  return scope.Close(rv);
}

Handle<Value> convert_g(const Arguments& args) {
  HandleScope scope;

  Iconv* w = Iconv::Unwrap<Iconv>(args[0]->ToObject());
  Local<Value> data = args[1];
  const int flags = args[2]->Int32Value();

  assert(data->IsString() || Buffer::HasInstance(data));

  if (args[1]->IsString()) {
    String::Utf8Value string(args[1]->ToString());
    return convert(w->iv_, *string, string.length(), flags);
  }
  else {
    Local<Object> o = args[1]->ToObject();
    return convert(w->iv_, Buffer::Data(o), Buffer::Length(o), flags);
  }
}

Handle<Value> NewErrnoException(const Arguments& args) {
  return HandleScope().Close(ErrnoException(
    args[0]->Int32Value(), // errno
    args[1]->IsString() ? *String::Utf8Value(args[1]) : 0,      // syscall
    args[2]->IsString() ? *String::Utf8Value(args[2]) : ""));   // message
}

void RegisterModule(Handle<Object> target) {
  HandleScope scope;

  handleTemplate = Persistent<ObjectTemplate>::New(ObjectTemplate::New());
  handleTemplate->SetInternalFieldCount(1);

  unconvertedSymbol = Persistent<String>::New(String::NewSymbol("unconverted"));
  convertedSymbol = Persistent<String>::New(String::NewSymbol("converted"));
  errnoSymbol = Persistent<String>::New(String::NewSymbol("errno"));

  target->Set(String::NewSymbol("errnoException"), FunctionTemplate::New(NewErrnoException)->GetFunction());
  target->Set(String::NewSymbol("iconv_open"), FunctionTemplate::New(iconv_open_g)->GetFunction());
  target->Set(String::NewSymbol("convert"), FunctionTemplate::New(convert_g)->GetFunction());
  target->Set(String::NewSymbol("PARTIAL"), Integer::NewFromUnsigned(F_PARTIAL));
}

} // anonymous namespace

NODE_MODULE(iconv, RegisterModule);
