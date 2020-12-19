[org 0x7c00]
mov [bootdrive], dl ; store boot drive in dl
mov bp , 0x8000 ; set stack
mov sp , bp
mov bx , 0x9000
mov dh , 5
mov dl , [bootdrive]
call disk_load
mov dx , [0x9000]       ; read first sector
call print_hex          ; it should print 0x0123
mov si, newline
call print_string
mov dx , [0x9000 + 512] ; read second sector
call print_hex          ; it should print 0x4567
mov si, newline
call print_string
mov dx , [0x9000 + 1024] ; read third sector
call print_hex          ; it should print 0x89ab
jmp $
bootdrive : db 0
newline db '', 0xd, 0xa, 0 ;0xd: let cursor go to hard left, 0xa: newline
%include "print_string.asm"
%include "print_hex.asm"
%include "read_disk.asm"
times 510 -($-$$) db 0
dw 0xaa55
;two additional sectors we want to read:
times 256 dw 0x0123     ; dw: define word, which is 8 bits(2 bytes), 2*256 = 512bytes
times 256 dw 0x4567     ; dw: define word, which is 8 bits(2 bytes), 2*256 = 512bytes
times 256 dw 0x89ab     ; dw: define word, which is 8 bits(2 bytes), 2*256 = 512bytes