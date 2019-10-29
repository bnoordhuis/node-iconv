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

var stream = require('stream');
var util = require('util');
var Buffer = require('safer-buffer').Buffer;

var bindings;
try {
  bindings = require('../build/Release/iconv.node');
}
catch (e) {
  if (e.code !== 'MODULE_NOT_FOUND') throw e;
  bindings = require('../build/Debug/iconv.node');
}

var E2BIG = bindings.E2BIG | 0;
var EILSEQ = bindings.EILSEQ | 0;
var EINVAL = bindings.EINVAL | 0;

// Marker object.
var FLUSH = {length: 0};

function Iconv(fromEncoding, toEncoding)
{
  if (!(this instanceof Iconv)) {
    return new Iconv(fromEncoding, toEncoding);
  }

  stream.Stream.call(this);
  this.writable = true;

  var conv = bindings.make(fixEncoding(fromEncoding),
                           fixEncoding(toEncoding));
  if (conv === null) {
    throw new Error('Conversion from ' +
                    fromEncoding + ' to ' +
                    toEncoding + ' is not supported.');
  }

  var context_ = { trailer: null };

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
    try {
      var buf = convert(conv, input, context_);
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
      var newbuf = Buffer.alloc(context.trailer.length + input.length);
      context.trailer.copy(newbuf, 0, 0, context.trailer.length);
      input.copy(newbuf, context.trailer.length, 0, input.length);
      context.trailer = null;
      input = newbuf;
    }
  }
  var output = Buffer.alloc(input.length * 2);  // To a first approximation.
  var input_start = 0;
  var output_start = 0;
  var input_size = input.length || 0;
  var output_size = output.length;
  var out = [0,0];
  for (;;) {
    var errno = bindings.convert(conv,
                                 input,
                                 input_start,
                                 input_size,
                                 output,
                                 output_start,
                                 output_size,
                                 out,
                                 input === FLUSH);
    var input_consumed = out[0];
    var output_consumed = out[1];
    input_start += input_consumed;
    input_size -= input_consumed;
    output_start += output_consumed;
    output_size -= output_consumed;
    if (errno) {
      if (errno === E2BIG) {
        output_size += output.length;
        var newbuf = Buffer.alloc(output.length * 2);
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
  var err = new Error(errmsg);
  err.code = code;
  return err;
}
