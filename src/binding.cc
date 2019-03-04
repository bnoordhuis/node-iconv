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
#include "napi.h"

#include <errno.h>
#include <assert.h>
#include <stdint.h>

#ifndef ICONV_CONST
#define ICONV_CONST
#endif  // ICONV_CONST

struct Iconv: Napi::ObjectWrap<Iconv>
{
  static Napi::FunctionReference object_template; // iconv_constructor

  Iconv(const Napi::CallbackInfo& info): 
    Napi::ObjectWrap<Iconv>(info) {
      conv_ = info[0].As<Napi::External<iconv_t>>().Data();
    }
  iconv_t conv_;

  ~Iconv()
  {
    iconv_close(conv_);
  }

  static void Init(Napi::Env env) {
    Napi::Function func = DefineClass(env, "Iconv", {});
    Iconv::object_template = Napi::Persistent(func);
    Iconv::object_template.SuppressDestruct();
  }

  static Napi::Object Initialize(Napi::Env env, Napi::Object exports)
  {
    Iconv::Init(env);
    exports.Set(Napi::String::New(env, "make"), 
                Napi::Function::New(env, Make));
    exports.Set(Napi::String::New(env, "convert"),
                Napi::Function::New(env, Convert));
#define EXPORT_ERRNO(err) \
    exports.Set(Napi::String::New(env, #err), Napi::Number::New(env, err))
    EXPORT_ERRNO(EINVAL);
    EXPORT_ERRNO(EILSEQ);
    EXPORT_ERRNO(E2BIG);
#undef EXPORT_ERRNO
    return exports;
  }

  static Napi::Value Make(const Napi::CallbackInfo& info)
  {
    std::string from_encoding = info[0].As<Napi::String>();
    std::string to_encoding = info[1].As<Napi::String>();
    iconv_t conv = iconv_open(to_encoding.c_str(), from_encoding.c_str());
    if (conv == reinterpret_cast<iconv_t>(-1)) {
      return info.Env().Null();
    }
    Napi::Value param = Napi::External<void>::New(info.Env(), conv);
    return Iconv::object_template.New({param});
  }

  static Napi::Value Convert(const Napi::CallbackInfo& info)
  {
    Napi::Env env = info.Env();
    Iconv* iv = Iconv::Unwrap(info[0].As<Napi::Object>());

    const bool is_flush = info[8].As<Napi::Boolean>().Value();
    ICONV_CONST char* input_buf =
        is_flush ? NULL : info[1].As<Napi::Buffer<ICONV_CONST char>>().Data();
    size_t input_start = info[2].IsNumber() ? info[2].As<Napi::Number>().Uint32Value() : static_cast<uint32_t>(0);
    size_t input_size = info[3].IsNumber() ? info[3].As<Napi::Number>().Uint32Value() : static_cast<uint32_t>(0);
    char* output_buf = info[4].As<Napi::Buffer<char>>().Data();
    size_t output_start = info[5].IsNumber() ? info[5].As<Napi::Number>().Uint32Value() : static_cast<uint32_t>(0);
    size_t output_size = info[6].IsNumber() ? info[6].As<Napi::Number>().Uint32Value() : static_cast<uint32_t>(0);
    Napi::Array rc = info[7].As<Napi::Array>();
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
    rc.Set(static_cast<uint32_t>(0), Napi::Number::New(env, static_cast<uint32_t>(input_consumed)));
    rc.Set(static_cast<uint32_t>(1), Napi::Number::New(env, static_cast<uint32_t>(output_consumed)));
    return Napi::Number::New(env, errorno);
  }

  // Forbid implicit copying.
  Iconv(const Iconv&);
  void operator=(const Iconv&);
};

Napi::FunctionReference Iconv::object_template; // iconv_constructor

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  return Iconv::Initialize(env, exports);
}

NODE_API_MODULE(iconv, InitAll)
