# node-iconv

Text recoding in JavaScript for fun and profit!

## Supported encodings

    European languages
        ASCII, ISO-8859-{1,2,3,4,5,7,9,10,13,14,15,16},
        KOI8-R, KOI8-U, KOI8-RU,
        CP{437,737,775,850,852,853,855,857,858,860,861,863,865,866,869}
        CP{1125,1250,1251,1252,1253,1254,1257}
        Mac{Roman,CentralEurope,Iceland,Croatian,Romania},
        Mac{Cyrillic,Ukraine,Greek,Turkish},
        Macintosh
    Semitic languages
        ISO-8859-{6,8}, CP{1255,1256}, CP862, CP864, Mac{Hebrew,Arabic}
    Japanese
        EUC-JP, SHIFT_JIS, CP932, ISO-2022-JP, ISO-2022-JP-2, ISO-2022-JP-1
        EUC-JISX0213, Shift_JISX0213, ISO-2022-JP-3
    Chinese
        EUC-CN, HZ, GBK, CP936, GB18030, EUC-TW, BIG5, CP950, BIG5-HKSCS,
        BIG5-HKSCS:2004, BIG5-HKSCS:2001, BIG5-HKSCS:1999, ISO-2022-CN,
        ISO-2022-CN-EXT, BIG5-2003 (experimental)
    Korean
        EUC-KR, CP949, ISO-2022-KR, JOHAB
    Turkmen
        TDS565
    Armenian
        ARMSCII-8
    Georgian
        Georgian-Academy, Georgian-PS
    Tajik
        KOI8-T
    Kazakh
        PT154, RK1048
    Thai
        ISO-8859-11, TIS-620, CP874, MacThai
    Laotian
        MuleLao-1, CP1133
    Vietnamese
        VISCII, TCVN, CP1258
    Platform specifics
        HP-ROMAN8, NEXTSTEP, ATARIST, RISCOS-LATIN1
    Full Unicode
        UTF-8
        UCS-2, UCS-2BE, UCS-2LE
        UCS-4, UCS-4BE, UCS-4LE
        UTF-16, UTF-16BE, UTF-16LE
        UTF-32, UTF-32BE, UTF-32LE
        UTF-7
        C99, JAVA
    Full Unicode, in terms of `uint16_t` or `uint32_t`
        (with machine dependent endianness and alignment)
        UCS-2-INTERNAL, UCS-4-INTERNAL
    Locale dependent, in terms of `char` or `wchar_t`
        (with machine dependent endianness and alignment, and with OS and
        locale dependent semantics)
        char, wchar_t
        The empty encoding name "" is equivalent to "char": it denotes the
        locale dependent character encoding.

If you don't need the full gamut of encodings, consider using [iconv-lite][].
It supports most common encodings and doesn't require a compiler to install.

## Installing with [npm](http://npmjs.org/)

    $ npm install iconv

Note that you do not need to have a copy of libiconv installed to use this
module.

## Compiling from source

    $ git clone git://github.com/bnoordhuis/node-iconv.git
    $ cd node-iconv
    $ npm install

If you have a specific node.js source checkout that you want to build against,
replace the last command with:

    $ npm install --nodedir=/path/to/node

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

A simple ISO-8859-1 to UTF-8 conversion TCP service:

    var net = require('net');
    var Iconv = require('iconv').Iconv;
    var server = net.createServer(function(conn) {
      var iconv = new Iconv('latin1', 'utf-8');
      conn.pipe(iconv).pipe(conn);
    });
    server.listen(8000);
    console.log('Listening on tcp://0.0.0.0:8000/');

Look at test/test-basic.js and test/test-stream.js for more examples
and node-iconv's behaviour under error conditions.

## Notes

Things to keep in mind when you work with node-iconv.

### Chunked data

Say you are reading data in chunks from a HTTP stream. The logical input is a
single document (the full POST request data) but the physical input will be
spread over several buffers (the request chunks).

You must accumulate the small buffers into a single large buffer before
performing the conversion. If you don't, you will get unexpected results with
multi-byte and stateful character sets like UTF-8 and ISO-2022-JP.

The above only applies when you are calling `Iconv#convert()` yourself.
If you use the streaming interface, node-iconv takes care of stitching
partial character sequences together again.

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

[iconv-lite]: https://www.npmjs.org/package/iconv-lite
