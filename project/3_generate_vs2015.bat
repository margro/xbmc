@echo off

cd %~dp0\..
SET KODI_SRC=%CD%
SET SOLUTION_DIR=%KODI_SRC%\project\VS2015

IF NOT EXIST %SOLUTION_DIR% (
	mkdir %SOLUTION_DIR%
)

cd %SOLUTION_DIR%

cmake -G "Visual Studio 14" %KODI_SRC%\project\cmake

set KODI_HOME=%SOLUTION_DIR%
set PATH=%SOLUTION_DIR%\system;%PATH%
start %SOLUTION_DIR%\kodi.sln