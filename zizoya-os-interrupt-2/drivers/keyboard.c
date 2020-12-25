#include "keyboard.h"
#include "ports.h"
#include "../low-level/isr.h"
#include "vga.h"

static void keyboard_callback(registers_t regs) {
    unsigned char scancode = port_byte_in(0x60);
    char *sc_ascii;
    zzyk_itoa(scancode, sc_ascii);
    vga_print("Keyboard scancode: ");
    vga_print(sc_ascii);
    vga_print(", ");
    print_letter(scancode);
    vga_print("\n");
}

void init_keyboard() {
   register_interrupt_handler(IRQ1, keyboard_callback); 
}

void print_letter(unsigned char scancode) {
    switch (scancode) {
        case 0x0:
            vga_print("ERROR");
            break;
        case 0x1:
            vga_print("ESC");
            break;
        case 0x2:
            vga_print("1");
            break;
        case 0x3:
            vga_print("2");
            break;
        case 0x4:
            vga_print("3");
            break;
        case 0x5:
            vga_print("4");
            break;
        case 0x6:
            vga_print("5");
            break;
        case 0x7:
            vga_print("6");
            break;
        case 0x8:
            vga_print("7");
            break;
        case 0x9:
            vga_print("8");
            break;
        case 0x0A:
            vga_print("9");
            break;
        case 0x0B:
            vga_print("0");
            break;
        case 0x0C:
            vga_print("-");
            break;
        case 0x0D:
            vga_print("+");
            break;
        case 0x0E:
            vga_print("Backspace");
            break;
        case 0x0F:
            vga_print("Tab");
            break;
        case 0x10:
            vga_print("Q");
            break;
        case 0x11:
            vga_print("W");
            break;
        case 0x12:
            vga_print("E");
            break;
        case 0x13:
            vga_print("R");
            break;
        case 0x14:
            vga_print("T");
            break;
        case 0x15:
            vga_print("Y");
            break;
        case 0x16:
            vga_print("U");
            break;
        case 0x17:
            vga_print("I");
            break;
        case 0x18:
            vga_print("O");
            break;
        case 0x19:
            vga_print("P");
            break;
		case 0x1A:
			vga_print("[");
			break;
		case 0x1B:
			vga_print("]");
			break;
		case 0x1C:
			vga_print("ENTER");
			break;
		case 0x1D:
			vga_print("LCtrl");
			break;
		case 0x1E:
			vga_print("A");
			break;
		case 0x1F:
			vga_print("S");
			break;
        case 0x20:
            vga_print("D");
            break;
        case 0x21:
            vga_print("F");
            break;
        case 0x22:
            vga_print("G");
            break;
        case 0x23:
            vga_print("H");
            break;
        case 0x24:
            vga_print("J");
            break;
        case 0x25:
            vga_print("K");
            break;
        case 0x26:
            vga_print("L");
            break;
        case 0x27:
            vga_print(";");
            break;
        case 0x28:
            vga_print("'");
            break;
        case 0x29:
            vga_print("`");
            break;
		case 0x2A:
			vga_print("LShift");
			break;
		case 0x2B:
			vga_print("\\");
			break;
		case 0x2C:
			vga_print("Z");
			break;
		case 0x2D:
			vga_print("X");
			break;
		case 0x2E:
			vga_print("C");
			break;
		case 0x2F:
			vga_print("V");
			break;
        case 0x30:
            vga_print("B");
            break;
        case 0x31:
            vga_print("N");
            break;
        case 0x32:
            vga_print("M");
            break;
        case 0x33:
            vga_print(",");
            break;
        case 0x34:
            vga_print(".");
            break;
        case 0x35:
            vga_print("/");
            break;
        case 0x36:
            vga_print("Rshift");
            break;
        case 0x37:
            vga_print("Keypad *");
            break;
        case 0x38:
            vga_print("LAlt");
            break;
        case 0x39:
            vga_print("Spc");
            break;
        default:
            if (scancode <= 0x7f) {
                vga_print("Unknown key down");
            } else if (scancode <= 0x39 + 0x80) {
                vga_print("key up ");
                print_letter(scancode - 0x80);
            } else {
                vga_print("Unknown key up");
            }
            break;
    }
}