:: Copiador de Assets para el .exe // Franco Vega

@echo off
echo Copiador de Assets para el .exe by Franco Vega
echo Copiando Archivos de Assets....

set targetdir=%1
set solutiondir=%2

XCOPY "%solutiondir%lib\SFML-2.5.1\bin\sfml-graphics-2.dll" "%targetdir%" /E /Y /S
XCOPY "%solutiondir%lib\SFML-2.5.1\bin\sfml-system-2.dll" "%targetdir%" /E /Y /S
XCOPY "%solutiondir%lib\SFML-2.5.1\bin\sfml-window-2.dll" "%targetdir%" /E /Y /S
XCOPY "%solutiondir%lib\STP\bin\STP.dll" "%targetdir%" /E /Y /S
XCOPY "%solutiondir%lib\STP\bin\zlib.dll" "%targetdir%" /E /Y /S

MKDIR "%targetdir%res/assets"
XCOPY "%solutiondir%res/assets" "%targetdir%res/assets" /E /Y /S

echo Copia de Assets terminada!


