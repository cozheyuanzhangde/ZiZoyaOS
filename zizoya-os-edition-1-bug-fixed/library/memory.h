#ifndef LIB_MEM
#define LIB_MEM

void zzylib_memcpy(char* source, char* dest, int size);
void zzylib_memset(unsigned char* dest, unsigned char val, unsigned int len);
unsigned int zzylib_memalloc(unsigned int size, int align, unsigned int *phys_addr);

#endif