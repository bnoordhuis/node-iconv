# node-iconv

Text recoding in JavaScript for fun and profit!

## Compiling

Easy as pie:

	node-waf configure build install

Thanks to a bug in the system libiconv, Mac OS X users need to build a libiconv from source. It's not as complicated as it sounds:

	wget http://ftp.gnu.org/pub/gnu/libiconv/libiconv-1.13.1.tar.gz
	tar xzvf libiconv-1.13.1.tar.gz
	cd libiconv-1.13.1
	./configure --prefix=/usr/local
	sudo make install
	cd ..
	node-waf configure build install --libiconv=/usr/local

A workaround to this issue is forthcoming.

## Usage

Encode from one character encoding to another:

	// convert from UTF-8 to ISO-8859-1
	var Buffer = require('buffer').Buffer;
	var Iconv  = require('./iconv').Iconv;
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