[bits 16]           ; tell assembler that working in real mode(16 bit mode)
[org 0x7c00]        ; organize from 0x7C00 memory location where BIOS will load us


start:              ; start label from where our code starts

    xor ax,ax           ; set ax register to 0
    mov ds,ax           ; set data segment(ds) to 0
    mov es,ax           ; set extra segment(es) to 0
    mov bx,0x8000


    ;mov si, hello_world              ; point hello_world to source index
    ;call print_string                ; call print different color string function
    call DispStr
    jmp $ ; and loop forever



    hello_world db 'Hello ZiZoyaOS!',13,0


DispStr:
    mov ah,9
    mov al,"hwiqewopoeqwqeoq"
    mov bh,0
    mov bl,4
    mov cx,1
    int 10h


print_string:
    mov ah, 0x0E  ; Write instruction for int 0x10

.repeat_next_char:
    lodsb                        ; Load byte at address SI into AL
    cmp al, 0                    ; cmp al with end of string
    je .done_print               ; je: jump if equal
    int 0x10                     ; else: print character
    jmp .repeat_next_char        ; jmp to .repeat_next_char if not 0

.done_print:
    ret

    times (510 - ($ - $$)) db 0x00     ;fill 512 bytes
    dw 0xAA55