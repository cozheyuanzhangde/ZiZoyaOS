## Differences from previous version:
1. kernel function only executes main(), which not from the first line of the kernel.c because extra code in kernel_entry.asm specifies it.