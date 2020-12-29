#include "keyboard.h"
#include "../low-level/ports.h"
#include "../low-level/isr.h"
#include "vga.h"
#include "../library/memory.h"
#include "../library/string.h"
#include "../library/function.h"
#include "../kernel/zizoya_kernel.h"

/*
keydown: mark code
keyup: break code
break code = mark code + 0x80
*/

#define BACKSPACE 0x0E
#define ENTER 0x1C
#define LSHIFT 0x2A
#define RSHIFT 0x36
#define EQUAL 0x0d
#define MINUS 0x0c
#define ONE 0x02
#define TWO 0x03
#define THREE 0x04
#define FOUR 0x05
#define FIVE 0x06
#define SIX 0x07
#define SEVEN 0x08
#define EIGHT 0x09
#define NINE 0x0a
#define ZERO 0x0b
#define LSQUAREBRACKET 0x1a
#define RSQUAREBRACKET 0x1b
#define SEMICOLON 0x27
#define APOSTROPHE 0x28
#define BACKSLASH 0x2b
#define COMMA 0x33
#define FULLSTOP 0x34
#define SLASH 0x35

#define SCANCODE_MAX 57

/*kd: keydown, 0:false, 1:true*/
int lshiftkd = 0;
int rshiftkd = 0;

static char key_buffer[256];


const char *sc_name[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6", 
    "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E", 
        "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl", 
        "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", 
        "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".", 
        "/", "RShift", "Keypad *", "LAlt", "Spacebar"};
const char sc_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 
        'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G', 
        'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V', 
        'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};

static void keyboard_callback(registers_t regs) {
    unsigned char scancode = port_byte_in(0x60);
    
    if (scancode == BACKSPACE){
        zzylib_backspace(key_buffer);
        vga_print_backspace();
    }else if(scancode == LSHIFT){
        lshiftkd = 1;
    }else if(scancode == (LSHIFT + 0x80)){
        lshiftkd = 0;
    }else if(scancode == RSHIFT){
        rshiftkd = 1;
    }else if(scancode == (RSHIFT + 0x80)){
        rshiftkd = 0;
    }else if (scancode > SCANCODE_MAX) {
        return;
    }else if(((lshiftkd == 1)||(rshiftkd == 1))&&(scancode == EQUAL)){
        char str[2] = {'+', '\0'};
        zzylib_append(key_buffer, '+');
        vga_print(str);
    }else if(((lshiftkd == 1)||(rshiftkd == 1))&&(scancode == MINUS)){
        char str[2] = {'_', '\0'};
        zzylib_append(key_buffer, '_');
        vga_print(str);
    }else if(((lshiftkd == 1)||(rshiftkd == 1))&&(scancode == ONE)){
        char str[2] = {'!', '\0'};
        zzylib_append(key_buffer, '!');
        vga_print(str);
    }else if(((lshiftkd == 1)||(rshiftkd == 1))&&(scancode == TWO)){
        char str[2] = {'@', '\0'};
        zzylib_append(key_buffer, '@');
        vga_print(str);
    }else if(((lshiftkd == 1)||(rshiftkd == 1))&&(scancode == THREE)){
        char str[2] = {'#', '\0'};
        zzylib_append(key_buffer, '#');
        vga_print(str);
    }else if(((lshiftkd == 1)||(rshiftkd == 1))&&(scancode == FOUR)){
        char str[2] = {'$', '\0'};
        zzylib_append(key_buffer, '$');
        vga_print(str);
    }else if(((lshiftkd == 1)||(rshiftkd == 1))&&(scancode == FIVE)){
        char str[2] = {'%', '\0'};
        zzylib_append(key_buffer, '%');
        vga_print(str);
    }else if(((lshiftkd == 1)||(rshiftkd == 1))&&(scancode == SIX)){
        char str[2] = {'^', '\0'};
        zzylib_append(key_buffer, '^');
        vga_print(str);
    }else if(((lshiftkd == 1)||(rshiftkd == 1))&&(scancode == SEVEN)){
        char str[2] = {'&', '\0'};
        zzylib_append(key_buffer, '&');
        vga_print(str);
    }else if(((lshiftkd == 1)||(rshiftkd == 1))&&(scancode == EIGHT)){
        char str[2] = {'*', '\0'};
        zzylib_append(key_buffer, '*');
        vga_print(str);
    }else if(((lshiftkd == 1)||(rshiftkd == 1))&&(scancode == NINE)){
        char str[2] = {'(', '\0'};
        zzylib_append(key_buffer, '(');
        vga_print(str);
    }else if(((lshiftkd == 1)||(rshiftkd == 1))&&(scancode == ZERO)){
        char str[2] = {')', '\0'};
        zzylib_append(key_buffer, ')');
        vga_print(str);
    }else if(((lshiftkd == 1)||(rshiftkd == 1))&&(scancode == LSQUAREBRACKET)){
        char str[2] = {'{', '\0'};
        zzylib_append(key_buffer, '{');
        vga_print(str);
    }else if(((lshiftkd == 1)||(rshiftkd == 1))&&(scancode == RSQUAREBRACKET)){
        char str[2] = {'}', '\0'};
        zzylib_append(key_buffer, '}');
        vga_print(str);
    }else if(((lshiftkd == 1)||(rshiftkd == 1))&&(scancode == SEMICOLON)){
        char str[2] = {':', '\0'};
        zzylib_append(key_buffer, ':');
        vga_print(str);
    }else if(((lshiftkd == 1)||(rshiftkd == 1))&&(scancode == APOSTROPHE)){
        char str[2] = {'"', '\0'};
        zzylib_append(key_buffer, '"');
        vga_print(str);
    }else if(((lshiftkd == 1)||(rshiftkd == 1))&&(scancode == BACKSLASH)){
        char str[2] = {'|', '\0'};
        zzylib_append(key_buffer, '|');
        vga_print(str);
    }else if(((lshiftkd == 1)||(rshiftkd == 1))&&(scancode == COMMA)){
        char str[2] = {'<', '\0'};
        zzylib_append(key_buffer, '<');
        vga_print(str);
    }else if(((lshiftkd == 1)||(rshiftkd == 1))&&(scancode == FULLSTOP)){
        char str[2] = {'>', '\0'};
        zzylib_append(key_buffer, '>');
        vga_print(str);
    }else if(((lshiftkd == 1)||(rshiftkd == 1))&&(scancode == SLASH)){
        char str[2] = {'?', '\0'};
        zzylib_append(key_buffer, '?');
        vga_print(str);
    }else if (scancode == ENTER){
        vga_print("\n");
        user_input(key_buffer);
        key_buffer[0] = '\0';
    } else {
        char letter = sc_ascii[(int)scancode];
        char str[2] = {letter, '\0'};
        zzylib_append(key_buffer, letter);
        vga_print(str);
    }
    UNUSED(regs);
}

void init_keyboard() {
   register_interrupt_handler(IRQ1, keyboard_callback); 
}