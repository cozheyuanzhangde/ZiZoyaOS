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
    ;define/declare bytes for hello_world

print_string:
    mov ah, 0x0E            ; Write #0x0E instruction for int 0x10

.repeat_next_char:
    lodsb                        ; Load byte at address SI into AL
    cmp al, 0                    ; cmp al with end of string
    je .finish_print             ; je: jump to .done_print if equal
    int 0x10                     ; else: call BIOS function 0x10 to print char in al
    jmp .repeat_next_char        ; print recursively

.finish_print:
    ret

clear_screen:                ; function for clear pre-load info including BIOS info  
    mov    ah, 0x06          ; Write #0x06 instruction for int 0x10 
    mov    al, 0 
    mov    ch, 0
    mov    ch, 0    
    mov    dh, 24 
    mov    dl, 79
    mov    bh, 0x07  
    int 0x10  
    ret  

times (510 - ($ - $$)) db 0x00     ; fill up to 512 bytes
dw 0xAA55                          ; boot-sector signature "magic number" 0xAA & 0x55