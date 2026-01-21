#include "pit.h"
#include "../vga/vga.h"
#include "idt.h"

uint64_t ticks;             // Keep track of the ticks
const uint32_t freg = 100;

void onIrq0(struct InterruptRegisters* regs)
{
    // Increment the ticks by 1
    ticks += 1;
}

bool pit_init()
{
    ticks = 0;
    irq_install_handler(0, &onIrq0);

    // 1.1931816666 MHz or 119318.16666
    uint32_t divisor = 119318.16666 / freg;         // The decimal places arn't necassary. Use 1193180 if required.

    outb(0x43, 0x36);
    outb(0x40, (uint8_t)(divisor & 0xFF));
    outb(0x40, (uint8_t)((divisor >> 8) & 0xFF));

    return true;
}
