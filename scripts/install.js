#!/usr/bin/env node

var fs = require('fs'),
    util = require('util'),
    path = require('path'),
    platform = process.platform
    , arch = process.arch
    , version = parseVersion(process.versions.node)


function parseVersion (str) {
    var m = String(str).match(/(\d+)\.(\d+)/)
    return m ? m[0] : null
}

var dir = path.join(__dirname,'..','compiled',version,platform,arch),
    srcPath = path.join(__dirname,'..', 'iconv.node'),
    dstPath = path.join(dir, 'iconv.node'),
    spawn = require('child_process').spawn;


var mkdir = spawn('mkdir', ['-p', dir], {cwd:path.join(__dirname,'..')});

mkdir.stdout.on('data', function (data) {
    console.log(''+data);
});

mkdir.stderr.on('data', function (data) {
    console.log(''+data);
});

var mv = spawn('mv', ['-fv', srcPath, dstPath], {cwd:path.join(__dirname,'..')});

mv.stdout.on('data', function (data) {
    console.log(''+data);
});

mv.stderr.on('data', function (data) {
    console.log(''+data);
});
