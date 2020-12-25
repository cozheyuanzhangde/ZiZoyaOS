nasm -f bin ipl/zizoya32_main.asm -o output/zizoya32_main.bin
nasm ipl/zizoya32_kernel_entry.asm -f elf -o output/zizoya32_kernel_entry.o
nasm low-level/interrupt.asm -f elf -o output/interrupt.o
gcc -m32 -fno-pic -ffreestanding -c kernel/zizoya_kernel.c -o output/zizoya_kernel.o
gcc -m32 -fno-pic -ffreestanding -c drivers/ports.c -o output/ports.o
gcc -m32 -fno-pic -ffreestanding -c drivers/vga.c -o output/vga.o
gcc -m32 -fno-pic -ffreestanding -c kernel/zizoya_util.c -o output/zizoya_util.o
gcc -m32 -fno-pic -ffreestanding -c low-level/idt.c -o output/idt.o
gcc -m32 -fno-pic -ffreestanding -c low-level/isr.c -o output/isr.o
ld -m elf_i386 -s -o output/zizoya_kernel.bin -Ttext 0x1000 output/zizoya32_kernel_entry.o output/zizoya_kernel.o output/ports.o output/vga.o output/zizoya_util.o output/idt.o output/isr.o output/interrupt.o --oformat binary
cat output/zizoya32_main.bin output/zizoya_kernel.bin > output/ZizoyaOS.bin
qemu-system-i386 -fda output/ZizoyaOS.bin
