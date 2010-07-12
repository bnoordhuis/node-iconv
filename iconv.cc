#include <iconv.h>

#include <v8.h>
#include <node.h>
#include <node_buffer.h>

#include <cstring>
#include <cerrno>
#include <cstdio>

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

// the actual conversion happens here
Handle<Value> Iconv::Convert(char* data, size_t length) {
  assert(conv_ != (iconv_t) -1);
  assert(data != 0);

  char *inbuf;
  char *outbuf;
  size_t inbytesleft;
  size_t outbytesleft;

  inbuf = data;
  inbytesleft = length;

  char tmp[4096];
  outbuf = tmp;
  outbytesleft = sizeof(tmp);

  size_t n = iconv(conv_, &inbuf, &inbytesleft, &outbuf, &outbytesleft);
  if (n == (size_t) -1) {
    const char* message = "Unexpected error.";

    switch (errno) {
    case E2BIG:
      message = "Output buffer not large enough. This is a bug.";
      break;
    case EILSEQ:
      message = "Illegal character sequence.";
      break;
    case EINVAL:
      message = "Incomplete character sequence.";
      break;
    }

    return ThrowException(ErrnoException(errno, "iconv", message));
  }

  n = sizeof(tmp) - outbytesleft;
  Buffer& b = *Buffer::New(n);
  memcpy(b.data(), tmp, n);

  return b.handle_;
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
    Handle<Value> object = arg->ToObject();
    if (Buffer::HasInstance(object)) {
      Buffer& buffer = *ObjectWrap::Unwrap<Buffer>(arg->ToObject());
      return self->Convert(buffer.data(), buffer.length());
    }
  }

  return Undefined();
}

Handle<Value> Iconv::New(const Arguments& args) {
  HandleScope scope;

  String::AsciiValue sourceEncoding(args[0]->ToString());
  String::AsciiValue targetEncoding(args[1]->ToString());

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

} // namespace
