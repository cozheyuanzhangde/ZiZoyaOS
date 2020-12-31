#include "zizoya_kernel.h"
#include "../drivers/vga.h"
#include "../drivers/keyboard.h"
#include "../library/memory.h"
#include "../library/string.h"
#include "../low-level/isr.h"
#include "../low-level/idt.h"
#include "../low-level/timer.h"

void input_selector(char* input);
void calc_parse_helper();
int is_num(char ch);
int is_op(char ch);
int is_COMPUTE(char* input);
void computation_routine(char* string);
int str_is_num(char* str);

int shell_mode = 0;
/***Shell Mode***/
/*
0: Normal Mode;
1: Calculator Mode;
2: Drawing Mode;
*/

int timer_enabled = 0;

void kernel_main() {
    vga_print("\nZiZoyaOS loaded the kernel in 32BIT-PROTECTED-MODE.");
    vga_print("\nPreparing installation of Interrupt Service Routine(ISR)...");
    isr_install();
    vga_print("\nZiZoyaOS installed ISR.");
    vga_print("\nPreparing installation of KEYBOARD Interrupt Request(IRQ)...");
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
            vga_print("Entered CALC Mode. Type and enter 'HELP' to see options and commands.\n");
        }else if(zzylib_strcmp(input, "DRAW") == 0){
            shell_mode = 2;
            vga_print("Entered DRAW Mode. Type and enter 'HELP' to see options and commands.\n");
        }else if(zzylib_strcmp(input, "CLRINT") == 0){
            vga_print("Clearing Interrupts...\n");
            __asm__ __volatile__("cli");
        }else if(zzylib_strcmp(input, "ABOUT") == 0){
            vga_print("\nZiZoyaOS is an Operating System written by c0zzyde for learning purposes.\n\nc0zzyde: I have to say, OS dev is a really fun journey for me. Even though it is very short, I learned a lot and indeed had a sense of accomplishment during development. The feel is like building a house from bricks and tiles(from scratch). I know my OS is not comparable to the famous Windows, Linux or MacOS, it indeed has its special meaning for me. At the end, I want to appreciate everything which helped me along the way including NASM assembler and GNU gcc so technically it is not actually builded from 'nothing'. \n\nThere are two quotes that I like: \nBig things have small beginnings.\nAll men dream: but not equally.\n");
        }else if(zzylib_strcmp(input, "SETINT") == 0){
            vga_print("Setting Interrupts...\n");
            __asm__ __volatile__("sti");
        }else if(zzylib_strcmp(input, "TIMER") == 0){
            if(timer_enabled == 0){
                vga_print("Initializing Timer for 100 printed ticks...\n");
                init_timer(10);
                timer_enabled = 1;
            }else{
                vga_print("Timer is Enabled. Please shut down the machine to Disable the Timer.\n");
            }
        }else if(zzylib_strcmp(input, "CLRSCRN") == 0){
            vga_clear_screen();
        }else if(zzylib_strcmp(input, "MEMALLOC") == 0) {
            unsigned int phys_addr;
            unsigned int page = zzylib_memalloc(1000, 1, &phys_addr);
            char phys_str[16] = "";
            zzylib_htoa(phys_addr, phys_str);
            vga_print("Physical Address: ");
            vga_print(phys_str);
            vga_print("\n");
        }else if(zzylib_strcmp(input, "HELP") == 0){
            vga_print("\n");
            vga_print("Available Commands in MODE NORMAL: \n");
            vga_print("\n");
            vga_print("ABOUT:     Print Information about the ZiZoyaOS including Dev Experience\n");
            vga_print("CALC:      Enter Shell Mode CALC(Calculator)\n");
            vga_print("CLRINT:    Clear Interrupts\n");
            vga_print("CLRSCRN:   Clear the Screen\n");
            vga_print("DRAW:      Enter Shell Mode DRAW(Drawing)\n");
            vga_print("HALT:      Halt/Stop the CPU\n");
            vga_print("MEMALLOC:  Allocate Memory and Show the Physical Address\n");
            vga_print("SETINT:    Set Interrupts\n");
            vga_print("TIMER:     Enable Timer(Install TIMER IRQ) and Show Timer 'Ticking' (for total             100 ticks)\n");
        }else{
            vga_print(input);
            vga_print(": ");
            vga_print("Unknown Command in Shell Mode NORMAL.");
        }
    }else if(shell_mode == 1){
        if(zzylib_strcmp(input, "COMPUTE") == 0) {
            vga_print("Missing Expression. You need an expression to COMPUTE.");
        }else if(zzylib_strcmp(input, "CLRSCRN") == 0){
            vga_clear_screen();
        }else if(zzylib_strcmp(input, "QUIT") == 0){
            shell_mode = 0;
            vga_print("Quitted Shell Mode CALC. Entered Shell Mode NORMAL. Type and enter 'HELP' to see options and commands.");
        }else if(is_COMPUTE(input) == 1){
            computation_routine(input);
        }else if(zzylib_strcmp(input, "HELP") == 0){
            vga_print("\n");
            vga_print("Available Commands in MODE CALC: \n");
            vga_print("\n");
            vga_print("*COMPUTE:  Compute the result of the expression. Available Type(s): Integer.               Available Operators: +,-,*,/,^,&,|. Usage: COMPUTE expression.                  Examples: COMPUTE 2*3, COMPUTE 56|6\n");
            vga_print("CLRSCRN:   Clear the Screen\n");
            vga_print("QUIT:      Quit Shell Mode CALC and Enter Mode NORMAL\n");
        }else{
            vga_print(input);
            vga_print(": ");
            vga_print("Unknown Command in Shell Mode CALC(Calculator).");
        }
    }else if(shell_mode == 2){
        if(zzylib_strcmp(input, "OSLOGO") == 0) {
            vga_print("\n");
            vga_print("   ********************************************************\n");
            vga_print("  * *****   ***   *****  *****  *   *    *    *****  ***** *\n");
            vga_print(" *     *     *       *   *   *   * *    * *   *   *  *      *\n");
            vga_print("*     *      *      *    *   *    *    *****  *   *  *****   *\n");
            vga_print(" *   *       *     *     *   *    *    *   *  *   *      *  *\n");
            vga_print("  * *****   ***   *****  *****    *    *   *  *****  ***** *\n");
            vga_print("   ********************************************************     by c0zzyde\n");
        }else if(zzylib_strcmp(input, "QUIT") == 0){
            shell_mode = 0;
            vga_print("Quitted Shell Mode DRAW. Entered Shell Mode NORMAL. Type and enter 'HELP' to see options and commands.");
        }else if(zzylib_strcmp(input, "CLRSCRN") == 0){
            vga_clear_screen();
        }else if(zzylib_strcmp(input, "HELP") == 0){
            vga_print("\n");
            vga_print("Available Commands in MODE DRAW: \n");
            vga_print("\n");
            vga_print("OSLOGO:    Draw(Print) the ZiZoyaOS Logo on the Screen\n");
            vga_print("CLRSCRN:   Clear the Screen\n");
            vga_print("QUIT:      Quit Shell Mode DRAW and Enter Mode NORMAL\n");
        }else{
            vga_print(input);
            vga_print(": ");
            vga_print("Unknown Command in Shell Mode DRAW(Drawing).");
        }
    }
}


