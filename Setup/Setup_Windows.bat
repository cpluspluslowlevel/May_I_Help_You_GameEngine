@echo off
setlocal

set EXTERNAL_DIRECTORY=%~dp0\..\External
set VCPKG_DIRECTORY=%EXTERNAL_DIRECTORY%\vcpkg

echo Checking %EXTERNAL_DIRECTORY% directory
if not exist "%EXTERNAL_DIRECTORY%" (
    echo Creating %EXTERNAL_DIRECTORY% directory
    mkdir "%EXTERNAL_DIRECTORY%"
) else (
    echo %EXTERNAL_DIRECTORY% directory already exists
)

echo Checking %VCPKG_DIRECTORY% directory
if not exist "%VCPKG_DIRECTORY%" (
    echo Creating %VCPKG_DIRECTORY% directory
    mkdir "%VCPKG_DIRECTORY%"
) else (
    echo %VCPKG_DIRECTORY% directory already exists
)

echo Checking vcpkg
%VCPKG_DIRECTORY%\vcpkg.exe --version
echo Error code: %errorlevel%
if %errorlevel% equ 0 (
    echo vcpkg already installed.
) else (

    echo Installing vcpkg

    echo Cloning vcpkg repository
    git clone https://github.com/microsoft/vcpkg.git "%VCPKG_DIRECTORY%"
    echo Error code: %errorlevel%

    echo Bootstrapping vcpkg
    call %VCPKG_DIRECTORY%\bootstrap-vcpkg.bat
    echo Error code: %errorlevel%

)



echo Installing packages
echo Checking vcpkg
%VCPKG_DIRECTORY%\vcpkg.exe --version
echo Error code: %errorlevel%
if %errorlevel% equ 0 (
    echo vcpkg installed.
) else (
    echo Failed to install vcpkg.
    exit /b 1
)

echo Installing clang


endlocal
pause