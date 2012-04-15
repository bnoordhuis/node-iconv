# node-iconv

Text recoding in JavaScript for fun and profit!  
Powerd by [GNU libiconv-1.9.1](http://ftp.gnu.org/gnu/libiconv/libiconv-1.9.1.tar.gz)  
The [libiconv-1.9.1-ja-patch-1.diff.gz](http://www2d.biglobe.ne.jp/~msyk/software/libiconv-1.9.1-patch.html) was applied.  
It will solve the problem to Japanese.  

---
in Japanese:  
nodeでiconvを利用するためのライブラリです。  
GNU libiconv-1.9.1をベースに[libiconv-1.9.1-ja-patch-1.diff.gz](http://www2d.biglobe.ne.jp/~msyk/software/libiconv-1.9.1-patch.html)を適用したものを利用しています。  
これにより、libiconvで起こる様々な日本語に対する問題を回避することができます。


## Installing with [npm](http://npmjs.org/)

	npm install iconv-jp

Note that the npm-ified version of node-iconv only
works with node.js >= v0.3.0.

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

Things to keep in mind when you work with node-iconv.

### Chunked data

Say you are reading data in chunks from a HTTP stream. The logical input is a single document (the full POST request data) but the physical input will be spread over several buffers (the request chunks).

You must accumulate the small buffers into a single large buffer before performing the conversion. If you don't, you will get unexpected results with multi-byte and stateful character sets like UTF-8 and ISO-2022-JP.

[node-buffertools](http://github.com/bnoordhuis/node-buffertools) lets you concatenate buffers painlessly. See the description of `buffertools.concat()` for details.

### Dealing with untranslatable characters

Characters are not always translatable to another encoding. The UTF-8 string
"ça va が", for example, cannot be represented in plain 7-bits ASCII without
some loss of fidelity.

By default, node-iconv throws EILSEQ when untranslatabe characters are encountered
but this can be customized. Quoting the `iconv_open(3)` man page:

	//TRANSLIT
		When  the  string  "//TRANSLIT"  is appended to tocode, transliteration is activated.
		This means that when a character cannot be represented in the target character set,
		it can be approximated through one or several similarly looking characters.

	//IGNORE
		When the string "//IGNORE" is appended to tocode, characters that cannot be represented
		in the target character set will be silently discarded.

Example usage:

	var iconv = new Iconv('UTF-8', 'ASCII');
	iconv.convert('ça va'); // throws EILSEQ

	var iconv = new Iconv('UTF-8', 'ASCII//IGNORE');
	iconv.convert('ça va'); // returns "a va"

	var iconv = new Iconv('UTF-8', 'ASCII//TRANSLIT');
	iconv.convert('ça va'); // "ca va"

	var iconv = new Iconv('UTF-8', 'ASCII//TRANSLIT//IGNORE');
	iconv.convert('ça va が'); // "ca va "

### EINVAL

EINVAL is raised when the input ends in a partial character sequence. This is a feature,
not a bug.
