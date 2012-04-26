@echo off
echo Configuring GNU libcharset for DJGPP v2.x...
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

:InPlace
Rem Update configuration files
echo Updating configuration scripts...
test -f ./configure.orig
if errorlevel 1 update ./configure ./configure.orig
sed -f %XSRC%/djgpp/config.sed ./configure.orig > configure
if errorlevel 1 goto SedError

Rem Make sure they have a config.site file
set CONFIG_SITE=%XSRC%/djgpp/config.site
if not "%CONFIG_SITE%" == "%XSRC%/djgpp/config.site" goto SmallEnv

Rem Make sure crucial file names are not munged by unpacking
test -f %XSRC%/config.h.in
if not errorlevel 1 mv -f %XSRC%/config.h.in %XSRC%/config.h-in
test -f %XSRC%/include/localcharset.h.in
if not errorlevel 1 mv -f %XSRC%/include/localcharset.h.in %XSRC%/include/localcharset.h-in

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
