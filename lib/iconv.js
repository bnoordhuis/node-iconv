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

// Marker object.
var FLUSH = {};

function fixEncoding(encoding)
{
  // Convert "utf8" to "utf-8".
  return /^utf[^-]/i.test(encoding) ? 'utf-' + encoding.substr(3) : encoding;
}

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

  function convert(input) {
    var output = new Buffer(input.length * 2);  // To a first approximation.
    var input_start = 0;
    var output_start = 0;
    var input_size = input.length;
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
                                   out);
      var input_consumed = out[0];
      var output_consumed = out[1];
      input_start += input_consumed;
      input_size -= input_consumed;
      output_start += output_consumed;
      output_size -= output_consumed;
      if (errno) {
        if (errno === bindings.EINVAL) {
          throw errnoException('EINVAL', 'Incomplete character sequence.');
        }
        else if (errno === bindings.EILSEQ) {
          throw errnoException('EILSEQ', 'Illegal character sequence.');
        }
        else if (errno === bindings.E2BIG) {
          output_size += output.length;
          var newbuf = new Buffer(output.length * 2);
          output.copy(newbuf, 0, 0, output_start);
          output = newbuf;
          continue;
        }
        throw 'unexpected error';
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
  };

  this.convert = function(input) {
    if (typeof(input) === 'string') input = new Buffer(input);
    if (!(input instanceof Buffer)) throw new Error('Bad argument.');
    return convert(input, true);
  };

  this.write = function(input) {
    try {
      var buf = convert(input);
    }
    catch (e) {
      this.emit('error', e);
      return false;
    }
    if (buf && buf.length !== 0) {
      this.emit('data', convert(input));
    }
    return true;
  };

  this.end = function() {
    this.write(FLUSH);
  };
}
util.inherits(Iconv, stream.Stream);

function errnoException(code, errmsg)
{
  var err = new Error(errmsg);
  err.code = code;
  return err;
}
