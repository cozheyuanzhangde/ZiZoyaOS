#include "../drivers/vga.h"

void main() {
    //vga_clear_screen();
	vga_print("\n");
	vga_print("If you saw this message, congratulations! That means the kernel has been loaded. helloworld_helloworld_helloworld");
	vga_print("\n");
	vga_print("Also, VGA driver runs successfully.");
	vga_print_at("NotEnoughNotEnoughNotEnoughNotEnoughNotEnough", 47, 24);
}
