@echo off
echo Configuring GNU libiconv for DJGPP v2.x...
Rem The SmallEnv tests protect against fixed and too small size
Rem of the environment in stock DOS shell.

Rem Find out where the sources are
set XSRC=.
if not "%XSRC%" == "." goto SmallEnv
if "%1" == "" goto InPlace
set XSRC=%1
if not "%XSRC%" == "%1" goto SmallEnv
redir -e /dev/null update %XSRC%/configure.orig ./configure
test -f ./configure
if errorlevel 1 update %XSRC%/configure ./configure
test -d ./libcharset
if errorlevel 1 md libcharset
redir -e /dev/null update %XSRC%/libcharset/configure.orig ./libcharset/configure
test -f ./libcharset/configure
if errorlevel 1 update %XSRC%/libcharset/configure ./libcharset/configure

:InPlace
Rem Update configuration files
echo Updating configuration scripts...
test -f ./configure.orig
if errorlevel 1 update ./configure ./configure.orig
sed -f %XSRC%/djgpp/config.sed ./configure.orig > configure
if errorlevel 1 goto SedError
test -f ./libcharset/configure.orig
if errorlevel 1 update ./libcharset/configure ./libcharset/configure.orig
sed -f %XSRC%/djgpp/config.sed ./libcharset/configure.orig > configure.tmp
if errorlevel 1 goto SedError
Rem The following is needed because the toplevel configure script calls the
Rem %XSRC%/libcharset/configure script instead of ./libcharset/configure.
test -f %XSRC%/libcharset/configure.orig
if errorlevel 1 update %XSRC%/libcharset/configure %XSRC%/libcharset/configure.orig
update configure.tmp %XSRC%/libcharset/configure
rm ./configure.tmp

Rem Make sure they have a config.site file
set CONFIG_SITE=%XSRC%/djgpp/config.site
if not "%CONFIG_SITE%" == "%XSRC%/djgpp/config.site" goto SmallEnv

Rem Make sure crucial file names are not munged by unpacking
test -f %XSRC%/config.h.in
if not errorlevel 1 mv -f %XSRC%/config.h.in %XSRC%/config.h-in
test -f %XSRC%/lib/config.h.in
if not errorlevel 1 mv -f %XSRC%/lib/config.h.in %XSRC%/lib/config.h-in
test -f %XSRC%/libcharset/config.h.in
if not errorlevel 1 mv -f %XSRC%/libcharset/config.h.in %XSRC%/libcharset/config.h-in
test -f %XSRC%/libcharset/include/localcharset.h.in
if not errorlevel 1 mv -f %XSRC%/libcharset/include/localcharset.h.in %XSRC%/libcharset/include/localcharset.h-in
test -f %XSRC%/include/iconv.h.in
if not errorlevel 1 mv -f %XSRC%/include/iconv.h.in %XSRC%/include/iconv.h-in

Rem All fixes needed to get the package configured, compiled and tested.
Rem 1:  Change the stateless-check script so it knowns about the
Rem     new filenames.
Rem 2:  Ditto for Makefile.in
Rem 3:  Ditto for source files.
Rem 4:  Change the files contained in the tests subdirectory from
Rem     UNIX-style EOL into DOS-style EOL so the testsuit works.

test -f %XSRC%/stamp-djgppfixes
if not errorlevel 1 goto TestsuitFixed
Rem Fix the Makefile.ins.
test -f %XSRC%/lib/Makefile.orig
if errorlevel 1 update %XSRC%/lib/Makefile.in %XSRC%/lib/Makefile.orig
sed -f %XSRC%/djgpp/makefile.sed %XSRC%/lib/Makefile.in > Makefile.tmp
if errorlevel 1 goto SedError
update Makefile.tmp %XSRC%/lib/Makefile.in
rm Makefile.tmp
test -f %XSRC%/tests/Makefile.orig
if errorlevel 1 update %XSRC%/tests/Makefile.in %XSRC%/tests/Makefile.orig
sed -f %XSRC%/djgpp/makefile.sed %XSRC%/tests/Makefile.in > Makefile.tmp
if errorlevel 1 goto SedError
update Makefile.tmp %XSRC%/tests/Makefile.in
rm Makefile.tmp

