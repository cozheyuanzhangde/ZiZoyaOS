nasm -f bin ipl/zizoya32_main.asm -o output/zizoya32_main.bin
nasm ipl/zizoya32_kernel_entry.asm -f elf -o output/zizoya32_kernel_entry.o
gcc -m32 -fno-pic -ffreestanding -c kernel/zizoya_kernel.c -o output/zizoya_kernel.o
gcc -m32 -fno-pic -ffreestanding -c drivers/ports.c -o output/ports.o
ld -m elf_i386 -s -o output/zizoya_kernel.bin -Ttext 0x1000 output/zizoya32_kernel_entry.o output/zizoya_kernel.o output/ports.o --oformat binary
cat output/zizoya32_main.bin output/zizoya_kernel.bin > output/ZizoyaOS.bin
qemu-system-i386 -fda output/ZizoyaOS.bin
