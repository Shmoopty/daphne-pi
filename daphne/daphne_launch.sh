#!/bin/bash

FULL_PATH=$1
DIR=$(basename "$FULL_PATH")
NAME="${DIR%.*}"


COMMAND_LINE_FILE="$FULL_PATH/$NAME.commands"
if [ -f "$COMMAND_LINE_FILE" ];
then
  CMD_LINE_EXTRAS=$(<"$COMMAND_LINE_FILE")
else
  CMD_LINE_EXTRAS=""
fi

/opt/retropie/emulators/daphne/daphne "$NAME" vldp -nohwaccel -framefile "$FULL_PATH/$NAME.txt" -homedir /home/pi/RetroPie/roms/daphne -fullscreen $CMD_LINE_EXTRAS
