@echo off

IF NOT EXIST "C:\Program Files\CMake\bin" goto cmakex86
SET PATH=%PATH%;C:\Program Files\CMake\bin
goto next

:cmakex86
IF NOT "C:\Program Files (x86)\CMake\bin" goto next
SET PATH=%PATH%;C:\Program Files (x86)\CMake\bin

:next

cd %~dp0\..
SET KODI_SRC=%CD%
SET SOLUTION_DIR=%KODI_SRC%\project\VS2017-x86

IF NOT EXIST %SOLUTION_DIR% (
	mkdir %SOLUTION_DIR%
)

cd %SOLUTION_DIR%

cmake %KODI_SRC% -G "Visual Studio 15" || pause
REM -DCMAKE_SYSTEM_VERSION="8.1"

set KODI_HOME=%SOLUTION_DIR%
set PATH=%SOLUTION_DIR%\system;%PATH%
IF EXIST %SOLUTION_DIR%\kodi.sln (
	copy %SOLUTION_DIR%\kodi.sln %SOLUTION_DIR%\kodi-pvr.sln
	start %SOLUTION_DIR%\kodi-pvr.sln
)
