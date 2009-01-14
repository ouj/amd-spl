echo off

set CLEANING=NO
for %%i in (DOCS, Docs, docs) do if "%1" == "%%i" goto BUILDDOC

for %%i in (Dbg, DBG, dbg) do if "%1" == "%%i" set CFG=DEBUG
for %%i in (REL, rel, Rel) do if "%1" == "%%i" set CFG=RELEASE

if "%APP%." == "." goto BADENV
if "%CFG%." == "." goto BADENV

set BUILDERR=%APP%_%CFG%.err
if exist %BUILDERR% del /f %BUILDERR%

if exist %APP%.vcproj goto CONTINUE
echo. fatal error:%APP%.vcproj does not exist
echo. fatal error:%APP%.vcproj does not exist > %BUILDERR%
goto END

:CONTINUE

set CLEANING=NO
for %%i in (Clean clean CLEAN) do if "%1" == "%%i" set CLEANING=YES

set BLDORCLN=
if /I "%CLEANING%"=="YES" set BLDORCLN=/clean

@for /f %%i in ('time /t') do @echo ___ {%%i} %BLDORCLN% %APP% %CFG% ___


::BUILD
call vcbuild /nologo %BLDORCLN% /errfile:%BUILDERR% /logfile:%BUILDERR% /useenv %APP%.vcproj "%CFG%"

if exist %BUILDERR% type %BUILDERR% > nul

goto END

:BUILDDOC
doxygen %CONF%\doxygen-conf
goto END

:BADENV

:END
set BUILDERR=
set CLEANING=
set BLDORCLN=