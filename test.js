assert = require('assert');
constants = require('constants');

Iconv = require('./build/Release/iconv').Iconv;
Buffer = require('buffer').Buffer;
SlowBuffer = require('buffer').SlowBuffer;

// hack to make the tests to pass with node v0.3.0's new buffer model
assert.isBuffer = function(object) {
  assert.ok(object instanceof Buffer || object instanceof SlowBuffer);
};

// hack to make the tests to pass with node v0.3.0's new buffer model
assert.bufferEqual = function(a, b) {
  assert.equal(
    a.inspect().replace(/^<SlowBuffer/, '<Buffer'),
    b.inspect().replace(/^<SlowBuffer/, '<Buffer'));
};

// unknown source/target encoding
assert.throws(function() { new Iconv('utf-8', 'xxx'); });
assert.throws(function() { new Iconv('xxx', 'utf-8'); });

// 'utf8' etc. should not throw "EINVAL: Conversion not supported"
new Iconv('utf7',    'utf8');
new Iconv('utf8',    'utf16');
new Iconv('utf16',   'utf32');
new Iconv('utf16le', 'utf16be');
new Iconv('utf32le', 'utf32be');

iconv = new Iconv('utf-8', 'iso-8859-1');
assert.equal(iconv.convert(), undefined);
assert.equal(iconv.convert(1), undefined);
assert.equal(iconv.convert({}), undefined);

assert.isBuffer(iconv.convert(new Buffer('xxx')));
assert.isBuffer(iconv.convert('xxx'));

assert.bufferEqual(iconv.convert('xxx'), new Buffer('xxx'));
assert.bufferEqual(iconv.convert(new Buffer('xxx')), new Buffer('xxx'));

buffer = new Buffer(1); buffer[0] = 235; // ë
assert.bufferEqual(iconv.convert('ë'), buffer);

// partial character sequence should throw EINVAL
buffer = new Buffer(1); buffer[0] = 195;
try {
  iconv.convert(buffer);
} catch (e) {
  assert.equal(e.errno, constants.EINVAL || 22);
}

// belongs to partial character sequence test - new input should be recoded without issues
buffer = new Buffer(1); buffer[0] = 235; // ë
assert.bufferEqual(iconv.convert('ë'), buffer);

// stateful encodings should do the Right Thing
iconv = new Iconv('iso-2022-jp', 'utf-8');
buffer = new Buffer(5);
buffer[0] = 0x1b;  // start escape sequence
buffer[1] = 0x24;
buffer[2] = 0x40;
buffer[3] = 0x24;  // start character sequence
buffer[4] = 0x2c;
assert.bufferEqual(iconv.convert(buffer), new Buffer('が'));

buffer = new Buffer(4);
buffer[0] = 0x1b;  // start escape sequence
buffer[1] = 0x24;
buffer[2] = 0x40;
buffer[3] = 0x24;  // start character sequence
//buffer[4] = 0x2c;
try {
  iconv.convert(buffer);
} catch (e) {
  assert.equal(e.errno, constants.EINVAL || 22);
}

// input too big to fit in single (internal) buffer
s = 'x'; for (var i = 0; i < 16; i++) s = s + s; s += '1234'; // 64K + 4B for good measure
result = iconv.convert(s);
assert.bufferEqual(new Buffer(s), result);
assert.equal(result.slice(65536, 65536 + 4).toString(), '1234');

// non-convertible character sequence should throw EILSEQ
iconv = new Iconv('utf-8', 'ascii');
try {
  iconv.convert('ë');
} catch (e) {
  assert.equal(e.errno, constants.EILSEQ);
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
