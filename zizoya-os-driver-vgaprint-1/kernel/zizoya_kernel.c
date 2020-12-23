#include "../drivers/ports.h"

//VGA control register: 0x3d4 for write/request, 0x3d5 for read/get.
//high byte of cursor: 14
//low byte of cursor: 15
void main() {
	port_byte_out(0x3d4, 14);   //request high byte
	int position = port_byte_in(0x3d5);   //get position from VGA
	position = position << 8;

	port_byte_out(0x3d4, 15);   //request low byte
	position += port_byte_in(0x3d5);    //get position from VGA

	int offset_from_vga = position * 2;

	char* vga = (char*) 0xb8000;
	vga[offset_from_vga] = 'B'; 
	vga[offset_from_vga+1] = 0x0f;   //white on black
}
