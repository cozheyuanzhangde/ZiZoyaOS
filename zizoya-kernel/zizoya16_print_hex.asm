print_hex_16bit:
    pusha
    mov cx, 0

; manipulate chars at hexoutput
hex_loop:
    cmp cx, 4
    je end   
    mov ax, dx
    and ax, 0x000f
    add al, 0x30
    cmp al, 0x39
    jle step2
    add al, 7

step2:
    mov bx, hexoutput + 5
    sub bx, cx
    mov [bx], al
    ror dx, 4
    add cx, 1
    jmp hex_loop

end:
    mov si, hexoutput
    call print_string_16bit
    popa
    ret

hexoutput:
    db '0x0000',0
