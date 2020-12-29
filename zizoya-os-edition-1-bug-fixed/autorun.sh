nasm -f bin ipl/zizoya32_main.asm -o output/zizoya32_main.bin
nasm ipl/zizoya32_kernel_entry.asm -f elf -o output/zizoya32_kernel_entry.o
nasm low-level/interrupt.asm -f elf -o output/interrupt.o
gcc -m32 -fno-pic -ffreestanding -c kernel/zizoya_kernel.c -o output/zizoya_kernel.o
gcc -m32 -fno-pic -ffreestanding -c low-level/ports.c -o output/ports.o
gcc -m32 -fno-pic -ffreestanding -c drivers/vga.c -o output/vga.o
gcc -m32 -fno-pic -ffreestanding -c low-level/idt.c -o output/idt.o
gcc -m32 -fno-pic -ffreestanding -c low-level/isr.c -o output/isr.o
gcc -m32 -fno-pic -ffreestanding -c low-level/timer.c -o output/timer.o
gcc -m32 -fno-pic -ffreestanding -c drivers/keyboard.c -o output/keyboard.o
gcc -m32 -fno-pic -ffreestanding -c library/memory.c -o output/memory.o
gcc -m32 -fno-pic -ffreestanding -c library/string.c -o output/string.o
ld -m elf_i386 -s -o output/zizoya_kernel.bin -Ttext 0x7e00 output/zizoya32_kernel_entry.o output/zizoya_kernel.o output/ports.o output/vga.o output/idt.o output/isr.o output/interrupt.o output/timer.o output/keyboard.o output/memory.o output/string.o --oformat binary
cat output/zizoya32_main.bin output/zizoya_kernel.bin > output/ZizoyaOS.bin
qemu-system-i386 -fda output/ZizoyaOS.bin
