@echo off
rem Do not edit! This batch file is created by CASIO fx-9860G SDK.


if exist SPEED.G1A  del SPEED.G1A

cd debug
if exist FXADDINror.bin  del FXADDINror.bin
"G:\Casio SDK\OS\SH\Bin\Hmake.exe" Addin.mak
cd ..
if not exist debug\FXADDINror.bin  goto error

"G:\Casio SDK\Tools\MakeAddinHeader363.exe" "G:\Casio SDK\Projekte\Speed"
if not exist SPEED.G1A  goto error
echo Build has completed.
goto end

:error
echo Build was not successful.

:end

