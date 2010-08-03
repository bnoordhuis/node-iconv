assert = require('assert'), Buffer = require('buffer').Buffer, Iconv = require('./iconv').Iconv;

// unknown source/target encoding
assert.throws(function() { new Iconv('utf-8', 'xxx'); });
assert.throws(function() { new Iconv('xxx', 'utf-8'); });

iconv = new Iconv('utf-8', 'iso-8859-1');
assert.equal(iconv.convert(), undefined);
assert.equal(iconv.convert(1), undefined);
assert.equal(iconv.convert({}), undefined);

assert.ok(iconv.convert('xxx') instanceof Buffer);
assert.ok(iconv.convert(new Buffer('xxx')) instanceof Buffer);

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

// input too big to fit in single (internal) buffer
s = 'x'; for (var i = 0; i < 14; i++) s = s + s; s += '1234'; // 16384 + 4 for good measure
assert.ok(new Buffer(s).inspect() == iconv.convert(s).inspect());

// non-convertible character sequence should throw EILSEQ
iconv = new Iconv('utf-8', 'ascii');
try {
	iconv.convert('ë');
} catch (e) {
	assert.equal(e.errno, process.EILSEQ);
}
