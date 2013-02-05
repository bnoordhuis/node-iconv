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

var Iconv = require('../lib/iconv').Iconv;
var assert = require('assert');

var iconv = new Iconv('UTF-8', 'UTF-16LE');

var utf8 = new Buffer(20000000);
for (var i = 0; i < utf8.length; i++) {
  utf8[i] = 97 + i % 26; // cycle from 'a' to 'z'.
}
var utf16 = iconv.convert(utf8);

assert.equal(utf16.length, utf8.length * 2);

for (i = 0; i < utf8.length; ++i) {
  assert.equal(utf16[i * 2], utf8[i]);
  assert.equal(utf16[i * 2 + 1], 0);
}
