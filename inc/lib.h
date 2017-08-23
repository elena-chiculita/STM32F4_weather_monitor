#ifndef _LIB_H_
#define _LIB_H_

#include <stddef.h>
#include <stdarg.h>
#include "embedded_types.h"


#define PRINTF_MAX_BUF 256


int printf(const char *format, ...);
int snprintf(char *s, size_t n, const char *format, ...);
void print_cpy_buf(char *s, size_t n, size_t *max_chars, size_t *no_chars, const char *format, va_list arg);
void* memset(void *ptr, int value, size_t num);
void* memcpy(void *destination, const void *source, size_t num);
bool memcpy_s(void *destination, size_t dest_size, const void *source, size_t num);
void* memmove(void *destination, const void *source, size_t num);
int memcmp(const void *ptr1, const void *ptr2, size_t num);
size_t strlen(const char *str);

#endif /* _LIB_H_ */
