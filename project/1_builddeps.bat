@echo off

cd %~dp0\..
SET KODI_SRC=%CD%
SET SOLUTION_DIR=%KODI_SRC%\project\VS2015

cd %KODI_SRC%\project\BuildDependencies
call DownloadBuildDeps.bat
call DownloadMingwBuildEnv.bat

cd %KODI_SRC%\tools\buildsteps\win32
call make-mingwlibs.bat noclean
