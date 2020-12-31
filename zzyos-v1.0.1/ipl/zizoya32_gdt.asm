;GDT structure for ZiZoyaOS entering 32bit protected mode.
gdt_start:

gdt_null:
    dd 0x0       ;dd: define/declare double word - 4bytes
    dd 0x0

gdt_code:
    dw 0xffff    ;dw: define/declare word - 2bytes
    dw 0x0
    db 0x0       ;db: define/declare byte - 1byte
    db 10011010b ;1st flags
    db 11001111b ;2nd flags
    db 0x0

gdt_data:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b ;1st flags
    db 11001111b ;2nd flags
    db 0x0

gdt_end:         ;this label made easy for calculate the size of the GDT

gdt_descriptor:
    dw gdt_end - gdt_start - 1     ;size of GDT
    dd gdt_start                   ;start address of GDT

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start