nasm -f bin test_stack.asm -o test_stack.bin
qemu-system-x86_64 test_stack.bin