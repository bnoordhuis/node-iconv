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
#include "nan.h"
#include "node_buffer.h"

#include <errno.h>
#include <assert.h>
#include <stdint.h>

#ifndef ICONV_CONST
#define ICONV_CONST
#endif  // ICONV_CONST

namespace
{

using v8::Array;
using v8::Integer;
using v8::Local;
using v8::Object;
using v8::ObjectTemplate;
using v8::String;


struct Iconv
{
  static Nan::Persistent<ObjectTemplate> object_template;
  iconv_t conv_;

  Iconv(iconv_t conv)
  {
    conv_ = conv;
  }

  ~Iconv()
  {
    iconv_close(conv_);
  }

  static void WeakCallback(const Nan::WeakCallbackInfo<Iconv>& data)
  {
    delete data.GetParameter();
  }

  static void Initialize(Local<Object> obj)
  {
    Local<ObjectTemplate> t = Nan::New<ObjectTemplate>();
    t->SetInternalFieldCount(1);
    object_template.Reset(t);
    Nan::SetMethod(obj, "make", Make);
    Nan::SetMethod(obj, "convert", Convert);
#define EXPORT_ERRNO(err)                                                     \
    Nan::Set(obj,                                                             \
             Nan::New<String>(#err).ToLocalChecked(),                         \
             Nan::New<Integer>(err))
    EXPORT_ERRNO(EINVAL);
    EXPORT_ERRNO(EILSEQ);
    EXPORT_ERRNO(E2BIG);
#undef EXPORT_ERRNO
  }

  static NAN_METHOD(Make)
  {
    Nan::Utf8String from_encoding(info[0]);
    Nan::Utf8String to_encoding(info[1]);
    iconv_t conv = iconv_open(*to_encoding, *from_encoding);
    if (conv == reinterpret_cast<iconv_t>(-1)) {
      return info.GetReturnValue().SetNull();
    }
    Iconv* iv = new Iconv(conv);
    Local<Object> obj =
        Nan::NewInstance(Nan::New<ObjectTemplate>(object_template))
        .ToLocalChecked();
    Nan::SetInternalFieldPointer(obj, 0, iv);
    Nan::Persistent<Object> persistent(obj);
    persistent.SetWeak(iv, WeakCallback, Nan::WeakCallbackType::kParameter);
    info.GetReturnValue().Set(obj);
  }

  static NAN_METHOD(Convert)
  {
    Iconv* iv = static_cast<Iconv*>(
        Nan::GetInternalFieldPointer(info[0].As<Object>(), 0));
    const bool is_flush = Nan::To<bool>(info[8]).FromJust();
    ICONV_CONST char* input_buf =
        is_flush ? NULL : node::Buffer::Data(info[1].As<Object>());
    size_t input_start = Nan::To<uint32_t>(info[2]).FromJust();
    size_t input_size = Nan::To<uint32_t>(info[3]).FromJust();
    char* output_buf = node::Buffer::Data(info[4].As<Object>());
    size_t output_start = Nan::To<uint32_t>(info[5]).FromJust();
    size_t output_size = Nan::To<uint32_t>(info[6]).FromJust();
    Local<Array> rc = info[7].As<Array>();
    if (input_buf != NULL) input_buf += input_start;
    output_buf += output_start;
    size_t input_consumed = input_size;
    size_t output_consumed = output_size;
    size_t nconv = iconv(iv->conv_,
                         &input_buf,
                         &input_size,
                         &output_buf,
                         &output_size);
    int errorno = 0;
    if (nconv == static_cast<size_t>(-1)) {
      errorno = errno;
    }
    input_consumed -= input_size;
    output_consumed -= output_size;
    Nan::Set(rc, 0, Nan::New<Integer>(static_cast<uint32_t>(input_consumed)));
    Nan::Set(rc, 1, Nan::New<Integer>(static_cast<uint32_t>(output_consumed)));
    info.GetReturnValue().Set(errorno);
  }

  // Forbid implicit copying.
  Iconv(const Iconv&);
  void operator=(const Iconv&);
};

Nan::Persistent<ObjectTemplate> Iconv::object_template;

} // namespace

NODE_MODULE(iconv, Iconv::Initialize);
