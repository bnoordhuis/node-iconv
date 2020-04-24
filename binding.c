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
#include "node_api.h"

#include <assert.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef E2BIG
#define E2BIG 0
#endif

#ifndef EILSEQ
#define EILSEQ 0
#endif

#ifndef EINVAL
#define EINVAL 0
#endif

#ifndef ICONV_CONST
#define ICONV_CONST
#endif

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(*x))

int
getpointer(napi_env env, napi_value argv[], uint32_t idx, char **out)
{
	uint32_t pos;
	void *p;

	if (napi_get_typedarray_info(env, argv[idx + 0], 0, 0, &p, 0, 0))
		return 1;

	if (napi_get_value_uint32(env, argv[idx + 1], &pos))
		return 1;

	*out = (char *) p + pos;

	return 0;
}

int
offsetat(napi_env env, napi_value array, uint32_t idx, size_t *out)
{
	napi_value jsval;
	uint32_t nval;

	if (napi_get_element(env, array, idx, &jsval))
		return 1;

	if (napi_get_value_uint32(env, jsval, &nval))
		return 1;

	*out = nval;

	return 0;
}

void
finalize(napi_env env, void *data, void *hint)
{
	iconv_t conv;

	conv = data;
	if (conv != (iconv_t) -1)
		iconv_close(conv);
}

napi_value
make(napi_env env, napi_callback_info info)
{
	char from[64];
	char to[64];
	iconv_t conv;
	napi_value argv[2];
	napi_value rval;
	size_t argc;

	if (napi_get_null(env, &rval))
		abort();

	argc = ARRAY_SIZE(argv);
	if (napi_get_cb_info(env, info, &argc, argv, 0, 0))
			return rval;

	if (napi_get_value_string_utf8(env, argv[0], from, sizeof(from), 0))
			return rval;

	if (napi_get_value_string_utf8(env, argv[1], to, sizeof(to), 0))
			return rval;

	conv = iconv_open(to, from);
	if (conv != (iconv_t) -1)
		if (napi_create_external(env, conv, finalize, 0, &rval))
			iconv_close(conv);

	return rval;
}

napi_value
convert(napi_env env, napi_callback_info info)
{
	bool is_flush;
	char *inbuf;
	char *outbuf;
	iconv_t conv;
	int err;
	napi_value argv[7];
	napi_value inout;
	napi_value rval;
	napi_value val;
	size_t argc;
	size_t inlen;
	size_t n;
	size_t outlen;

	if (napi_get_null(env, &rval))
		abort();

	argc = ARRAY_SIZE(argv);
	if (napi_get_cb_info(env, info, &argc, argv, 0, 0))
			return rval;

	if (napi_get_value_bool(env, argv[0], &is_flush))
		return rval;

	if (napi_get_value_external(env, argv[1], &conv))
		return rval;

	inbuf = 0;
	if (!is_flush)
		if (getpointer(env, argv, 2, &inbuf))
			return rval;

	if (getpointer(env, argv, 4, &outbuf))
		return rval;

	inout = argv[6];

	if (offsetat(env, inout, 0, &inlen))
		return rval;

	if (offsetat(env, inout, 1, &outlen))
		return rval;

	n = iconv(conv, (ICONV_CONST char **) &inbuf, &inlen, &outbuf, &outlen);

	err = 0;
	if (n == (size_t) -1)
		err = errno;

	if (napi_create_uint32(env, inlen, &val))
		return rval;

	if (napi_set_element(env, inout, 0, val))
		return rval;

	if (napi_create_uint32(env, outlen, &val))
		return rval;

	if (napi_set_element(env, inout, 1, val))
		return rval;

	if (napi_create_uint32(env, err, &rval))
		return rval;

	return rval;
}

#define EXPORT_METHOD(desc, name)					\
	do								\
	{								\
		*desc = (napi_property_descriptor)			\
		{							\
			.utf8name = #name,				\
			.method = name,					\
		};							\
	}								\
	while (0)

#define EXPORT_VALUE(desc, name)					\
	do								\
	{								\
		napi_value result;					\
									\
		if (napi_create_int32(env, name, &result))		\
			return exports;					\
									\
		*desc = (napi_property_descriptor)			\
		{							\
			.utf8name = #name,				\
			.value = result,				\
		};							\
	}								\
	while (0)

napi_value
init(napi_env env, napi_value exports)
{
	napi_property_descriptor props[5];

	EXPORT_METHOD(&props[0], convert);
	EXPORT_METHOD(&props[1], make);
	EXPORT_VALUE(&props[2], E2BIG);
	EXPORT_VALUE(&props[3], EILSEQ);
	EXPORT_VALUE(&props[4], EINVAL);
	napi_define_properties(env, exports, ARRAY_SIZE(props), props);

	return exports;
}

NAPI_MODULE(iconv, init);
