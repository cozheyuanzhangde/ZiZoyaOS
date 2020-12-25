#include "timer.h"
#include "../drivers/vga.h"
#include "../kernel/zizoya_util.h"
#include "isr.h"

unsigned int tick = 0;

static void timer_callback(registers_t regs) {
    tick++;
    vga_print("Tick: ");
    
    char tick_ascii[256];
    zzyk_itoa(tick, tick_ascii);
    vga_print(tick_ascii);
    vga_print("\n");
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