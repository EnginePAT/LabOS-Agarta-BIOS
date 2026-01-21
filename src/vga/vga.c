#include "vga.h"

uint16_t line = 0;
uint16_t column = 0;
uint16_t* vga = (uint16_t* const) 0xB8000;

// Color attributes
const uint16_t defaultColor = (COLOR8_LIGHT_GRAY << 8) | (COLOR8_BLACK << 12);
uint16_t currentColor = defaultColor;


void vga_reset()
{
    // Reset variables so drawing starts at the start of the screen
    column = 0;
    line = 0;
    currentColor = defaultColor;

    // Loop over the screen and set all spaces to a ' '
    // NOTE:    i = x axis
    //          j = y axis
    for (uint16_t i = 0; i < VGA_WIDTH; i++)
    {
        for (uint64_t j = 0; j < VGA_HEIGHT; j++)
        {
            vga[j * VGA_WIDTH + i] = ' ' | currentColor;
        }
    }
}


void vga_scroll()
{
    for (uint16_t i = 0; i < VGA_WIDTH; i++)
    {
        for (uint16_t j = 1; j < VGA_HEIGHT; j++)
        {
            vga[(j - 1) * VGA_WIDTH + i] = vga[j * VGA_WIDTH + i];
        }
    }

    for (uint16_t i = 0; i < VGA_WIDTH; i++)
    {
        vga[(VGA_HEIGHT - 1) * VGA_WIDTH + i] = ' ' | currentColor;
    }

    line = VGA_HEIGHT - 1;
}

void vga_newLine()
{
    if (line < VGA_HEIGHT - 1)
    {
        line++;
        column = 0;         // We want to start at the beginning of the line
    } else {
        vga_scroll();
        column = 0;
    }
}

void vga_putc(char c)
{
    // Print the character to the screen and increment the column
    vga[line * VGA_WIDTH + column] = c | currentColor;
    column++;

    // Simple line wrapping
    if (column > VGA_WIDTH)
    {
        column = 0;
        line++;
    }

    // If we are at the bottom, scroll
    if (line > VGA_HEIGHT)
    {
        vga_scroll();
    }
}

void vga_puts(const char* s)
{
    // Loop over the string provided and place a character
    while (*s != '\0')
    {
        switch (*s)
        {
            case '\n':
                vga_newLine();
                s++;
                break;

            default:
                vga_putc(*s++);         // Increment so we don't end up in an infinite loop!
                break;
        }
    }
}
