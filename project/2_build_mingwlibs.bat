@echo off

cd %~dp0\..
SET KODI_SRC=%CD%

cd %KODI_SRC%\tools\buildsteps\win32
call make-mingwlibs.bat noclean
