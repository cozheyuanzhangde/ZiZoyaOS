[bits 16]           ; 16-bit mode
[org 0x7c00]        ; 0x7c00 is the BIOS load memory location


start:


    xor ax,ax           ; set ax to 0: xor: output 1 only when different bits --- 0 xor 1 or 1 xor 0
    mov ds,ax           ; set ds to 0
    mov es,ax           ; set es to 0
    mov bx,0x8000       ; memory location above 0x7c00
    
    call clear_screen   ; clear pre-load info


    mov si, hello_world              ; point hello_world to si
    call print_string                ; call print different color string function



    hello_world db  '------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------Hello, ZizoyaOS is booting...-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------',0
    ;define/declare bytes for hello_world, use 0 as null terminator

%include "print_string.asm"
%include "clear_screen.asm"

times (510 - ($ - $$)) db 0x00     ; fill up to 512 bytes
dw 0xAA55                          ; boot-sector signature "magic number" 0xAA & 0x55