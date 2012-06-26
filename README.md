# node-iconv

Text recoding in JavaScript for fun and profit!

node-iconv may or may not work on Windows. Please try it and report any issues
you have.

## Installing with [npm](http://npmjs.org/)

    $ npm install iconv

Note that you do not need to have a copy of libiconv installed to use this
module.

## Compiling from source

    $ git clone git://github.com/bnoordhuis/node-iconv.git
    $ node-gyp configure build
    $ npm install .

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

Look at test.js for more examples and node-iconv's behaviour under error
conditions.

## Notes

Things to keep in mind when you work with node-iconv.

### Chunked data

Say you are reading data in chunks from a HTTP stream. The logical input is a
single document (the full POST request data) but the physical input will be
spread over several buffers (the request chunks).

You must accumulate the small buffers into a single large buffer before
performing the conversion. If you don't, you will get unexpected results with
multi-byte and stateful character sets like UTF-8 and ISO-2022-JP.

[node-buffertools](http://github.com/bnoordhuis/node-buffertools) lets you
concatenate buffers painlessly. See the description of `buffertools.concat()`
for details.

### Dealing with untranslatable characters

Characters are not always translatable to another encoding. The UTF-8 string
"ça va が", for example, cannot be represented in plain 7-bits ASCII without
some loss of fidelity.

By default, node-iconv throws EILSEQ when untranslatabe characters are
encountered but this can be customized. Quoting the `iconv_open(3)` man page:

    //TRANSLIT
    When  the  string  "//TRANSLIT"  is appended to tocode, transliteration is
    activated. This means that when a character cannot be represented in the
    target character set, it can be approximated through one or several
    similarly looking characters.

    //IGNORE
    When the string "//IGNORE" is appended to tocode, characters that cannot be
    represented in the target character set will be silently discarded.

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

EINVAL is raised when the input ends in a partial character sequence. This is a
feature, not a bug.
