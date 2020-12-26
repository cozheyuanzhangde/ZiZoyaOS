#include "timer.h"
#include "../drivers/vga.h"
#include "../library/memory.h"
#include "../library/string.h"
#include "isr.h"
#include "../low-level/ports.h"
#include "../library/function.h"

unsigned int tick = 0;

static void timer_callback(registers_t regs) {
    tick++;
    UNUSED(regs);
}

void init_timer(unsigned int freq) {
    register_interrupt_handler(IRQ0, timer_callback);

    //hardware clock: 1193180 Hz
    unsigned int divisor = 1193180 / freq;
    unsigned char low  = (unsigned char)(divisor & 0xFF);
    unsigned char high = (unsigned char)( (divisor >> 8) & 0xFF);
    port_byte_out(0x43, 0x36);
    port_byte_out(0x40, low);
    port_byte_out(0x40, high);
}