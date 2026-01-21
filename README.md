# LabOS Agarta

LabOS Agarta is an OS developed for the x86_64 architecture.
It implements a desktop environment using VESA graphics.

## Building
Really easy to build. You just need the following tools:
- i386-elf-gcc
- i386-elf-binutils
- Mtools
- GNU Make
- Nasm
- A Unix based system (MacOS, Linux etc...)

To build:
- make
- ./scripts/gen_initrd.sh
- ./scripts/gen_sysroot.sh
- make run
