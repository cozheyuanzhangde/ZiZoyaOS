#include "../drivers/vga.h"
#include "zizoya_util.h"
#include "../low-level/isr.h"
#include "../low-level/idt.h"

void main() {
    isr_install();
    //test interrupts
    __asm__ __volatile__("int $2");
    __asm__ __volatile__("int $3");
}