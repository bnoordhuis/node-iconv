/*
 * Copyright (c) 2013, Ben Noordhuis <info@bnoordhuis.nl>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "iconv.h"
#include "node.h"
#include "v8.h"

#include <errno.h>
#include <assert.h>
#include <stdint.h>

#include "node_version.h"

#if NODE_MAJOR_VERSION == 0 && NODE_MINOR_VERSION <= 10
# define GetAlignedPointerFromInternalField GetPointerFromInternalField
# define SetAlignedPointerInInternalField SetPointerInInternalField
#endif

namespace
{

using v8::Arguments;
using v8::Array;
using v8::Boolean;
using v8::FunctionTemplate;
using v8::Handle;
using v8::HandleScope;
using v8::Integer;
using v8::Local;
using v8::Null;
using v8::Object;
using v8::ObjectTemplate;
using v8::Persistent;
using v8::String;
using v8::Value;

struct Iconv
{
  static Persistent<ObjectTemplate> object_template;
  iconv_t conv_;

  Iconv(iconv_t conv)
  {
    conv_ = conv;
  }

  ~Iconv()
  {
    iconv_close(conv_);
  }

  static void Initialize(Handle<Object> obj)
  {
    HandleScope scope;
    Local<ObjectTemplate> t = ObjectTemplate::New();
    object_template = Persistent<ObjectTemplate>::New(t);
    object_template->SetInternalFieldCount(1);
    obj->Set(String::New("make"),
             FunctionTemplate::New(Make)->GetFunction());
    obj->Set(String::New("convert"),
             FunctionTemplate::New(Convert)->GetFunction());
#define EXPORT_ERRNO(err) obj->Set(String::New(#err), Integer::New(err))
    EXPORT_ERRNO(EINVAL);
    EXPORT_ERRNO(EILSEQ);
    EXPORT_ERRNO(E2BIG);
#undef EXPORT_ERRNO
  }

  static void WeakCallback(Persistent<Value> val, void* arg)
  {
    delete static_cast<Iconv*>(arg);
    val.Dispose();
    val.Clear();
  }

  static Handle<Value> Make(const Arguments& args)
  {
    HandleScope scope;
    String::AsciiValue from_encoding(args[0]);
    String::AsciiValue to_encoding(args[1]);
    iconv_t conv = iconv_open(*to_encoding, *from_encoding);
    if (conv == reinterpret_cast<iconv_t>(-1)) return Null();
    Iconv* iv = new Iconv(conv);
    Local<Object> t = object_template->NewInstance();
    Persistent<Object> obj = Persistent<Object>::New(t);
    obj->SetAlignedPointerInInternalField(0, iv);
    obj.MakeWeak(iv, WeakCallback);
    obj.MarkIndependent();
    return scope.Close(obj);
  }

  static Handle<Value> Convert(const Arguments& args)
  {
    HandleScope scope;
    Iconv* iv = static_cast<Iconv*>(
        args[0].As<Object>()->GetAlignedPointerFromInternalField(0));
    const char* input_buf = static_cast<const char*>(  // NULL on flush.
        args[1].As<Object>()->GetIndexedPropertiesExternalArrayData());
    size_t input_start = args[2]->Uint32Value();
    size_t input_size = args[3]->Uint32Value();
    char* output_buf = static_cast<char*>(  // Never NULL.
        args[4].As<Object>()->GetIndexedPropertiesExternalArrayData());
    size_t output_start = args[5]->Uint32Value();
    size_t output_size = args[6]->Uint32Value();
    Local<Array> rc = args[7].As<Array>();
    if (input_buf != NULL) input_buf += input_start;
    output_buf += output_start;
    size_t input_consumed = input_size;
    size_t output_consumed = output_size;
    errno = 0;
    size_t nconv = iconv(iv->conv_,
                         &input_buf,
                         &input_size,
                         &output_buf,
                         &output_size);
    int errorno = errno;
    input_consumed -= input_size;
    output_consumed -= output_size;
    rc->Set(0, Integer::NewFromUnsigned(input_consumed));
    rc->Set(1, Integer::NewFromUnsigned(output_consumed));
    return scope.Close(Integer::New(errorno));
  }

  // Forbid implicit copying.
  Iconv(const Iconv&);
  void operator=(const Iconv&);
};

Persistent<ObjectTemplate> Iconv::object_template;

} // namespace

NODE_MODULE(iconv, Iconv::Initialize);
