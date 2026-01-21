#ifndef VGA_H
#define VGA_H

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

#define COLOR8_BLACK 0
#define COLOR8_LIGHT_GRAY 7

#include <stdint.h>

void vga_reset();
void vga_scroll();
void vga_newLine();
void vga_putc(char c);
void vga_puts(const char* s);


#endif      // VGA_H
