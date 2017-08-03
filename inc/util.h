#ifndef _UTIL_H_
#define _UTIL_H_

#include <stddef.h>


#define UNUSED(x) ((void)(x))

#define ASSERT(expr) \
    (!(expr)) ? cpu_halt(__FILE__, __LINE__, #expr) : UNUSED(expr)

#define FIELD_OFFSET(s, x) ((size_t)(&(((s *)0)->x)))

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))


void _disable_irq(void);
void _enable_irq(void);
void cpu_halt(const char * const file, const uint32_t line, const char * const expr);
void uint_to_str(uint32_t n, uint8_t *str, uint8_t *size);
void int_to_str(int32_t n, uint8_t *str, uint8_t *size);
void hex_to_str(uint32_t n, uint8_t *str, uint8_t *size, bool uppercase);
void *memset(void *ptr, int value, size_t num);
void *memcpy(void *destination, const void *source, size_t num);
void *memmove(void *destination, const void *source, size_t num);
int memcmp(const void *ptr1, const void *ptr2, size_t num);
size_t strlen(const char *str);
uint32_t core_reg_get_control(void);
void core_reg_set_control(uint32_t val);
void delay(uint32_t ms);
size_t get_lr(void);

#endif /* _UTIL_H_ */
