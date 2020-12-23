[bits 32]
[extern main] ; execute kernel in intended entry function main
call main ; call main() in kernel
jmp $
