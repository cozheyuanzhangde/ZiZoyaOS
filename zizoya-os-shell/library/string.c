#include "string.h"

void zzylib_itoa(int n, char str[]) {
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';

    zzylib_strrev(str);
}

void zzylib_strrev(char s[]) {
    int c, i, j;
    for (i = 0, j = zzylib_strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

int zzylib_strlen(char s[]) {
    int count = 0;
    while (s[count] != '\0') ++count;
    return count;
}

void zzylib_append(char s[], char n) {
    int len = zzylib_strlen(s);
    s[len] = n;
    s[len+1] = '\0';
}

void zzylib_backspace(char s[]) {
    int len = zzylib_strlen(s);
    s[len-1] = '\0';
}

//Returns <0 if s1<s2, 0 if s1==s2, >0 if s1>s2
int zzylib_strcmp(char s1[], char s2[]) {
    int i;
    for (i = 0; s1[i] == s2[i]; i++) {    //i++ while s1[i]==s2[i] and try to detect the end of string character '\0', if true means both strings are same until the end.
        if (s1[i] == '\0') return 0;
    }
    return s1[i] - s2[i];
}