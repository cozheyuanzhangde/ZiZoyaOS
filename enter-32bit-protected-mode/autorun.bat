nasm -f bin zizoya32_enter.asm -o zizoya32_enter.bin
qemu-system-x86_64 -fda zizoya32_enter.bin