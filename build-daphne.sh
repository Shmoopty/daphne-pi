#!/bin/bash

# This script should produce the executable daphne.bin in the current directory

# Determine Raspberry Pi hardware
PI_VERSION=UNKNOWN
ARCH=$(uname -m)
if [[ $ARCH == *"armv6"* ]]
then
  PI_VERSION=rpi
  echo "This hardware resembles a Raspberry Pi 1"
elif [[ $ARCH == *"armv7"* ]]
then
  PI_VERSION=rpi2
  echo "This hardware resembles a Raspberry Pi 2"
else
  echo "This hardware is unfamiliar!  Not arm6 or arm7."
  exit 1
fi

# Get dependencies
sudo apt-get update
if [ $? -ne 0 ]; then echo "apt-get update was not successful"; exit 1; fi

sudo apt-get -y install libvorbis-dev libglew-dev
if [ $? -ne 0 ]; then echo "installing dependencies was not successful"; exit 1; fi

# Optional: clean intermediate files
#find . -name "*.[od]" -delete

# Build vldp2 lib
pushd ./src/vldp2/
if [ $? -ne 0 ]; then echo "vldp2 directory not found"; exit 1; fi

./configure
if [ $? -ne 0 ]; then echo "vldp2 config was not successful"; exit 1; fi

make -f "Makefile.linux_$PI_VERSION"
if [ $? -ne 0 ]; then echo "vldp2 build was not successful"; exit 1; fi

popd

# Build Daphne
pushd ./src/
if [ $? -ne 0 ]; then echo "src directory not found"; exit 1; fi

rm -f ./Makefile.vars
ln -s "./Makefile.vars.linux_$PI_VERSION" ./Makefile.vars
if [ $? -ne 0 ]; then echo "./Makefile.vars.linux_$PI_VERSION was not found"; exit 1; fi

make
popd

# Copy daphne to runtime folder
cp -f ./daphne.bin ./daphne/daphne
if [ $? -ne 0 ]; then echo "daphne.bin was not found"; exit 1; fi

# Success
echo ""
echo "Success!"
echo ""
echo "From the daphne subfolder, you should now be able to run:"
echo " $ ./daphne lair noldp -nohwaccel"
echo ""
echo "(Keyboard 'Q' to quit)"
echo ""

