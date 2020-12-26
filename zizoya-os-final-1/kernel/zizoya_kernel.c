#include "zizoya_kernel.h"
#include "../drivers/vga.h"
#include "../drivers/keyboard.h"
#include "../library/memory.h"
#include "../library/string.h"
#include "../low-level/isr.h"
#include "../low-level/idt.h"
#include "../low-level/timer.h"

void input_selector(char* input);

int shell_mode = 0;
/***Shell Mode***/
/*
0: Normal Mode;
1: Calculator Mode;
*/

void main() {
    vga_print("\nZiZoyaOS loaded the kernel in 32BIT-PROTECTED-MODE.");
    vga_print("\nPreparing installation of Interrupt Service Routine(ISR)...");
    isr_install();
    vga_print("\nZiZoyaOS installed ISR.");
    vga_print("\nPreparing installation of TIMER and KEYBOARD Interrupt Request(IRQ)...");
    irq_install();
    vga_print("\nZiZoyaOS installed IRQ.");
    vga_print("\nZiZoya_Shell(Command Prompt) loaded. Current Shell Mode: NORMAL.");
    vga_print("\n");
    vga_print("\nType and enter 'HELP' to see options and commands.");
    vga_print("\n> ");       //command prompt starts from here

    //vga_print("Type something, it will go through the kernel\n""Type END to halt the CPU\n> ");
}

void user_input(char* input) {
    input_selector(input);
    //vga_print(input);
    vga_print("\n> ");
    /***below: solving the cursor disappear problem***/
    //char teststr[4];
    //zzylib_itoa(get_cursor_offset(),teststr);
    if(get_cursor_offset() >= 3840){
        scroll_newline_init();
    }   
}

void input_selector(char* input) {
    if(shell_mode == 0){
        if(zzylib_strcmp(input, "HALT") == 0) {
            vga_print("ZiZoyaOS is stopping the CPU...\n");
            __asm__ __volatile__("hlt");
        }else if(zzylib_strcmp(input, "CALC") == 0){
            shell_mode = 1;
            vga_print("Entered Calculator Mode, please input: \n");
        }else if(zzylib_strcmp(input, "CLRINT") == 0){
            vga_print("Clearing Interrupts...\n");
            __asm__ __volatile__("cli");
        }else if(zzylib_strcmp(input, "SETINT") == 0){
            vga_print("Setting Interrupts...\n");
            __asm__ __volatile__("sti");
        }else if(zzylib_strcmp(input, "CLRSCRN") == 0){
            vga_clear_screen();
        }else if(zzylib_strcmp(input, "HELP") == 0){
            vga_print("Available Commands in MODE NORMAL: \n");
            vga_print("CALC:     Enter Shell Mode CALC(Calculator)\n");
            vga_print("CLRINT:   Clear Interrupts\n");
            vga_print("CLRSCRN:  Clear the Screen\n");
            vga_print("HALT:     Halt/Stop the CPU\n");
            vga_print("SETINT:   Set Interrupts\n");
        }else{
            vga_print("Unknown Command in Shell Mode NORMAL.");
        }
    }else if(shell_mode == 1){
        if(zzylib_strcmp(input, "") == 0) {
            vga_print("none");
        }else if(zzylib_strcmp(input, "CLRSCRN") == 0){
            vga_clear_screen();
        }else if(zzylib_strcmp(input, "QUIT") == 0){
            shell_mode = 0;
            vga_print("Quitted Shell Mode CALC. Entered Shell Mode NORMAL.");
        }else if(zzylib_strcmp(input, "HELP") == 0){
            vga_print("Available Commands in MODE CALC: \n");
            vga_print("CLRSCRN:  Clear the Screen\n");
            vga_print("QUIT:   Quit Shell Mode CALC and Enter Mode NORMAL\n");
        }else{
            vga_print("Unknown Command in Shell Mode CALC(Calculator).");
        }
    }
}