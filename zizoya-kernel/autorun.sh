nasm -f bin zizoya32_main.asm -o zizoya32_main.bin
gcc -ffreestanding -c kernel.c -o kernel.o
ld -o kernel.bin -Ttext 0x1000 kernel.o --oformat binary
cat zizoya32_main.bin kernel.bin > ZizoyaOS
qemu-system-x86_64 -fda ZizoyaOS
