@echo off

if not "%OS%" == "Windows_NT" goto ErrSys

rem detect system type


rem detect system bit
IF DEFINED "ProgramFiles(x86)" (set SYSTEM_BIT=64) ELSE (set SYSTEM_BIT=32)
echo This is a %SYSTEM_BIT% bit system.

rem set the project root path, choose the right path
cd ..
cd ..
subst u: /d
subst u: .

rem set the compiler path, assuming the vs2005 is install in the default path of c:
IF %SYSTEM_BIT%==32 (cd /d "%ProgramFiles%\Microsoft Visual Studio 8") ELSE (cd /d %ProgramFiles(x86)%\Microsoft Visual Studio 8)
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
set CAL_INC=%CALROOT%include
if exist "%CALROOT%lib\lh32" set CAL_LIB=%CALROOT%lib\lh32
if exist "%CALROOT%lib\xp32" set CAL_LIB=%CALROOT%lib\xp32
if exist "%CALROOT%lib\lh64" set CAL_LIB=%CALROOT%lib\lh64
if exist "%CALROOT%lib\xp64" set CAL_LIB=%CALROOT%lib\xp64

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
call amd-spl.sln
start cmd
goto EndOfBat

:ErrSys
echo "This script is only for Windows NT system."
goto EndOfBat

:EndOfBat
