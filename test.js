var assert = require('assert');

var Buffer = require('buffer').Buffer;
var Iconv = require('./iconv').Iconv;

// unknown source/target encoding
assert.throws(function() { new Iconv('utf-8', 'xxx'); });
assert.throws(function() { new Iconv('xxx', 'utf-8'); });

var iconv = new Iconv('utf-8', 'iso-8859-1');
assert.ok(undefined === iconv.convert());
assert.ok(undefined === iconv.convert(1));
assert.ok(undefined === iconv.convert({}));

assert.ok(iconv.convert('xxx') instanceof Buffer);
assert.ok(iconv.convert(new Buffer('xxx')) instanceof Buffer);

assert.ok(new Buffer('xxx').inspect() == iconv.convert('xxx').inspect());
assert.ok(new Buffer('xxx').inspect() == iconv.convert(new Buffer('xxx')).inspect());

var buffer = new Buffer(1); buffer[0] = 235; // ë
assert.ok(buffer.inspect() == iconv.convert('ë').inspect());

// partial character sequence - throws for now
assert.throws(function() {
	buffer = new Buffer(1); buffer[0] = 195;
	iconv.convert(buffer);
});

// belongs to partial character sequence test - new input should be recoded without issues
buffer = new Buffer(1); buffer[0] = 235; // ë
assert.ok(buffer.inspect() == iconv.convert('ë').inspect());

// input too big to fit in single (internal) buffer
var s = 'x'; for (var i = 0; i < 14; i++) s = s + s; s += '1234'; // 16384 + 4 for good measure
assert.ok(new Buffer(s).inspect() == iconv.convert(s).inspect());
