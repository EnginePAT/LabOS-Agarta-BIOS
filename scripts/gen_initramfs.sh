#!/bin/bash

# Disk image name
export NAME=initrd.img

# Generate the initramfs disk image for the operating system
# Create the disk image
dd if=/dev/zero of=$NAME bs=1m count=64         # 64Mb blank disk
mkfs.vfat -F 32 -n "LabOSAgarta" -I $NAME       # Turn the blank disk into FAT32 formatted disk

# Copy a dummy file onto the filesystem (May be overwritten when gen_sysroot.sh runs)
if command -v mtools
then
    mcopy -i $NAME scripts/Welcome.txt ::Welcome.txt
else
    echo "[ERROR]: Mtools could not be found. Please install with either"
    echo "brew install mtools"
    echo "sudo apt-get install mtools"
fi

# Copy the disk image to '/LabOS/' (/ = project root)
cp $NAME LabOS/$NAME
