#include "zizoya_kernel.h"
#include "../drivers/vga.h"
#include "../drivers/keyboard.h"
#include "../library/memory.h"
#include "../library/string.h"
#include "../low-level/isr.h"
#include "../low-level/idt.h"
#include "../low-level/timer.h"

void main() {
    isr_install();
    irq_install();

    vga_print("Type something, it will go through the kernel\n"
        "Type END to halt the CPU\n> ");
}

void user_input(char* input) {
    if (zzylib_strcmp(input, "END") == 0) {
        vga_print("Stopping the CPU. Bye!\n");
        __asm__ __volatile__("hlt");
    }
    vga_print(input);
    vga_print("\n> ");
}