#include <system.h>
#include "vga/vga.h"

int exit(int status)
{
    if (status != 0)
    {
        vga_puts("Exited with status code 0.\n");
        while (1);
    } else {
        vga_puts("Exited with status code ERR (Unknown)\n");
        while (1);
    }
}
