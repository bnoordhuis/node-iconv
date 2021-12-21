/*
 * Copyright (c) 2013, Ben Noordhuis <info@bnoordhuis.nl>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

'use strict';

exports.Iconv = Iconv;

const stream = require('stream');
const util = require('util');

let bindings;
try {
  bindings = require('./build/Release/iconv.node');
}
catch (e) {
  if (e.code !== 'MODULE_NOT_FOUND') throw e;
  bindings = require('./build/Debug/iconv.node');
}

const E2BIG = bindings.E2BIG | 0;
const EILSEQ = bindings.EILSEQ | 0;
const EINVAL = bindings.EINVAL | 0;

// Marker object.
const FLUSH = Buffer.alloc(0);

function Iconv(fromEncoding, toEncoding)
{
  if (!(this instanceof Iconv)) {
    return new Iconv(fromEncoding, toEncoding);
  }

  stream.Stream.call(this);
  this.writable = true;

  const conv = bindings.make(fixEncoding(fromEncoding),
                             fixEncoding(toEncoding));
  if (conv === null) {
    throw new Error('Conversion from ' +
                    fromEncoding + ' to ' +
                    toEncoding + ' is not supported.');
  }

  const context_ = { trailer: null };

  this.convert = function(input, encoding) {
    if (typeof(input) === 'string') {
      input = Buffer.from(input, encoding || 'utf8');
    }
    return convert(conv, input, null);
  };

  this.write = function(input, encoding) {
    if (typeof(input) === 'string') {
      input = Buffer.from(input, encoding || 'utf8');
    }
    let buf;
    try {
      buf = convert(conv, input, context_);
    }
    catch (e) {
      this.emit('error', e);
      return false;
    }
    if (buf && buf.length !== 0) {
      this.emit('data', buf);
    }
    return true;
  };

  this.end = function(input, encoding) {
    if (typeof(input) !== 'undefined') {
      this.write(input, encoding);
    }
    this.write(FLUSH);
    this.emit('end');
  };
}
util.inherits(Iconv, stream.Stream);

function fixEncoding(encoding)
{
  if (/^windows-31j$/i.test(encoding)) return 'cp932';

  // Obsolete (but not yet extinct) aliases.
  if ('5601' === encoding) return 'euc-kr';
  if ('646' === encoding) return 'ascii';
  if (/^ansi-1251$/i.test(encoding)) return 'cp1251';
  if (/^cns11643$/i.test(encoding)) return 'euc-tw';
  if (/^dechanyu$/i.test(encoding)) return 'dec-hanyu';
  if (/^dechanzi$/i.test(encoding)) return 'euc-cn';
  if (/^deckanji$/i.test(encoding)) return 'dec-kanji';
  if (/^deckorean$/i.test(encoding)) return 'euc-kr';
  if (/^hp15cn$/i.test(encoding)) return 'euc-cn';
  if (/^ibm-1046$/i.test(encoding)) return 'cp1046';
  if (/^ibm-1124$/i.test(encoding)) return 'cp1124';
  if (/^ibm-1129$/i.test(encoding)) return 'cp1129';
  if (/^ibm-1131$/i.test(encoding)) return 'cp1131';
  if (/^ibm-1252$/i.test(encoding)) return 'cp1252';
  if (/^ibm-850$/i.test(encoding)) return 'cp850';
  if (/^ibm-856$/i.test(encoding)) return 'cp856';
  if (/^ibm-921$/i.test(encoding)) return 'iso8859-13';
  if (/^ibm-922$/i.test(encoding)) return 'cp922';
  if (/^ibm-932$/i.test(encoding)) return 'cp932';
  if (/^ibm-943$/i.test(encoding)) return 'cp943';
  if (/^ibm-euccn$/i.test(encoding)) return 'euc-cn';
  if (/^ibm-eucjp$/i.test(encoding)) return 'euc-jp';
  if (/^ibm-euckr$/i.test(encoding)) return 'euc-kr';
  if (/^ibm-euctw$/i.test(encoding)) return 'euc-tw';
  if (/^iso88591$/i.test(encoding)) return 'iso8859-1';
  if (/^iso885915$/i.test(encoding)) return 'iso8859-15';
  if (/^iso88592$/i.test(encoding)) return 'iso8859-2';
  if (/^iso88595$/i.test(encoding)) return 'iso8859-5';
  if (/^iso88596$/i.test(encoding)) return 'iso8859-6';
  if (/^iso88597$/i.test(encoding)) return 'iso8859-7';
  if (/^iso88598$/i.test(encoding)) return 'iso8859-8';
  if (/^iso88599$/i.test(encoding)) return 'iso8859-9';
  if (/^ko_kr[.]johap92$/i.test(encoding)) return 'johab';
  if (/^ksc5601$/i.test(encoding)) return 'cp949';
  if (/^pck$/i.test(encoding)) return 'sjis';
  if (/^sdeckanji$/i.test(encoding)) return 'euc-jp';
  if (/^tactis$/i.test(encoding)) return 'tis620';
  if (/^tis620[.]2533$/i.test(encoding)) return 'tis620';

  // Convert "utf8" to "utf-8".
  return /^utf[^-]/i.test(encoding) ? 'utf-' + encoding.substr(3) : encoding;
}

function convert(conv, input, context) {
  if (!Buffer.isBuffer(input) && input !== FLUSH) {
    throw new Error('Bad argument.');  // Not a buffer or a string.
  }
  if (context !== null && context.trailer !== null && input === FLUSH) {
    throw errnoException('EINVAL', 'Incomplete character sequence.');
  }
  if (context !== null && context.trailer !== null) {
    if (input.length === 0) {
      // Use the trailer directly when the input is empty,
      // don't allocate a new buffer.
      input = context.trailer;
      context.trailer = null;
    } else {
      // Prepend input buffer with trailer from last chunk.
      const newbuf = Buffer.alloc(context.trailer.length + input.length);
      context.trailer.copy(newbuf, 0, 0, context.trailer.length);
      input.copy(newbuf, context.trailer.length, 0, input.length);
      context.trailer = null;
      input = newbuf;
    }
  }
  let output = Buffer.alloc(input.length * 2);  // To a first approximation.
  let input_start = 0;
  let output_start = 0;
  let input_size = input.length;
  let output_size = output.length;
  const inout = [0,0];
  for (;;) {
    inout[0] = input_size;
    inout[1] = output_size;
    const errno = bindings.convert(input === FLUSH,
                                 conv,
                                 input,
                                 input_start,
                                 output,
                                 output_start,
                                 inout);
    const input_consumed = input_size - inout[0];
    const output_consumed = output_size - inout[1];
    input_start += input_consumed;
    input_size -= input_consumed;
    output_start += output_consumed;
    output_size -= output_consumed;
    if (errno) {
      if (errno === E2BIG) {
        output_size += output.length;
        const newbuf = Buffer.alloc(output.length * 2);
        output.copy(newbuf, 0, 0, output_start);
        output = newbuf;
        continue;
      }
      else if (errno === EILSEQ) {
        throw errnoException('EILSEQ', 'Illegal character sequence.');
      }
      else if (errno === EINVAL) {
        if (context === null || input === FLUSH) {
          throw errnoException('EINVAL', 'Incomplete character sequence.');
        }
        else {
          context.trailer = input.slice(input_start);
          return output.slice(0, output_start);
        }
      }
      else {
        throw 'unexpected error';
      }
    }
    if (input !== FLUSH) {
      input = FLUSH;
      continue;
    }
    if (output_start < output.length) {
      output = output.slice(0, output_start);
    }
    return output;
  }
}

function errnoException(code, errmsg)
{
  const err = new Error(errmsg);
  err.code = code;
  return err;
}
