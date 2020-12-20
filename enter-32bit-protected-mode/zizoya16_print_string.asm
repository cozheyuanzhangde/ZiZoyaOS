print_string_16bit:
    mov ah, 0x0E                 ; Write #0x0E instruction for int 0x10

.repeat_next_char:
    lodsb                        ; Load byte at address SI into AL
    cmp al, 0                    ; cmp al with end of string
    je .finish_print             ; je: jump to .done_print if equal
    int 0x10                     ; else: call BIOS function 0x10 to print char in al
    jmp .repeat_next_char        ; print recursively

.finish_print:
    ret