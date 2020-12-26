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