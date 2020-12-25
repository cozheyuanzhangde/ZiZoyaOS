#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define COLOR_WHITEONBLACK 0x0f
#define COLOR_REDONWHITE 0xf4

#define VGA_CONTROL 0x3d4   //write/request
#define VGA_DATA 0x3d5      //read/get

void vga_clear_screen();
void vga_print_at(char* string, int col, int row);
void vga_print(char* string);