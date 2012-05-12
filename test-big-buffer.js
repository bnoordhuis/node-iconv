var Iconv = require('./build/Release/iconv').Iconv,
   assert = require('assert');

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

