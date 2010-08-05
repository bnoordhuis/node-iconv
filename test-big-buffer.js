var Iconv = require('./iconv').Iconv,
   assert = require('assert');

var iconv = new Iconv('UTF-8', 'UTF-16');

var utf8 = new Buffer(20000000);
for (var i = 0; i < utf8.length; i++) {
  utf8[i] = 97 + i % 26; // cycle from 'a' to 'z'.
}
var utf16 = iconv.convert(utf8);

// 2 bytes per character + 2 bytes for BOM
assert.equal(utf16.length, utf8.length * 2 + 2);

// test for BOM
assert.equal(utf16[0], 0xff);
assert.equal(utf16[1], 0xfe);

for (i = 0; i < utf8.length; ++i) {
  assert.equal(utf16[2 + i * 2], utf8[i]);
  assert.equal(utf16[2 + i * 2 + 1], 0);
}

