@echo off

IF NOT EXIST "C:\Program Files (x86)\CMake\bin" (
	GOTO SKIP_SET_PATH
)
echo Adding CMake to the path
SET PATH=%PATH%;C:\Program Files (x86)\CMake\bin

:SKIP_SET_PATH

cd %~dp0\..
SET KODI_SRC=%CD%
SET SOLUTION_DIR=%KODI_SRC%\project\VS2015

IF NOT EXIST %SOLUTION_DIR% (
	mkdir %SOLUTION_DIR%
)

cd %SOLUTION_DIR%

cmake %KODI_SRC% -G "Visual Studio 14" -DCMAKE_SYSTEM_VERSION="8.1"

set KODI_HOME=%SOLUTION_DIR%
set PATH=%SOLUTION_DIR%\system;%PATH%
IF EXIST %SOLUTION_DIR%\kodi.sln (
	start %SOLUTION_DIR%\kodi.sln
)
