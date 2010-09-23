assert = require('assert'), Buffer = require('buffer').Buffer, SlowBuffer = require('buffer').SlowBuffer, Iconv = require('iconv').Iconv;

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

assert.ok(iconv.convert(new Buffer('xxx')) instanceof Buffer);
assert.ok(iconv.convert('xxx') instanceof Buffer);

assert.equal(iconv.convert('xxx').inspect(), new Buffer('xxx').inspect());
assert.equal(iconv.convert(new Buffer('xxx')).inspect(), new Buffer('xxx').inspect());

buffer = new Buffer(1); buffer[0] = 235; // ë
assert.equal(iconv.convert('ë').inspect(), buffer.inspect());

// partial character sequence should throw EINVAL
buffer = new Buffer(1); buffer[0] = 195;
try {
	iconv.convert(buffer);
} catch (e) {
	assert.equal(e.errno, process.EINVAL);
}

// belongs to partial character sequence test - new input should be recoded without issues
buffer = new Buffer(1); buffer[0] = 235; // ë
assert.equal(iconv.convert('ë').inspect(), buffer.inspect());

// stateful encodings should do the Right Thing
iconv = new Iconv('iso-2022-jp', 'utf-8');
buffer = new Buffer(5);
buffer[0] = 0x1b;  // start escape sequence
buffer[1] = 0x24;
buffer[2] = 0x40;
buffer[3] = 0x24;  // start character sequence
buffer[4] = 0x2c;
assert.equal(iconv.convert(buffer).inspect(), new Buffer('が').inspect());

buffer = new Buffer(4);
buffer[0] = 0x1b;  // start escape sequence
buffer[1] = 0x24;
buffer[2] = 0x40;
buffer[3] = 0x24;  // start character sequence
//buffer[4] = 0x2c;
try {
	iconv.convert(buffer);
} catch (e) {
	assert.equal(e.errno, process.EINVAL);
}

// input too big to fit in single (internal) buffer
s = 'x'; for (var i = 0; i < 16; i++) s = s + s; s += '1234'; // 64K + 4B for good measure
assert.ok(new Buffer(s).inspect() == iconv.convert(s).inspect());

// non-convertible character sequence should throw EILSEQ
iconv = new Iconv('utf-8', 'ascii');
try {
	iconv.convert('ë');
} catch (e) {
	assert.equal(e.errno, process.EILSEQ);
}

// prototypical inheritance should work
if (false) {	// XXX disabled for now
	Foo = function() { Foo.prototype.call(this, 'utf-8', 'ascii'); };
	Foo.prototype = Iconv;
	new Foo();
}
