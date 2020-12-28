global _start
[bits 32]

_start:
    [extern kernel_main] ; define calling point
    call kernel_main ; calls kernel main function
    jmp $