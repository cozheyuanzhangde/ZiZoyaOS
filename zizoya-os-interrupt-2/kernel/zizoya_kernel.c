#include "../drivers/vga.h"
#include "zizoya_util.h"
#include "../low-level/isr.h"
#include "../low-level/idt.h"
#include "../low-level/timer.h"
#include "../drivers/keyboard.h"

void main() {
    isr_install();

    asm volatile("sti");
    init_timer(50);
    init_keyboard();
}