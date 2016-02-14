#!/bin/bash

FULL_PATH=$1
DIR=$(basename "$FULL_PATH")
NAME="${DIR%.*}"

/opt/retropie/emulators/daphne/daphne "$NAME" vldp -nohwaccel -framefile "$FULL_PATH/$NAME.txt" -homedir /home/pi/RetroPie/roms/daphne -fullscreen -fastboot


