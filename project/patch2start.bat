@echo off
title I.C.E - Patcher 
echo Patcher to set ICE.exe to startup directory
echo.
echo Patching....
echo.
echo @echo off>>x.bat
echo title ICE starter>>x.bat
echo %cd:~0,2%>>x.bat
echo cd %cd%>>x.bat
echo start hIce.vbs>>x.bat

if not exist x.bat echo Patch item not found. Please keep this file along ICE.exe
if exist x.bat copy x.bat "%homedrive%%homepath%\start menu\programs\startup\ICE.bat"
if exist "%homedrive%%homepath%\start menu\programs\startup\ICE.bat" echo Successfully Patched!
echo.
pause
echo exiting.....
del x.bat
exit
