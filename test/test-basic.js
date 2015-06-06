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

'use strict';

var assert = require('assert');
var Iconv = require('../lib/iconv').Iconv;

// unknown source/target encoding
assert.throws(function() { new Iconv('utf-8', 'xxx'); });
assert.throws(function() { new Iconv('xxx', 'utf-8'); });

// 'utf8' etc. should not throw "EINVAL: Conversion not supported"
new Iconv('utf7',    'utf8');
new Iconv('utf8',    'utf16');
new Iconv('utf16',   'utf32');
new Iconv('utf16le', 'utf16be');
new Iconv('utf32le', 'utf32be');

var iconv = new Iconv('utf-8', 'iso-8859-1');
assert.throws(function() { iconv.convert() });
assert.throws(function() { iconv.convert(1) });
assert.throws(function() { iconv.convert({}) });

assert(iconv.convert(new Buffer('xxx')) instanceof Buffer);
assert(iconv.convert('xxx') instanceof Buffer);

assert.deepEqual(iconv.convert('xxx'), new Buffer('xxx'));
assert.deepEqual(iconv.convert(new Buffer('xxx')), new Buffer('xxx'));

var buffer = new Buffer(1); buffer[0] = 235; // ë
assert.deepEqual(iconv.convert('ë'), buffer);

// partial character sequence should throw EINVAL
buffer = new Buffer(1); buffer[0] = 195;
try {
  iconv.convert(buffer);
} catch (e) {
  assert.equal(e.code, 'EINVAL');
}

// belongs to partial character sequence test - new input should be recoded without issues
buffer = new Buffer(1); buffer[0] = 235; // ë
assert.deepEqual(iconv.convert('ë'), buffer);

// stateful encodings should do the Right Thing
iconv = new Iconv('iso-2022-jp', 'utf-8');
buffer = new Buffer(5);
buffer[0] = 0x1b;  // start escape sequence
buffer[1] = 0x24;
buffer[2] = 0x40;
buffer[3] = 0x24;  // start character sequence
buffer[4] = 0x2c;
assert.deepEqual(iconv.convert(buffer), new Buffer('が'));

buffer = new Buffer(4);
buffer[0] = 0x1b;  // start escape sequence
buffer[1] = 0x24;
buffer[2] = 0x40;
buffer[3] = 0x24;  // start character sequence
//buffer[4] = 0x2c;
try {
  iconv.convert(buffer);
} catch (e) {
  assert.equal(e.code, 'EINVAL');
}

// non-convertible character sequence should throw EILSEQ
iconv = new Iconv('utf-8', 'ascii');
try {
  iconv.convert('ë');
} catch (e) {
  assert.equal(e.code, 'EILSEQ');
}

// prototypical inheritance should work
if (false) {  // XXX disabled for now
  Foo = function() { Foo.prototype.call(this, 'utf-8', 'ascii'); };
  Foo.prototype = Iconv;
  new Foo();
}

// GH-14 ensure that shift sequences are written out
iconv = new Iconv('utf-8', 'utf-7');
assert.equal(iconv.convert('ç').toString(), '+AOc-');
assert.equal(iconv.convert('çç').toString(), '+AOcA5w-');
assert.equal(iconv.convert('çxç').toString(), '+AOc-x+AOc-');

// GH-15 document and support //TRANSLIT and //IGNORE
iconv = new Iconv('utf-8', 'ascii');
assert.throws(function() { iconv.convert('ça va'); }); // untranslatable

iconv = new Iconv('utf-8', 'ascii//ignore');
assert.equal(iconv.convert('ça va').toString(), 'a va');

iconv = new Iconv('utf-8', 'ascii//translit');
assert.equal(iconv.convert('ça va').toString(), 'ca va');

iconv = new Iconv('utf-8', 'ascii//translit');
assert.throws(function() { iconv.convert('ça va が'); }); // untranslatable

iconv = new Iconv('utf-8', 'ascii//translit//ignore');
assert.equal(iconv.convert('ça va が').toString(), 'ca va ');

iconv = Iconv('utf-8', 'iso-8859-1');
assert.equal(iconv.convert('b2s=', 'base64').toString(), 'ok');

var aixEncodings =
    'CP856 CP922 CP943 CP1046 CP1124 CP1129 CP1161 CP1162 CP1163';

var dosEncodings =
    'CP437 CP737 CP775 CP852 CP853 CP855 CP857 CP858 CP860 CP861 ' +
    'CP863 CP864 CP865 CP869 CP1125';

// Check that AIX and DOS encodings are available.
aixEncodings.split(' ').forEach(function(name) { Iconv(name, 'utf-8'); })
dosEncodings.split(' ').forEach(function(name) { Iconv(name, 'utf-8'); })
