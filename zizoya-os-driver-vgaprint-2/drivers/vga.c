#include "vga.h"
#include "ports.h"

//pre-declarations
int get_cursor_offset();
void set_cursor_offset(int offset);
int print_char(char c, int col, int row, char attr);
int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);

//PRIVATE functions for kernel (not in vga.h header file)

int get_offset(int col, int row) {
    return 2 * (row * MAX_COLS + col);
}

int get_offset_row(int offset) { 
    return offset / (2 * MAX_COLS); 
}

int get_offset_col(int offset) { 
    return (offset - (get_offset_row(offset)*2*MAX_COLS))/2; 
}

int print_char(char c, int col, int row, char attr) {
    unsigned char* vidmem = (unsigned char*) VIDEO_ADDRESS;
    if (!attr) attr = COLOR_WHITEONBLACK;     //default

    //if across boundary: print a red 'E'
    if (col >= MAX_COLS || row >= MAX_ROWS) {
        vidmem[2*(MAX_COLS)*(MAX_ROWS)-2] = 'E';
        vidmem[2*(MAX_COLS)*(MAX_ROWS)-1] = COLOR_REDONWHITE;
        return get_offset(col, row);
    }

    int offset;
    if (col >= 0 && row >= 0) offset = get_offset(col, row);
    else offset = get_cursor_offset();

    if (c == '\n') {                   //set newline escape character
        row = get_offset_row(offset);
        offset = get_offset(0, row+1);
    } else {
        vidmem[offset] = c;
        vidmem[offset+1] = attr;
        offset += 2;
    }
    set_cursor_offset(offset);
    return offset;
}

int get_cursor_offset() {
    //use ports.c get the cursor high byte and low byte
    port_byte_out(VGA_CONTROL, 14);    //request high byte
    int offset = port_byte_in(VGA_DATA) << 8;
    port_byte_out(VGA_CONTROL, 15);    //request low byte
    offset += port_byte_in(VGA_DATA);
    return offset * 2; //size of character cell = 2 therefore multiply 2
}

void set_cursor_offset(int offset) {
    //similar as above but this time write
    offset /= 2;
    port_byte_out(VGA_CONTROL, 14);
    port_byte_out(VGA_DATA, (unsigned char)(offset >> 8));   //write high byte
    port_byte_out(VGA_CONTROL, 15);
    port_byte_out(VGA_DATA, (unsigned char)(offset & 0xff)); //write low byte
}

//PUBLIC functions for kernel
void vga_clear_screen() {
    int screen_size = MAX_COLS * MAX_ROWS; //total cells
    int i;
    char* screen = (char*) VIDEO_ADDRESS;

    for (i = 0; i < screen_size; i++) {      //loop through all cells
        screen[i*2] = ' ';                   //character content - blank in this case
        screen[i*2+1] = COLOR_WHITEONBLACK;  //character attribute
    }
    set_cursor_offset(get_offset(0, 0));     //set cursor to 0,0
}

void vga_print_at(char* string, int col, int row) {
    int offset;
    if (col >= 0 && row >= 0)
        offset = get_offset(col, row);
    else {                              //if col or row is negative (which means is invalid)
        offset = get_cursor_offset();   //print in the position of cursor
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }

    int i = 0;
    while (string[i] != 0) {            //traverse the string as chars and print them
        offset = print_char(string[i++], col, row, COLOR_WHITEONBLACK);
        row = get_offset_row(offset);   //update row
        col = get_offset_col(offset);   //update col
    }
}

void vga_print(char* string) {
    vga_print_at(string, -1, -1);     //wrapper function: print in the position of cursor
}