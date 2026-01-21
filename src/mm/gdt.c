#include "gdt.h"
#include <util.h>


extern void gdt_flush(uint32_t);
extern void tss_flush();
struct gdt_entry_struct gdt_entries[6];
struct gdt_ptr_struct gdt_ptr;
struct tss_entry_struct tss_entry;


bool gdt_init()
{
    // Initialize the GDT
    gdt_ptr.limit = (sizeof(struct gdt_entry_struct) * 6) - 1;
    gdt_ptr.base = (uint32_t)gdt_entries;

    gdt_set_gate(0, 0, 0, 0, 0);                    // Null segments
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);     // Kernel Code Segment
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);     // Kernel Data Segment
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);     // User Code Segment
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);     // User Data Segment

    tss_write(5, 0x10, 0x0);                        // Write the Task State Segment (TSS)

    gdt_flush((uint32_t)&gdt_ptr);
    tss_flush();
    return true;
}


void gdt_set_gate(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{

    gdt_entries[num].base_low = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high = (base >> 24) & 0xFF;

    gdt_entries[num].limit = limit & 0xFFFF;
    gdt_entries[num].flags = (limit >> 16) & 0x0F;
    gdt_entries[num].flags |= (gran & 0xF0);

    gdt_entries[num].access = access;
    
}

void tss_write(uint32_t num, uint16_t ss0, uint16_t esp0)
{
    uint32_t base = (uint32_t)&tss_entry;
    uint32_t limit = base + sizeof(tss_entry);

    gdt_set_gate(num, base, limit, 0xE9, 0x00);
    memset(&tss_entry, 0, sizeof(tss_entry));

    tss_entry.ss0 = ss0;            // Set the kernel stack segment
    tss_entry.esp0 = esp0;          // Set the stack pointer

    tss_entry.cs = 0x08 | 0x3;      // Set the code segment (privledge mode 3 - this lets us switch into kernel mode from ring 3)
    tss_entry.ss = tss_entry.ds = tss_entry.fs = tss_entry.gs = tss_entry.es = 0x10 | 0x3;
}
