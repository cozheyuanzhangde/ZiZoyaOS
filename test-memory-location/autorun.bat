nasm -f bin test_mem.asm -o test_mem.bin
qemu-system-x86_64 test_mem.bin