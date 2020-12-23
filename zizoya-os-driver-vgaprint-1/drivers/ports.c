unsigned char port_byte_in (unsigned short port) {
	//read result(byte) from a specified port
        unsigned char result;
        __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
        return result;
}

void port_byte_out (unsigned short port, unsigned char data) {
	//write data(byte) to a specified port
	__asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

unsigned short port_word_in (unsigned short port) {
	//read result(word) to a specified port
	unsigned short result;
	__asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
	return result;
}

void port_word_out (unsigned short port, unsigned short data) {
	//write data(word) to a specified port
	__asm__("out %%ax, %%dx" : : "a" (data), "d" (port));
}
