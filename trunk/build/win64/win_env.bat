@echo off

if not "%OS%" == "Windows_NT" goto ErrSys

rem set the project root path, choose the right path
cd ..
cd ..
subst u: /d
subst u: .

rem set the compiler path, assuming the vs2005 is install in the default path of c:
IF EXIST "%ProgramFiles%\Microsoft Visual Studio 8\VC\vcvarsall.bat" (@call "%ProgramFiles%\Microsoft Visual Studio 8\VC\vcvarsall.bat" x64)
IF EXIST "%ProgramFiles(x86)%\Microsoft Visual Studio 8\VC\vcvarsall.bat" (@call "%ProgramFiles(x86)%\Microsoft Visual Studio 8\VC\vcvarsall.bat" x64)

rem set the env variable
::============================================
:: Configuration
set CONF=u:\conf

:: Tool
set TOOLS=u:\tools\bin

:: Build Directory
set BLD=u:\build\win64

::Source
set SRC=u:\src
set INC=u:\include

::Input
if exist "%CALROOT%include" set CAL_INC=%CALROOT%include
if exist "%CALROOT%lib\lh64" set CAL_LIB=%CALROOT%lib\lh64
if exist "%CALROOT%lib\xp64" set CAL_LIB=%CALROOT%lib\xp64
if not defined "CAL_LIB" goto ErrIncLib
if not defined "CAL_INC" goto ErrIncLib

::Output
set SPLLIB=u:\lib
set SPLBIN=u:\bin

::Docs
set DOCS=u:\docs

::============================================
set PATH=%PATH%;%TOOLS%;%SPLBIN%;%BLD%;%CONF%;%ANT_HOME%\bin;%ANT_HOME%\lib;
::=============================================
::Set app name to amd-spl
set APP=amd-spl
set CFG=debug

cd /d %BLD%
call amd-spl.sln
start cmd
goto EndOfBat

ErrIncLib
PAUSE "No 64bit CAL libraries and includes"
goto EndofBat

:ErrSys
PAUSE "This script is only for Windows NT system."
goto EndOfBat

:EndOfBat
PAUSE
