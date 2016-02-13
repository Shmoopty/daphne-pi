#!/bin/bash

# Set this to the working daphne directory, which should also contain the binary "daphne".
export DAPHNE_DIR=/home/pi/daphne

# Runs Dragon's Lair, but other games should work similarly.
$DAPHNE_DIR/daphne lair vldp -nohwaccel -framefile $DAPHNE_DIR/lair/lair.txt -homedir $DAPHNE_DIR -fullscreen -fastboot
