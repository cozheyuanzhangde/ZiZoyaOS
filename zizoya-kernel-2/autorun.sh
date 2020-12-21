nasm -f bin zizoya32_main.asm -o zizoya32_main.bin
nasm kernel_entry.asm -f elf -o kernel_entry.o
gcc -m32 -fno-pie -ffreestanding -c kernel.c -o kernel.o
ld -m elf_i386 -s -o kernel.bin -Ttext 0x1000 kernel_entry.o kernel.o --oformat binary
cat zizoya32_main.bin kernel.bin > ZizoyaOS.bin
qemu-system-i386 -fda ZizoyaOS.bin