/*
ABCDEFGHIJKLMNOPQRSTUVWXYZ
*/

int is_COMPUTE(char* thisstr){
    int count = 1;
    char sevenchs[10];
    while((*thisstr != '\0')&&(count <= 8)){
        zzylib_append(sevenchs, *thisstr);
        thisstr = thisstr + 1;
        count = count + 1;
    }
    //zzylib_append(sevenchs, '\0');
    if(zzylib_strcmp(sevenchs, "COMPUTE ") == 0){
        return 1;
    }else{
        return 0;
    }
}

void computation_routine(char* string){
    int count = 1;
    char expression[80] = "";
    while(*string != '\0'){
        if(count > 8){
            zzylib_append(expression, *string);
            string = string + 1;
            count = count + 1;
        }else{
            string = string + 1;
            count = count + 1;
        }
    }
    int index = 0;
    int first_num_exist = 0;
    int op_exist = 0;
    int exp_end = 0;
    char num1temp[20] = "";
    char optemp[2] = "";
    char num2temp[20] = ""; 
    while(expression[index] != '\0'){
        if((exp_end == 0)&&(op_exist == 0)&&(first_num_exist == 0)&&(is_num(expression[index]) == 1)){
            zzylib_append(num1temp, expression[index]);
        }else if((exp_end == 0)&&(op_exist == 0)&&(first_num_exist == 0)&&(is_op(expression[index]) == 1)){
            first_num_exist = 1;
            zzylib_append(optemp, expression[index]);
            op_exist = 1;
        }else if((exp_end == 0)&&(op_exist == 1)&&(first_num_exist == 1)&&(is_num(expression[index]) == 1)){
            zzylib_append(num2temp, expression[index]);
        }else if((exp_end == 0)&&(op_exist == 1)&&(first_num_exist == 1)&&(is_num(expression[index]) == 0)){
            exp_end = 1;
        }
        index = index + 1;
    }
    //vga_print(num1temp);
    //vga_print("\n");
    //vga_print(optemp);
    //vga_print("\n");
    //vga_print(num2temp);
    if((str_is_num(num1temp) == 1)&&(str_is_num(num2temp) == 1)&&(zzylib_strlen(num1temp) > 0)&&(zzylib_strlen(num2temp) > 0)){
        int num1 = zzylib_atoi(num1temp);
        int num2 = zzylib_atoi(num2temp);
        int result = 0;
        if(zzylib_strcmp(optemp, "+") == 0){
            result = num1 + num2;
            char resultstr[80];
            zzylib_itoa(result, resultstr);
            vga_print(resultstr);
            vga_print("\n");
        }else if(zzylib_strcmp(optemp, "-") == 0){
            result = num1 - num2;
            char resultstr[80];
            zzylib_itoa(result, resultstr);
            vga_print(resultstr);
            vga_print("\n");
        }else if(zzylib_strcmp(optemp, "*") == 0){
            result = num1 * num2;
            char resultstr[80];
            zzylib_itoa(result, resultstr);
            vga_print(resultstr);
            vga_print("\n");
        }else if(zzylib_strcmp(optemp, "/") == 0){
            if(num2 == 0){
                vga_print("***CALC MODE ERROR: DIVISION BY ZERO***\n");
                vga_print("***ZIZOYA_KERNEL_SHELL WILL NOT LET CPU CALCULATE EXPRESSION CONTAINS DIVISION BY ZERO***\n");
            }else{
                result = num1 / num2;
                char resultstr[80];
                zzylib_itoa(result, resultstr);
                vga_print(resultstr);
                vga_print("\n");
            }
        }else if(zzylib_strcmp(optemp, "^") == 0){
            int result = 1;
            int i = 0;
            for(i = 0; i < num2; i++){
                result = result * num1;
            }
            char resultstr[80];
            zzylib_itoa(result, resultstr);
            vga_print(resultstr);
            vga_print("\n");
        }else if(zzylib_strcmp(optemp, "&") == 0){
            result = num1 & num2;
            char resultstr[80];
            zzylib_itoa(result, resultstr);
            vga_print(resultstr);
            vga_print("\n");
        }else if(zzylib_strcmp(optemp, "|") == 0){
            result = num1 | num2;
            char resultstr[80];
            zzylib_itoa(result, resultstr);
            vga_print(resultstr);
            vga_print("\n");
        }else{
            vga_print("***INVALID EXPRESSION***\n");
        }
    }else{
        vga_print("***INVALID EXPRESSION***\n");
    }
}


int str_is_num(char* str){
    while(*str != '\0'){
        if(is_num(*str) == 0){
            return 0;
        }
        str = str + 1;
    }
    return 1;
}


int is_num(char ch){
    if((ch == '0')||(ch == '1')||(ch == '2')||(ch == '3')||(ch == '4')||(ch == '5')||(ch == '6')||(ch == '7')||(ch == '8')||(ch == '9')){
        return 1;
    }else{
        return 0;
    }
}

int is_op(char ch){
    if((ch == '+')||(ch == '-')||(ch == '*')||(ch == '/')||(ch == '^')||(ch == '&')||(ch == '|')){
        return 1;
    }else{
        return 0;
    }
}