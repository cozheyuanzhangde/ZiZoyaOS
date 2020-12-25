#include "../drivers/vga.h"
#include "zizoya_util.h"
#include "../low-level/isr.h"
#include "../low-level/idt.h"
#include "../low-level/timer.h"
#include "../drivers/keyboard.h"

void main() {
    vga_print("hello");
    isr_install();
    __asm__ __volatile__("sti");
    //init_timer(10);
    init_keyboard();
}