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

const Iconv = require('../').Iconv;
const assert = require('assert');
const stream = require('stream');
const net = require('net');
const fs = require('fs');
const PORT = 12345;

assert(new Iconv('ascii', 'ascii') instanceof stream.Stream);

(function() {
  const infile = __dirname + '/fixtures/lorem-ipsum.txt';
  const input = fs.createReadStream(infile,
                                  { bufferSize: 64,
                                    lowWaterMark: 0,
                                    highWaterMark: 64 });
  const outfile = __dirname + '/tmp/lorem-ipsum.txt';
  const output = fs.createWriteStream(outfile);
  input.pipe(Iconv('ascii', 'utf-16le')).pipe(output);

  output.on('end', function() {
    const input = fs.readFileSync(infile);
    const output = fs.readFileSync(outfile);
    for (let i = 0; i < input.length; ++i) {
      assert.equal(output[i * 2 + 0], input[i]);
      assert.equal(output[i * 2 + 1], 0);
    }
  });
})();

(function() {
  let ok = false;

  process.on('exit', function() {
    assert(ok);
  });

  const server = net.createServer(function(conn) {
    conn.pipe(Iconv('utf-8', 'utf-7')).pipe(conn);
    server.close();
  });

  server.listen(PORT, function() {
    const conn = net.createConnection(PORT);
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
  let ok = false;
  const stream = Iconv('utf-8', 'utf-7');
  stream.on('data', function(s) {
    assert.equal(s.toString(), '+AOc-x+AOc-');
    ok = true;
  });
  stream.write('çxç');  // String should get converted to buffer.
  assert(ok);
})();

(function() {
  let num_data_events = 0;
  let num_end_events = 0;
  const stream = Iconv('utf-8', 'ascii');
  stream.on('data', function(s) {
    assert.equal(num_data_events, 0);
    assert.equal(num_end_events, 0);
    assert.equal(s.toString(), 'test');
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
  const stream = Iconv('utf-8', 'ascii//translit');
  let ok = false;
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
  let ok = false;
  const stream = Iconv('utf-8', 'iso-8859-1');
  stream.on('data', function(buf) {
    assert.equal(buf.length, 1);
    assert.equal(buf[0], 0xA9);
    ok = true;
  });
  stream.write(Buffer.from([0xC2]));
  stream.write(Buffer.from([0xA9]));
  assert(ok);
})();

(function() {
  let ok = false;
  const stream = Iconv('utf-8', 'iso-8859-1');
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
  stream.write(Buffer.from([0xC2,0xAE,0xC2]));
  stream.write(Buffer.from([0xA9]));
  assert(ok);
})();

(function() {
  let ok = false;
  const stream = Iconv('utf-8', 'iso-8859-1');
  stream.once('data', function(buf) {
    assert.equal(buf.toString(), 'ok');
    ok = true;
  });
  stream.write('b2s=', 'base64');
  assert(ok);
})();

(function() {
  let ok = false;
  const stream = Iconv('utf-8', 'iso-8859-1');
  stream.once('data', function(buf) {
    assert.equal(buf.toString(), 'ok');
    ok = true;
  });
  stream.end('b2s=', 'base64');
  assert(ok);
})();

(function() {
  let ok = false;
  const stream = Iconv('gb18030', 'utf-8');
  stream.once('error', function(e) {
    assert.equal(e.message, 'Incomplete character sequence.');
    assert.equal(e.code, 'EINVAL');
    ok = true;
  });
  const octets = [
    0x00, 0xf1, 0x52, 0x00, 0x00, 0x78, 0x51, 0xd9, 0xf7, 0x78, 0x51, 0xd9
  ];
  stream.end(Buffer.from(octets));
  assert(ok);
})();

(function() {
  let ok = false;
  const stream = Iconv('utf-8', 'utf-16');
  stream.once('error', function(e) {
    assert.equal(e.message, 'Incomplete character sequence.');
    assert.equal(e.code, 'EINVAL');
    ok = true;
  });
  stream.end(Buffer.from([0xc3]));
  assert(ok);
})();
