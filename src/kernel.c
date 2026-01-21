#include <stdint.h>
#include "vga/vga.h"

extern void kernel_main(void);          // Forward declare to avoid redeclaration issues

extern void kernel_main(void)
{
    vga_reset();
    vga_puts("Hello, world!");
    vga_puts("++++++++++++++++++\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
    while (1);                          // Infinite loop
}