Rem Fix the source files.
test -f %XSRC%/lib/iconv.orig
if errorlevel 1 update %XSRC%/lib/iconv.c %XSRC%/lib/iconv.orig
sed -f %XSRC%/djgpp/sources.sed %XSRC%/lib/iconv.c > iconv.tmp
if errorlevel 1 goto SedError
update iconv.tmp %XSRC%/lib/iconv.c
rm iconv.tmp
test -f %XSRC%/lib/converters.orig
if errorlevel 1 update %XSRC%/lib/converters.h %XSRC%/lib/converters.orig
sed -f %XSRC%/djgpp/sources.sed %XSRC%/lib/converters.h > converters.tmp
if errorlevel 1 goto SedError
update converters.tmp %XSRC%/lib/converters.h
rm converters.tmp
test -f %XSRC%/lib/cns/11643.orig
if errorlevel 1 update %XSRC%/lib/cns/11643.h %XSRC%/lib/cns/11643.orig
sed -f %XSRC%/djgpp/sources.sed %XSRC%/lib/cns/11643.h > 11643.tmp
if errorlevel 1 goto SedError
update 11643.tmp %XSRC%/lib/cns/11643.h
rm 11643.tmp
test -f %XSRC%/lib/cns/11643_4.orig
if errorlevel 1 update %XSRC%/lib/cns/11643_4.h %XSRC%/lib/cns/11643_4.orig
sed -f %XSRC%/djgpp/sources.sed %XSRC%/lib/cns/11643_4.h > 11643_4.tmp
if errorlevel 1 goto SedError
update 11643_4.tmp %XSRC%/lib/cns/11643_4.h
rm 11643_4.tmp
test -f %XSRC%/lib/iso/ir165.orig
if errorlevel 1 update %XSRC%/lib/iso/ir165.h %XSRC%/lib/iso/ir165.orig
sed -f %XSRC%/djgpp/sources.sed %XSRC%/lib/iso/ir165.h > ir165.tmp
if errorlevel 1 goto SedError
update ir165.tmp %XSRC%/lib/iso/ir165.h
rm ir165.tmp

Rem Change file's NL to CRLF.
utod %XSRC%/tests/*.txt
utod %XSRC%/tests/GEORGIAN/*.txt
utod %XSRC%/tests/ISO/*.txt
utod %XSRC%/tests/MAC/*.txt

Rem Fix the test scripts.
if "%XSRC%" == "." goto NoDirChange
cd | sed "s|:.*$|:|" > cd_BuildDir.bat
cd | sed "s|^.:|cd |" >> cd_BuildDir.bat
mv -f cd_BuildDir.bat %XSRC%/cd_BuildDir.bat
echo %XSRC% | sed -e "s|^/dev/||" -e "s|/|:|" -e "s|:.*$|:|g" > cd_SrcDir.bat
echo %XSRC% | sed -e "s|^/dev/||" -e "s|/|:/|" -e "s|^.*:|cd |" -e "s|^\.\.|cd &|" -e "s|/|\\|g" >> cd_SrcDir.bat
call cd_SrcDir.bat
call djgpp\edtest.bat
call cd_BuildDir.bat
rm -f cd_SrcDir.bat cd_BuildDir.bat %XSRC%/cd_BuildDir.bat
goto TestsuitFixed
:NoDirChange
call djgpp\edtest.bat
:TestsuitFixed
touch %XSRC%/stamp-djgppfixes

Rem This is required because DOS/Windows are case-insensitive
Rem to file names, and "make install" will do nothing if Make
Rem finds a file called `install'.
if exist INSTALL mv -f INSTALL INSTALL.txt

Rem install-sh is required by the configure script but clashes with the
Rem various Makefile install-foo targets, so we MUST have it before the
Rem script runs and rename it afterwards
test -f %XSRC%/install-sh
if not errorlevel 1 goto NoRen0
test -f %XSRC%/install-sh.sh
if not errorlevel 1 mv -f %XSRC%/install-sh.sh %XSRC%/install-sh
:NoRen0

Rem Set HOSTNAME so it shows in config.status
if not "%HOSTNAME%" == "" goto hostdone
if "%windir%" == "" goto msdos
set OS=MS-Windows
if not "%OS%" == "MS-Windows" goto SmallEnv
goto haveos
:msdos
set OS=MS-DOS
if not "%OS%" == "MS-DOS" goto SmallEnv
:haveos
if not "%USERNAME%" == "" goto haveuname
if not "%USER%" == "" goto haveuser
echo No USERNAME and no USER found in the environment, using default values
set HOSTNAME=Unknown PC
if not "%HOSTNAME%" == "Unknown PC" goto SmallEnv
goto userdone
:haveuser
set HOSTNAME=%USER%'s PC
if not "%HOSTNAME%" == "%USER%'s PC" goto SmallEnv
goto userdone
:haveuname
set HOSTNAME=%USERNAME%'s PC
if not "%HOSTNAME%" == "%USERNAME%'s PC" goto SmallEnv
:userdone
set _HOSTNAME=%HOSTNAME%, %OS%
if not "%_HOSTNAME%" == "%HOSTNAME%, %OS%" goto SmallEnv
set HOSTNAME=%_HOSTNAME%
:hostdone
set _HOSTNAME=
set OS=

Rem With libtool 1.4 -fPIC is the default. This completely breaks compilations
Rem with djgpp, so we will always use --disable-shared to inhibit the usage of
Rem -fPIC and -DPIC flags in libtool.
echo Running the ./configure script...
sh ./configure --enable-static --disable-shared --src=%XSRC%
if errorlevel 1 goto CfgError
echo Done.
goto End

:SedError
echo ./configure script editing failed!
goto End

:CfgError
echo ./configure script exited abnormally!
goto End

:SmallEnv
echo Your environment size is too small.  Enlarge it and run me again.
echo Configuration NOT done!

:End
test -f %XSRC%/install-sh.sh
if not errorlevel 1 goto NoRen1
test -f %XSRC%/install-sh
if not errorlevel 1 mv -f %XSRC%/install-sh %XSRC%/install-sh.sh
:NoRen1
set CONFIG_SITE=
set HOSTNAME=
set XSRC=
