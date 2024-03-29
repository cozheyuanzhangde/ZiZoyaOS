//ZizoyaOS-Kernel(zzyk)-utilities
void zzyk_memcpy(char* source, char* dest, int size) {
    int i;
    for (i = 0; i < size; i++) {
        *(dest + i) = *(source + i);
    }
}

void zzyk_memset(unsigned char* dest, unsigned char val, unsigned int len) {
    unsigned char* destptr = (unsigned char*) dest;
    int i;
    for (i = len; i != 0; i--) {
        *destptr++ = val;
    }
}

void zzyk_itoa(int n, char str[]) {
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';
}