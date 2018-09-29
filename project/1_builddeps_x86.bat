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

cd %KODI_SRC%\tools\buildsteps\windows\win32
call download-dependencies.bat
call download-msys2.bat
call make-mingwlibs.bat noclean
