/*
 * check-stateless
 *
 *      Complete check of a stateless encoding.
 *      Usage: check-stateless SRCDIR CHARSET
 */

IF RxFuncQuery('SysLoadFuncs') THEN DO
   CALL RxFuncAdd 'SysLoadFuncs', 'RexxUtil', 'SysLoadFuncs'
   CALL SysLoadFuncs
END

'@echo off'

PARSE ARG srcdir charset

'.\table-from 'charset' > tmp-'charset'.TXT'
'.\table-to 'charset' | sort > tmp-'charset'.INVERSE.TXT'
'cmp 'srcdir'\'charset'.TXT tmp-'charset'.TXT'

IF exists(srcdir'\'charset'.IRREVERSIBLE.TXT') = 1 THEN
    DO
        'cat 'srcdir'\'charset'.TXT 'srcdir'\'charset'.IRREVERSIBLE.TXT | sort | uniq -u > tmp-orig-'charset'.INVERSE.TXT'
        'cmp tmp-orig-'charset'.INVERSE.TXT tmp-'charset'.INVERSE.TXT'
    END
ELSE 
    DO
        'cmp 'srcdir'\'charset'.TXT tmp-'charset'.INVERSE.TXT'
    END

'rm -f tmp-'charset'.TXT tmp-'charset'.INVERSE.TXT tmp-orig-'charset'.INVERSE.TXT'

EXIT

/*
 * exists - check if file exists
 */

exists: PROCEDURE
    IF STREAM(ARG(1), 'C', 'QUERY EXISTS') = '' THEN
        RETURN 0
    ELSE
        RETURN 1
