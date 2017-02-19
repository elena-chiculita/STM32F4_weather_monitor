#ifndef UTIL_H_
#define UTIL_H_


#include <stddef.h>

#define UNUSED(x) ((void)(x))

#define ASSERT(expr) \
    if (!(expr)) \
        cpu_halt(__FILE__, __LINE__, #expr)

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

void cpu_halt(const char * const file, const uint32_t line, const char * const expr);
void delay(uint32_t ms);
void uint_to_str(uint32_t n, uint8_t *str, uint8_t *size);
void memset(uint8_t *buf, int8_t c, size_t size);

#endif /* UTIL_H_ */

