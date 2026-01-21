#!/bin/bash

# Generate the system root for LabOS Agarta
export NAME=initrd.img
if ! mkdir -p sysroot/{tmp,var,etc,usr,dev,home,frameworks,apps}
then
    echo "[ERROR]: Failed to create directory structure!"
else
    echo "Successfully created sysroot!"
fi


# Copy the sysroot folder contents to the FAT32 filesystem
if command -v mtools
then
    mcopy -i "$NAME" sysroot/* ::/
else
    echo "[ERROR]: Mtools could not be found. Please install with either"
    echo "brew install mtools"
    echo "sudo apt-get install mtools"
fi
