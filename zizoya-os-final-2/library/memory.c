#include "memory.h"

void zzylib_memcpy(char* source, char* dest, int size) {
    int i;
    for (i = 0; i < size; i++) {
        *(dest + i) = *(source + i);
    }
}

void zzylib_memset(unsigned char* dest, unsigned char val, unsigned int len) {
    unsigned char* destptr = (unsigned char*) dest;
    int i;
    for (i = len; i != 0; i--) {
        *destptr++ = val;
    }
}

unsigned int free_mem_addr = 0x10000;

unsigned int zzylib_memalloc(unsigned int size, int align, unsigned int *phys_addr) {
    if (align == 1 && (free_mem_addr & 0xFFFFF000)) {
        free_mem_addr &= 0xFFFFF000;
        free_mem_addr += 0x1000;
    }
    if (phys_addr) *phys_addr = free_mem_addr;

    unsigned int ret = free_mem_addr;
    free_mem_addr += size;
    return ret;
}