#ifndef LIB_STR
#define LIB_STR

void zzylib_itoa(int n, char str[]);
void zzylib_htoa(int n, char str[]);
void zzylib_strrev(char s[]);
int zzylib_strlen(char s[]);
void zzylib_append(char s[], char n);
void zzylib_backspace(char s[]);
int zzylib_strcmp(char s1[], char s2[]);
int zzylib_atoi(char* str);
void zzylib_append2(char s[], char n);

#endif