@echo off

for %%i in (Tools, tools, TOOLS) do if "%1" == "%%i" cd %TOOLs%
for %%i in (splroot, SPLROOT, SplRoot, spl) do if "%1" == "%%i" cd %SPLROOT%
for %%i in (docs, Docs, DOCS) do if "%1" == "%%i" cd %DOCS%

for %%i in (bin, BIN, Bin) do if "%1" == "%%i" cd %BIN%