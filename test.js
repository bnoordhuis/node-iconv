var Iconv = require('./lib/iconv.js').Iconv;

var iconvDE = new Iconv('UTF-8', 'ASCII//TRANSLIT//IGNORE', 'de_DE.UTF-8');
var iconvEN = new Iconv('UTF-8', 'ASCII//TRANSLIT//IGNORE', 'en_US.UTF-8');

var ITERATIONS = 100000;
var TEST_STRING = 'ü  ä  ö  ß  Ü  Ä  Ö {"·45 g kjshdflkj hl sññplñlñl+çñç';
var GERMAN_TRANSLITERATION = 'ue  ae  oe  ss  UE  AE  OE {"?45 g kjshdflkj hl snnplnlnl+cnc';
var ENGLISH_TRANSLITERATION = 'u  a  o  ss  U  A  O {"?45 g kjshdflkj hl snnplnlnl+cnc';

var time = Date.now();

for(var i = ITERATIONS; i >= 0; i--){
	iconvDE.convert(TEST_STRING).toString();
}

var elapsedTime = (Date.now() - time);

console.log('Time for ' + ITERATIONS + ' iterations with ' + TEST_STRING.length + ' characters string: ' + elapsedTime + 'ms');
console.log('One transliteration takes: ' + (elapsedTime / ITERATIONS).toFixed(3) + "ms");

if(testDE() && testC() && testC() && testDE() && testDE() && testDE() && testC() && testDE())
	console.log('All test OK');
else
	console.log('Test FAIL');



function testDE (iconv) {
	if(iconvDE.convert(TEST_STRING).toString() !== GERMAN_TRANSLITERATION)
		return false;	
	return true;
}

function testC (iconv) {
	if(iconvEN.convert(TEST_STRING).toString() !== ENGLISH_TRANSLITERATION)
		return false;
	
	return true;
}
