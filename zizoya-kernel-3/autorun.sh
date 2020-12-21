nasm -f bin zizoya32_main.asm -o zizoya32_main.bin
nasm zizoya32_kernel_entry.asm -f elf -o zizoya32_kernel_entry.o
gcc -m32 -fno-pic -ffreestanding -c zizoya_kernel.c -o zizoya_kernel.o
ld -m elf_i386 -s -o zizoya_kernel.bin -Ttext 0x1000 zizoya32_kernel_entry.o zizoya_kernel.o --oformat binary
cat zizoya32_main.bin zizoya_kernel.bin > ZizoyaOS.bin
qemu-system-i386 -fda ZizoyaOS.bin
