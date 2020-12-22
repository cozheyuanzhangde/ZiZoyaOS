[org 0x7c00]

KERNEL_OFFSET equ 0x1000    ; kernel load memory offset

start:
    
    mov [BOOTDRIVE], dl ; store boot drive in dl
    mov bp , 0x9000  ; set stack
    mov sp , bp
    call clear_screen_16bit
    mov si , MSG_16bit_REALMODE_BOOTING
    call print_string_16bit
    call load_kernel
    call switch_to_pm ; start entering into 32bit protected mode

    MSG_16bit_REALMODE_BOOTING db "Hello, ZizoyaOS is booting in 16BIT-REAL-MODE...Please Wait...", 0


%include "ipl/zizoya16_print_string.asm"
%include "ipl/zizoya32_print_string.asm"
%include "ipl/zizoya32_gdt.asm"
%include "ipl/zizoya16to32.asm"
%include "ipl/zizoya16_clear_screen.asm"
%include "ipl/zizoya16_print_hex.asm"
%include "ipl/zizoya16_read_disk.asm"

[bits 16]
load_kernel:
    mov si, MSG_LOAD_ZizoyaKernel
    call print_string_16bit
    mov bx, KERNEL_OFFSET
    mov dh, 15
    mov dl, [BOOTDRIVE]
    call disk_load_16bit

    ret

    MSG_LOAD_ZizoyaKernel db "ZizoyaOS is loading the kernel...", 0

[bits 32]
BEGIN_PM:               ; be called in zizoya16to32.asm(after the switch)

    mov ebx , MSG_32bit_PROTECTEDMODE_BOOTING
    call print_string_32bit
    call KERNEL_OFFSET
    jmp $

    MSG_32bit_PROTECTEDMODE_BOOTING db ">>>>>>ZizoyaOS successfully entered 32BIT-PROTECTED-MODE>>>>>>", 0


BOOTDRIVE db 0

times 510 -($-$$) db 0
dw 0xaa55
