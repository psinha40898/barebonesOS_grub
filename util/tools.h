#ifndef TOOLS_H
#define TOOLS_H
#include <stdint.h>

void memory_set(uint8_t *dest, uint8_t val, uint32_t len);
void int_to_ascii(int n, char str[]);
void reverse(char s[]);
int strlen(char s[]);

#endif