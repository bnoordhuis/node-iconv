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

var Iconv = require('../lib/iconv').Iconv;
var assert = require('assert');
var stream = require('stream');
var net = require('net');
var fs = require('fs');
var PORT = 12345;

assert(new Iconv('ascii', 'ascii') instanceof stream.Stream);

(function() {
  var infile = __dirname + '/fixtures/lorem-ipsum.txt';
  var input = fs.createReadStream(infile,
                                  { bufferSize: 64,
                                    lowWaterMark: 0,
                                    highWaterMark: 64 });
  var outfile = __dirname + '/tmp/lorem-ipsum.txt';
  var output = fs.createWriteStream(outfile);
  input.pipe(Iconv('ascii', 'utf-16le')).pipe(output);

  output.on('end', function() {
    var input = fs.readFileSync(infile);
    var output = fs.readFileSync(outfile);
    for (var i = 0; i < input.length; ++i) {
      assert.equal(output[i * 2 + 0], input[i]);
      assert.equal(output[i * 2 + 1], 0);
    }
  });
})();

(function() {
  var ok = false;

  process.on('exit', function() {
    assert(ok);
  });

  var server = net.createServer(function(conn) {
    conn.pipe(Iconv('utf-8', 'utf-7')).pipe(conn);
    server.close();
  });

  server.listen(PORT, function() {
    var conn = net.createConnection(PORT);
    conn.setEncoding('utf-8');
    conn.write('çxç');
    conn.on('data', function(s) {
      assert.equal(s, '+AOc-x+AOc-');
      ok = true;
      conn.destroy();
    });
  });
})();

(function() {
  var ok = false;
  var stream = Iconv('utf-8', 'utf-7');
  stream.on('data', function(s) {
    assert.equal(s, '+AOc-x+AOc-');
    ok = true;
  });
  stream.write('çxç');  // String should get converted to buffer.
  assert(ok);
})();

(function() {
  var num_data_events = 0;
  var num_end_events = 0;
  var stream = Iconv('utf-8', 'ascii');
  stream.on('data', function(s) {
    assert.equal(num_data_events, 0);
    assert.equal(num_end_events, 0);
    assert.equal(s, 'test');
    num_data_events += 1;
  });
  stream.on('end', function() {
    assert.equal(num_data_events, 1);
    assert.equal(num_end_events, 0);
    num_end_events += 1;
  });
  stream.end('test');
  assert.equal(num_data_events, 1);
  assert.equal(num_end_events, 1);
})();

(function() {
  var stream = Iconv('utf-8', 'ascii//translit');
  var ok = false;
  stream.on('data', function() {
    assert.equal(ok, false);
  });
  stream.on('end', function() {
    assert.equal(ok, false);
    ok = true;
  });
  fs.createReadStream(__filename).pipe(stream);
  process.on('exit', function() {
    assert(ok);
  });
})();

(function() {
  var ok = false;
  var stream = Iconv('utf-8', 'iso-8859-1');
  stream.on('data', function(buf) {
    assert.equal(buf.length, 1);
    assert.equal(buf[0], 0xA9);
    ok = true;
  });
  stream.write(Buffer([0xC2]));
  stream.write(Buffer([0xA9]));
  assert(ok);
})();

(function() {
  var ok = false;
  var stream = Iconv('utf-8', 'iso-8859-1');
  stream.once('data', step1);
  function step1(buf) {
    assert.equal(buf.length, 1);
    assert.equal(buf[0], 0xAE);
    stream.once('data', step2);
  }
  function step2(buf) {
    assert.equal(buf.length, 1);
    assert.equal(buf[0], 0xA9);
    ok = true;
  }
  stream.write(Buffer([0xC2,0xAE,0xC2]));
  stream.write(Buffer([0xA9]));
  assert(ok);
})();
