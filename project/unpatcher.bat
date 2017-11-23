@echo off
title I.C.E - UN-Patcher 
if exist "%homedrive%%homepath%\start menu\programs\startup\ICE.bat" goto 1
if exist "%homedrive%%homepath%\start menu\programs\startup\ICEdemo.bat" goto 2
echo No ICE startup items were detected in startup
goto 3
:1
echo ICE starter found in startup
if exist "%homedrive%%homepath%\start menu\programs\startup\ICE.bat" del "%homedrive%%homepath%\start menu\programs\startup\ICE.bat"
if not exist "%homedrive%%homepath%\start menu\programs\startup\ICE.bat" echo Successfully removed ICE.bat from startup
if exist "%homedrive%%homepath%\start menu\programs\startup\ICEdemo.bat" goto 2
goto 3
:2
echo ICEdemo starter found in startup
if exist "%homedrive%%homepath%\start menu\programs\startup\ICEdemo.bat" del "%homedrive%%homepath%\start menu\programs\startup\ICEdemo.bat"
if not exist "%homedrive%%homepath%\start menu\programs\startup\ICEdemo.bat" echo Successfully removed ICEdemo.bat from startup
:3
echo.
echo Press any Key to exit.....
pause
exit
