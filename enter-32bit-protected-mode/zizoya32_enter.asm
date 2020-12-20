[org 0x7c00]

start:

    mov bp , 0x9000  ; set stack
    mov sp , bp
    call clear_screen_16bit
    mov si , MSG_16bit_REALMODE_BOOTING
    call print_string_16bit
    call switch_to_pm ; start entering into 32bit protected mode

    MSG_16bit_REALMODE_BOOTING db "Hello, ZizoyaOS is booting in 16BIT-REAL-MODE...Please Wait...", 0


%include "zizoya16_print_string.asm"
%include "zizoya32_print_string.asm"
%include "zizoya32_gdt.asm"
%include "zizoya16to32.asm"
%include "zizoya16_clear_screen.asm"

[bits 32]
BEGIN_PM:               ; be called in zizoya16to32.asm(after the switch)

    mov ebx , MSG_32bit_PROTECTEDMODE_BOOTING
    call print_string_32bit
    jmp $

    MSG_32bit_PROTECTEDMODE_BOOTING db ">>>>>>ZizoyaOS successfully entered 32BIT-PROTECTED-MODE>>>>>>", 0


times 510 -($-$$) db 0
dw 0xaa55