/*
 * check-stateful
 *
 *      Simple check of a stateful encoding.
 *      Usage: check-stateful SRCDIR CHARSET
 */

IF RxFuncQuery('SysLoadFuncs') THEN DO
   CALL RxFuncAdd 'SysLoadFuncs', 'RexxUtil', 'SysLoadFuncs'
   CALL SysLoadFuncs
END

'@echo off'

PARSE ARG srcdir charset

'..\src\iconv --binary -f 'charset' -t UTF-8 < 'srcdir'\'charset'-snippet > tmp-snippet'
'cmp 'srcdir'\'charset'-snippet.UTF-8 tmp-snippet'
'..\src\iconv --binary -f UTF-8 -t 'charset' < 'srcdir'\'charset'-snippet.UTF-8 > tmp-snippet'
'cmp 'srcdir'\'charset'-snippet tmp-snippet'
'rm -f tmp-snippet'

EXIT
