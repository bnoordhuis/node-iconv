#include <iconv.h>

#include <v8.h>
#include <node.h>
#include <node_buffer.h>

#include <cstring>
#include <cerrno>

// for stack-based placement new
#include <alloca.h>
#include <new>

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

// helper class: reverse linked list of dumb buffers
struct chunk {
  chunk *const prev;
  size_t size;
  char data[4096];

  chunk(chunk *prev): prev(prev), size(0) {
  }
};

// the actual conversion happens here
Handle<Value> Iconv::Convert(char* data, size_t length) {
  assert(conv_ != (iconv_t) -1);
  assert(data != 0);

  chunk *c = 0;
  char *inbuf = data;
  size_t inbytesleft = length;
  size_t offset = 0;

  while (true) {
    // placement new on stack
    c = new (alloca(sizeof *c)) chunk(c);

    char *outbuf = c->data;
    size_t outbytesleft = sizeof(c->data);

    size_t rv = iconv(conv_, &inbuf, &inbytesleft, &outbuf, &outbytesleft);
    offset += (c->size = sizeof(c->data) - outbytesleft);

    if (rv == (size_t) -1) {
      if (errno == E2BIG) {
        continue;
      }
      if (errno == EINVAL) {
        return ThrowException(ErrnoException(errno, "iconv", "Incomplete character sequence."));
      }
      if (errno == EILSEQ) {
        return ThrowException(ErrnoException(errno, "iconv", "Illegal character sequence."));
      }
      return ThrowException(ErrnoException(errno, "iconv"));
    }

    assert(inbytesleft == 0);
    break;
  }

  // copy linked list of chunks into Buffer in reverse order (last chunk at the top, second-to-last chunk below that, etc)
  Buffer& b = *Buffer::New(offset);
  for (; c != 0; c = c->prev) {
    offset -= c->size;
    memcpy(b.data() + offset, c->data, c->size);
  }

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

  // inconsistency: node-iconv expects (source, target) while native iconv expects (target, source)
  // wontfix for now, node-iconv's approach feels more intuitive
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
