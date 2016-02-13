#!/bin/bash

# This script should produce the executable daphne.bin in the current directory

# Get dependencies
sudo apt-get update
sudo apt-get -y install libvorbis-dev libglew-dev

# Optional: clean intermediate files
#find . -name "*.[od]" -delete

# Build vldp2 lib
pushd ./src/vldp2/
./configure
make -f Makefile.linux_rpi2
popd

# Build Daphne
pushd ./src/
rm ./Makefile.vars
ln -s ./Makefile.vars.linux_rpi2 ./Makefile.vars
make
popd

# Copy daphne to runtime folder
cp ./daphne.bin ./daphne/daphne

# Success
echo ""
echo "Success!"
echo ""
echo "From the daphne subfolder, you should now be able to run:"
echo " $ ./daphne lair noldp -nohwaccel"
echo ""
echo "(Keyboard 'Q' to quit)"
echo ""

