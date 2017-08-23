#ifndef _UTIL_H_
#define _UTIL_H_

#include "irq.h"


#define UNUSED(x) ((void)(x))

#define ASSERT(expr) \
    (!(expr)) ? cpu_halt(__FILE__, __LINE__, #expr) : UNUSED(expr)

#define FIELD_OFFSET(s, x) ((size_t)(&(((s *)0)->x)))

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))


void uint_to_str(uint32_t n, uint8_t *str, uint8_t *size);
void int_to_str(int32_t n, uint8_t *str, uint8_t *size);
void hex_to_str(uint32_t n, uint8_t *str, uint8_t *size, bool uppercase);
void delay(uint32_t ms);

#endif /* _UTIL_H_ */
