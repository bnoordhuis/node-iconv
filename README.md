# node-iconv

Text recoding in JavaScript for fun and profit!

## Compiling

To compile and install the module, type:

	make install NODE_PATH=/path/to/nodejs

NODE_PATH will default to `/usr/local` if omitted.

Note that you do not need to have a copy of libiconv installed to use this module.

## Usage

Encode from one character encoding to another:

	// convert from UTF-8 to ISO-8859-1
	var Buffer = require('buffer').Buffer;
	var Iconv  = require('iconv').Iconv;
	var assert = require('assert');
	
	var iconv = new Iconv('UTF-8', 'ISO-8859-1');
	var buffer = iconv.convert('Hello, world!');
	var buffer2 = iconv.convert(new Buffer('Hello, world!'));
	assert.equals(buffer.inspect(), buffer2.inspect());
	// do something useful with the buffers

Look at test.js for more examples and node-iconv's behaviour under error conditions.

## Notes

EINVAL is raised when the input ends in a partial character sequence. This is a feature,
not a bug. 