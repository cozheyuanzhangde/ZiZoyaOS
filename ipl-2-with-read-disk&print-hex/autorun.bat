nasm -f bin ipl2.asm -o ipl2.bin
qemu-system-x86_64 -fda ipl2.bin