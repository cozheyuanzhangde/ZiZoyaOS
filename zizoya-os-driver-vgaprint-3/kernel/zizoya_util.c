//ZizoyaOS-Kernel(zzyk)-utilities
void zzyk_memcpy(char* source, char* dest, int size) {
    int i;
    for (i = 0; i < size; i++) {
        *(dest + i) = *(source + i);
    }
}