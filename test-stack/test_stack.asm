mov ah, 0x0e ; Write #0x0E instruction for int 0x10

mov bp, 0x8000

push 'A'
;current stack:
;A
push 'B'
;current stack:
;B
;A
push 'C'
;current stack:
;C
;B
;A

pop bx
mov al, bl
int 0x10
;current stack:
;B
;A

pop bx
mov al, bl
int 0x10
;current stack:
;A

pop bx
mov al, bl
int 0x10

jmp $    ; infinite loop / jump to current location

times 510-($-$$) db 0
dw 0xaa55