@echo off
setlocal

set EXTERNAL_DIRECTORY=%~dp0\..\External

echo -------------------------------------------------------------------------------
echo Checking directory

echo Checking %EXTERNAL_DIRECTORY% directory
if not exist "%EXTERNAL_DIRECTORY%" (
    echo Creating %EXTERNAL_DIRECTORY% directory
    mkdir "%EXTERNAL_DIRECTORY%"
) else (
    echo %EXTERNAL_DIRECTORY% directory already exists
)

echo -------------------------------------------------------------------------------


endlocal
pause