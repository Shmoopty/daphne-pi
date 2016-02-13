#!/bin/bash

# This script should produce the executable daphne.bin in the current directory

# Get dependencies
sudo apt-get update
sudo apt-get install libvorbisidec1
sudo apt-get install libglew1.10

# Optional: clean intermediate files
find . -name "*.[od]" -delete

# Build vldp2 lib
pushd ./src/vldp2/
./configure
make -f Makefile.linux_rpi2
popd

# Build Daphne
pushd ./src/
sudo apt-get install libvorbisidec1
rm ./Makefile.vars
ln -s ./Makefile.vars.linux_rpi2 ./Makefile.vars
make

