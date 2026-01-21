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
OBJS:=$(BUILD_DIR)/boot.o $(BUILD_DIR)/kernel.o $(BUILD_DIR)/vga.o $(BUILD_DIR)/gdt.o $(BUILD_DIR)/gdt_s.o \
	$(BUILD_DIR)/util.o $(BUILD_DIR)/system.o $(BUILD_DIR)/idt.o $(BUILD_DIR)/idt_s.o $(BUILD_DIR)/pit.o


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
# Core kernel
$(BUILD_DIR)/boot.o: $(SRC_DIR)/boot.asm | $(BUILD_DIR)
	$(ASM) $< -f elf -o $@

$(BUILD_DIR)/kernel.o: $(SRC_DIR)/kernel.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/vga.o: $(SRC_DIR)/vga/vga.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@


# System utilities
$(BUILD_DIR)/util.o: $(SRC_DIR)/util.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/system.o: $(SRC_DIR)/system.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@


# Memory management sources
$(BUILD_DIR)/gdt.o: $(SRC_DIR)/mm/gdt.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/gdt_s.o: $(SRC_DIR)/mm/gdt.asm | $(BUILD_DIR)
	$(ASM) $< -f elf -o $@

$(BUILD_DIR)/idt.o: $(SRC_DIR)/mm/idt.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/idt_s.o: $(SRC_DIR)/mm/idt.asm | $(BUILD_DIR)
	$(ASM) $< -f elf -o $@


$(BUILD_DIR)/pit.o: $(SRC_DIR)/mm/pit.c | $(BUILD_DIR)
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
