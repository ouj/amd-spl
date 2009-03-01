@echo off

rem set the project root path, choose the right path
cd /d ..
subst u: /d
subst u: .

rem set the compiler path, assuming the vs2005 is install in the default path of c:
cd /d C:\Program Files\Microsoft Visual Studio 8
subst x: /d
subst x: .

rem set vc system variable
@call x:\VC\bin\vcvars32.bat

rem set the env variable
::============================================
:: Configuration
set CONF=u:\conf

:: Tool
set TOOLS=u:\tools\bin

:: Build Directory
set BLD=u:\build\win32

::Source
set SRC=u:\src
set INC=u:\include

::Input
set CINC=%CALROOT%\include
set CLIB=%CALROOT%\lib\lh32

::Output
set SPLLIB=u:\lib\win32
set SPLBIN=u:\bin\win32

::Docs
set DOCS=u:\docs

::============================================
set PATH=%PATH%;%TOOLS%;%SPLBIN%;%BLD%;%CONF%;%ANT_HOME%\bin;%ANT_HOME%\lib;
::=============================================
::Set app name to amd-spl
set APP=amd-spl
set CFG=debug


cd /d %BLD%
start cmd