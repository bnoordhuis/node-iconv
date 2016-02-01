var Iconv = require('./lib/iconv.js').Iconv;

var iconv = new Iconv('UTF-8', 'ASCII//TRANSLIT//IGNORE', 'de_DE.UTF-8');


var time = Date.now();

var data = iconv.convert('ü  ä  ö  ß  Ü  Ä  Ö {"·45 g kjshdflkj hl sññplñlñl+çñç').toString();

console.log(Date.now() - time);

console.log(data);
