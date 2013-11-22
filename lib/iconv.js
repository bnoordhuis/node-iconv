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

exports.Iconv = Iconv;

var stream = require('stream');
var util = require('util');

var bindings;
try {
  bindings = require('../build/Release/iconv.node');
}
catch (e) {
  bindings = require('../build/Debug/iconv.node');
}

var E2BIG = bindings.E2BIG | 0;
var EILSEQ = bindings.EILSEQ | 0;
var EINVAL = bindings.EINVAL | 0;

// Marker object.
var FLUSH = {};

function Iconv(fromEncoding, toEncoding)
{
  if (!(this instanceof Iconv)) {
    return new Iconv(fromEncoding, toEncoding);
  }

  stream.Stream.call(this);
  this.writable = true;

  var conv = bindings.make(fixEncoding(fromEncoding),
                           fixEncoding(toEncoding));
  if (conv === null) throw new Error('Conversion not supported.');

  var convert_ = convert.bind({ conv_: conv });
  var context_ = { trailer: null };

  this.convert = function(input, encoding) {
    if (typeof(input) === 'string') {
      input = new Buffer(input, encoding || 'utf8');
    }
    return convert_(input, null);
  };

  this.write = function(input, encoding) {
    if (typeof(input) === 'string') {
      input = new Buffer(input, encoding || 'utf8');
    }
    try {
      var buf = convert_(input, context_);
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
  // Convert "utf8" to "utf-8".
  return /^utf[^-]/i.test(encoding) ? 'utf-' + encoding.substr(3) : encoding;
}

function convert(input, context) {
  if (!(input instanceof Buffer) && input !== FLUSH) {
    throw new Error('Bad argument.');  // Not a buffer or a string.
  }
  if (context !== null && context.trailer !== null) {
    // Prepend input buffer with trailer from last chunk.
    var newbuf = new Buffer(context.trailer.length + input.length);
    context.trailer.copy(newbuf, 0, 0, context.trailer.length);
    input.copy(newbuf, context.trailer.length, 0, input.length);
    context.trailer = null;
    input = newbuf;
  }
  var output = new Buffer(input.length * 2);  // To a first approximation.
  var input_start = 0;
  var output_start = 0;
  var input_size = input.length;
  var output_size = output.length;
  var out = [0,0];
  for (;;) {
    var errno = bindings.convert(this.conv_,
                                 input,
                                 input_start,
                                 input_size,
                                 output,
                                 output_start,
                                 output_size,
                                 out);
    var input_consumed = out[0];
    var output_consumed = out[1];
    input_start += input_consumed;
    input_size -= input_consumed;
    output_start += output_consumed;
    output_size -= output_consumed;
    if (errno) {
      if (errno === E2BIG) {
        output_size += output.length;
        var newbuf = new Buffer(output.length * 2);
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
