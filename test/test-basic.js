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

const assert = require('assert');
const Iconv = require('../').Iconv;

// unknown source/target encoding
assert.throws(function() { new Iconv('utf-8', 'xxx'); });
assert.throws(function() { new Iconv('xxx', 'utf-8'); });

// 'utf8' etc. should not throw "EINVAL: Conversion not supported"
new Iconv('utf7',    'utf8');
new Iconv('utf8',    'utf16');
new Iconv('utf16',   'utf32');
new Iconv('utf16le', 'utf16be');
new Iconv('utf32le', 'utf32be');

// https://github.com/bnoordhuis/node-iconv/issues/152
new Iconv('windows-31J', 'windows-31j');

let iconv = new Iconv('utf-8', 'iso-8859-1');
assert.throws(function() { iconv.convert() });
assert.throws(function() { iconv.convert(1) });
assert.throws(function() { iconv.convert({}) });

assert(Buffer.isBuffer(iconv.convert(Buffer.from('xxx'))));
assert(Buffer.isBuffer(iconv.convert('xxx')));

assert.deepEqual(iconv.convert('xxx'), Buffer.from('xxx'));
assert.deepEqual(iconv.convert(Buffer.from('xxx')), Buffer.from('xxx'));

let buffer = Buffer.alloc(1); buffer[0] = 235; // ë
assert.deepEqual(iconv.convert('ë'), buffer);

// test conversion error messages
const unknown_conv = 'whatchimajig';
try {
  new Iconv('utf-8', unknown_conv);
  assert.fail('unreachable');
} catch (e) {
  assert.equal(e.message,
               'Conversion from utf-8 to ' + unknown_conv +
               ' is not supported.');
}

try {
  new Iconv(unknown_conv, 'utf-8');
  assert.fail('unreachable');
} catch (e) {
  assert.equal(e.message,
               'Conversion from ' + unknown_conv +
               ' to utf-8 is not supported.');
}

// partial character sequence should throw EINVAL
buffer = Buffer.alloc(1); buffer[0] = 195;
try {
  iconv.convert(buffer);
} catch (e) {
  assert.equal(e.code, 'EINVAL');
}

// belongs to partial character sequence test - new input should be recoded without issues
buffer = Buffer.alloc(1); buffer[0] = 235; // ë
assert.deepEqual(iconv.convert('ë'), buffer);

// stateful encodings should do the Right Thing
iconv = new Iconv('iso-2022-jp', 'utf-8');
buffer = Buffer.alloc(5);
buffer[0] = 0x1b;  // start escape sequence
buffer[1] = 0x24;
buffer[2] = 0x40;
buffer[3] = 0x24;  // start character sequence
buffer[4] = 0x2c;
assert.deepEqual(iconv.convert(buffer), Buffer.from('が'));

buffer = Buffer.alloc(4);
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

const aixEncodings =
    'CP856 CP922 CP943 CP1046 CP1124 CP1129 CP1161 CP1162 CP1163';

const dosEncodings =
    'CP437 CP737 CP775 CP852 CP853 CP855 CP857 CP858 CP860 CP861 ' +
    'CP863 CP864 CP865 CP869 CP1125';

// Check that AIX and DOS encodings are available.
aixEncodings.split(' ').forEach(function(name) { Iconv(name, 'utf-8'); })
dosEncodings.split(' ').forEach(function(name) { Iconv(name, 'utf-8'); })

// https://github.com/bnoordhuis/node-iconv/issues/172
new Iconv('5601', 'euc-kr'); new Iconv('euc-kr', '5601');
new Iconv('646', 'ascii'); new Iconv('ascii', '646');
new Iconv('ansi-1251', 'cp1251'); new Iconv('cp1251', 'ansi-1251');
new Iconv('cns11643', 'euc-tw'); new Iconv('euc-tw', 'cns11643');
new Iconv('dechanyu', 'dec-hanyu'); new Iconv('dec-hanyu', 'dechanyu');
new Iconv('dechanzi', 'euc-cn'); new Iconv('euc-cn', 'dechanzi');
new Iconv('deckanji', 'dec-kanji'); new Iconv('dec-kanji', 'deckanji');
new Iconv('deckorean', 'euc-kr'); new Iconv('euc-kr', 'deckorean');
new Iconv('hp15cn', 'euc-cn'); new Iconv('euc-cn', 'hp15cn');
new Iconv('ibm-1046', 'cp1046'); new Iconv('cp1046', 'ibm-1046');
new Iconv('ibm-1124', 'cp1124'); new Iconv('cp1124', 'ibm-1124');
new Iconv('ibm-1129', 'cp1129'); new Iconv('cp1129', 'ibm-1129');
new Iconv('ibm-1131', 'cp1131'); new Iconv('cp1131', 'ibm-1131');
new Iconv('ibm-1252', 'cp1252'); new Iconv('cp1252', 'ibm-1252');
new Iconv('ibm-850', 'cp850'); new Iconv('cp850', 'ibm-850');
new Iconv('ibm-856', 'cp856'); new Iconv('cp856', 'ibm-856');
new Iconv('ibm-921', 'iso8859-13'); new Iconv('iso8859-13', 'ibm-921');
new Iconv('ibm-922', 'cp922'); new Iconv('cp922', 'ibm-922');
new Iconv('ibm-932', 'cp932'); new Iconv('cp932', 'ibm-932');
new Iconv('ibm-943', 'cp943'); new Iconv('cp943', 'ibm-943');
new Iconv('ibm-euccn', 'euc-cn'); new Iconv('euc-cn', 'ibm-euccn');
new Iconv('ibm-eucjp', 'euc-jp'); new Iconv('euc-jp', 'ibm-eucjp');
new Iconv('ibm-euckr', 'euc-kr'); new Iconv('euc-kr', 'ibm-euckr');
new Iconv('ibm-euctw', 'euc-tw'); new Iconv('euc-tw', 'ibm-euctw');
new Iconv('iso88591', 'iso8859-1'); new Iconv('iso8859-1', 'iso88591');
new Iconv('iso885915', 'iso8859-15'); new Iconv('iso8859-15', 'iso885915');
new Iconv('iso88592', 'iso8859-2'); new Iconv('iso8859-2', 'iso88592');
new Iconv('iso88595', 'iso8859-5'); new Iconv('iso8859-5', 'iso88595');
new Iconv('iso88596', 'iso8859-6'); new Iconv('iso8859-6', 'iso88596');
new Iconv('iso88597', 'iso8859-7'); new Iconv('iso8859-7', 'iso88597');
new Iconv('iso88598', 'iso8859-8'); new Iconv('iso8859-8', 'iso88598');
new Iconv('iso88599', 'iso8859-9'); new Iconv('iso8859-9', 'iso88599');
new Iconv('ko_kr.johap92', 'johab'); new Iconv('johab', 'ko_kr.johap92');
new Iconv('ksc5601', 'cp949'); new Iconv('cp949', 'ksc5601');
new Iconv('pck', 'sjis'); new Iconv('sjis', 'pck');
new Iconv('sdeckanji', 'euc-jp'); new Iconv('euc-jp', 'sdeckanji');
new Iconv('tactis', 'tis620'); new Iconv('tis620', 'tactis');
new Iconv('tis620.2533', 'tis620'); new Iconv('tis620', 'tis620.2533');
