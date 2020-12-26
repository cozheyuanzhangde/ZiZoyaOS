; VGA(Video Graphics Array) colour text mode in 32bit protected mode
[bits 32]

VIDEO_MEMORY equ 0xb8000   ;define/declare constant VIDEO_MEMORY
COLOR_WHITEONBLACK equ 0x0f    ;define/declare constant WHITE_ON_BLACK(color)

print_string_32bit:
    pusha
    mov edx, VIDEO_MEMORY

print_string_32bit_loop:
    mov al, [ebx]               ;store char at ebx into al
    mov ah, COLOR_WHITEONBLACK  ;store the color constant into ah

    cmp al, 0                   ; check end of string using null terminator
    je print_string_32bit_done  ; if meet null terminator, jump to done(finished)

    mov [edx], ax
    add ebx, 1      ; next char
    add edx, 2      ; next video memory

    jmp print_string_32bit_loop  ; loop to print the next char...

print_string_32bit_done:
    popa
    ret