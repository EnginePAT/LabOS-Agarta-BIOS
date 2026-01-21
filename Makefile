# Directories
SRC_DIR=src
INCLUDE_DIR=include
BUILD_DIR=build


# Tools
ASM=nasm
CC=i386-elf-gcc
LD=i386-elf-ld
QEMU=qemu-system-x86_64

# Flags
CFLAGS=-ffreestanding -nostdlib -m32 -fno-stack-protector -fno-builtin -I$(INCLUDE_DIR) -g -c
LDFLAGS=-m elf_i386


# Image
IMAGE:=labos-agarta-x86_64-bios-2026.01.iso


# Object files
OBJS:=$(BUILD_DIR)/boot.o $(BUILD_DIR)/kernel.o $(BUILD_DIR)/vga.o


#
# Link the kernel and copy to LabOS/boot/kernel.bin
#
$(IMAGE): $(OBJS)
	$(LD) $(LDFLAGS) -T $(SRC_DIR)/linker.ld -o kernel.bin $^
	mv kernel.bin LabOS/boot/kernel.bin
	grub-mkrescue -o $@ LabOS/



#
# Build the source files into object files
#
$(BUILD_DIR)/boot.o: $(SRC_DIR)/boot.asm | $(BUILD_DIR)
	$(ASM) $< -f elf -o $@

$(BUILD_DIR)/kernel.o: $(SRC_DIR)/kernel.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/vga.o: $(SRC_DIR)/vga/vga.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@



#
# Clean
#
clean:
	rm -rf $(IMAGE)
	rm -rf $(BUILD_DIR)/*

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)



#
# Run
#
run: $(IMAGE)
	$(QEMU) -hda $<
