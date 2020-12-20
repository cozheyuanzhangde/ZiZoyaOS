nasm -f bin test_seg.asm -o test_seg.bin
qemu-system-x86_64 test_seg.bin