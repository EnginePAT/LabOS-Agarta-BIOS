#include <stdint.h>
#include <system.h>
#include "vga/vga.h"
#include "mm/gdt.h"
#include "mm/idt.h"
#include "mm/pit.h"

extern void kernel_main(void);          // Forward declare to avoid redeclaration issues

extern void kernel_main(void)
{
    vga_reset();

    // Initialize the GDT
    if (!gdt_init())
    {
        vga_puts("[ ERROR ]: Failed to start GDT!\n");
        exit(1);
    }
    vga_puts("[ OK ]: GDT is done!\n");


    // Initialize the IDT
    if (!idt_init())
    {
        vga_puts("[ ERROR ]: Failed to start IDT!\n");
        exit(1);
    }
    vga_puts("[ OK ]: IDT is done!\n");

    // Initialize the PIT timer
    if (!pit_init())
    {
        vga_puts("[ ERROR ]: Failed to start PIT!\n");
        exit(1);
    }
    vga_puts("[ OK ]: PIT is running!\n");


    // Print our message
    vga_puts("Hello, world!");
    vga_puts("++++++++++++++++++\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
    while (1);                          // Infinite loop
}
