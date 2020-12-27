#ifndef IDT_H
#define IDT_H

#include "predef.h"

//segment selector
#define KERNEL_CS 0x08

typedef struct {
    unsigned short low_offset;
    unsigned short sel;
    unsigned char always0;
    unsigned char flags; 
    unsigned short high_offset;
} __attribute__((packed)) idt_gate_t;  //data structure alignment, not allow structure padding


typedef struct {
    unsigned short limit;
    unsigned int base;
} __attribute__((packed)) idt_register_t; //data structure alignment, not allow structure padding

#define IDT_ENTRIES 256
idt_gate_t idt[IDT_ENTRIES];
idt_register_t idt_reg;

void set_idt_gate(int n, unsigned int handler);
void set_idt();

#endif