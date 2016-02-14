#!/bin/bash

# This script should install the built daphne to RetroPie

if [ "$EUID" -ne 0 ]
  then echo "Please run as root"
  exit
fi

# Verify build
if [ ! -f daphne/daphne ]; then
  echo "Daphne has not been fully built!  Run ./build-daphne.sh"
  exit 1
fi

# Install runtime

cp -rf ./daphne /opt/retropie/emulators/
if [ $? -ne 0 ]; then echo "apt-get update was not successful"; exit 1; fi

# Install roms folder

mkdir -p /home/pi/RetroPie/roms/daphne
if [ $? -ne 0 ]; then echo "Could not create rom folder"; exit 1; fi

cp ./supplementary/dapinput.ini /home/pi/RetroPie/roms/daphne/
if [ $? -ne 0 ]; then echo "Could not copy button mapping"; exit 1; fi

cp ./supplementary/README.txt /home/pi/RetroPie/roms/daphne/
if [ $? -ne 0 ]; then echo "Could not copy rom folder README.txt"; exit 1; fi

# Install config

mkdir -p /opt/retropie/configs/daphne/
if [ $? -ne 0 ]; then echo "Could not create configs folder"; exit 1; fi

cp -f ./supplementary/emulators.cfg /opt/retropie/configs/daphne/
if [ $? -ne 0 ]; then echo "Could not copy config"; exit 1; fi

# Backup and replace systems list

cp -f /etc/emulationstation/es_systems.cfg /etc/emulationstation/es_systems.cfg.backup
if [ $? -ne 0 ]; then echo "Could not backup es_systems.cfg"; exit 1; fi

cp -f ./supplementary/es_systems.cfg /etc/emulationstation/
if [ $? -ne 0 ]; then echo "Could not replace es_systems.cfg"; exit 1; fi

# Success
echo ""
echo "Success!"
echo ""
echo "Daphne should now be a working emulator in RetroPie when it next starts"
echo ""

