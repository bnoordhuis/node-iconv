/**
 * Copyright (C) 2011 by Ben Noordhuis <info@bnoordhuis.nl>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

var bindings = require('./iconv.node');
var constants = require('constants');
var stream = require('stream');
var util = require('util');

var errorMessages = {};
errorMessages[constants.EINVAL] = 'Incomplete character sequence.';
errorMessages[constants.EILSEQ] = 'Illegal character sequence.';
errorMessages[constants.E2BIG]  = 'Output buffer too small.'; // shouldn't happen
errorMessages[constants.ENOMEM] = 'Out of memory.';

function errnoException(errno, message) {
  return bindings.errnoException(errno, 'iconv', message || errorMessages[errno] || '');
}

// workaround for shortcoming in libiconv: "UTF-8" is recognized but "UTF8" isn't
function fixEncodingName(encoding) {
  if (typeof encoding != 'string') {
    encoding = '' + encoding;
  }
  return /^UTF\d/i.test(encoding) ? ('UTF-' + encoding.slice(3)) : encoding;
}

function iconv_open(sourceEncoding, targetEncoding) {
  sourceEncoding = fixEncodingName(sourceEncoding);
  targetEncoding = fixEncodingName(targetEncoding);
  return bindings.iconv_open(sourceEncoding, targetEncoding);
}

function Iconv(sourceEncoding, targetEncoding) {
  // guard against non-constructor function calls
  if (!(this instanceof Iconv)) {
    return new Iconv(sourceEncoding, targetEncoding);
  }

  // may throw but that's okay
  var iv_ = iconv_open(sourceEncoding, targetEncoding);

  this.convert = function(data) {
    if (typeof data != 'string' && !Buffer.isBuffer(data)) {
      return undefined; // backwards compatibility
    }

    var r = bindings.convert(iv_, data, 0);

    if (r.errno) {
      throw errnoException(r.errno);
    }

    return r.converted;
  };
}

// pass-through stream that transcodes input and emits it
function Stream(sourceEncoding, targetEncoding) {
  // guard against non-constructor function calls
  if (!(this instanceof Stream)) {
    return new Stream(sourceEncoding, targetEncoding);
  }

  stream.Stream.call(this);

  // may throw but that's okay
  var iv_ = iconv_open(sourcEncoding, targetEncoding);

  this.readable = true;
  this.writable = true;

  this.write = function(data) {
    data = bindings.convert(iv_, data, bindings.PARTIAL);
  };

  this.end = function(data) {
  };

  this.destroy = function() {
  };

  this.destroySoon = function() {
  };
}

util.inherits(Stream, stream.Stream);

exports.Iconv = Iconv;
exports.Stream = Stream;
