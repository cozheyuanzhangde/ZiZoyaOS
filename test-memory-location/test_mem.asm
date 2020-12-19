mov ah, 0x0e ; Write #0x0E instruction for int 0x10

mov al, "1"           ;this will not work because SUCCESS is a memory location, cannot be printed.
int 0x10
mov al, SUCCESS
int 0x10

mov al, "2"           ;this will not work because SUCCESS is a "relative address" which cannot be read as the ipl starts from 0x7c00.
int 0x10
mov al, [SUCCESS]
int 0x10

mov al, "3"           ;this will work. (Added 0x7c00)
int 0x10
mov bx, SUCCESS
add bx, 0x7c00
mov al, [bx]
int 0x10

mov al, "4"           ;this will work.
int 0x10
mov al, [0x7c2d]
int 0x10


jmp $ ; infinite loop / jump to current location

SUCCESS:
    db "S"

times 510-($-$$) db 0
dw 0xaa55