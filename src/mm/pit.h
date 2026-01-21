#ifndef PIT_H
#define PIT_H

#include <stdint.h>
#include <stdbool.h>
#include <util.h>

bool pit_init();
void onIrq0(struct InterruptRegisters* regs);

#endif      // PIT_H
