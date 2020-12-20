;Segment registers: cs,ds,ss,es
;This test may look quite similar to test_mem but this time, we not
;add 0x7c0 to the address, instead, we use ds(data segment) register
;to achieve it. (segmentation is basically using offset)
;If we set the ds register to 0x7c0, CPU will do this offset:
;0x7c0 * 16 + SUCCESS
;(when we shift a number by 16, in hex, it will shift a digit to the left, for example, 0x7c0*16=0x7c00, then we can add...)
mov ah, 0x0e ; Write #0x0E instruction for int 0x10

mov al, "1"        ; this will not work because haven't set ds register
int 0x10
mov al, [SUCCESS]
int 0x10

mov al, "2"        ; this will work.
int 0x10
mov bx, 0x7c0
mov ds, bx
mov al, [SUCCESS]
int 0x10

mov al, "3"        ; this will not work because we haven't set es register to 0x7c00. but [es:SUCCESS] tell the CPU to use the es (not ds) register. We need to set it again.
int 0x10
mov al, [es:SUCCESS]
int 0x10

mov al, "4"        ; this will work because we set the es register to 0x7c00.
int 0x10
mov bx, 0x7c0
mov es, bx
mov al, [es:SUCCESS]
int 0x10


jmp $ ; infinite loop / jump to current location

SUCCESS:
    db "S"

times 510-($-$$) db 0
dw 0xaa55