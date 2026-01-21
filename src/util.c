#include <util.h>

void memset(void* dest, char val, uint32_t count)
{
    char* temp = (char*)dest;
    for (; count != 0; count--)
    {
        *temp++ = val;
    }
}

void outb(uint16_t port, uint8_t val)
{
    asm volatile("outb %0, %1" : : "a" (val), "Nd" (port));
}
