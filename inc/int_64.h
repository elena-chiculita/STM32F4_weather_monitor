#ifndef _INT_64_H_
#define _INT_64_H_

#include "embedded_types.h"
#include "64bit.h"


int_64_t convert_uint64_to_int64(uint_64_t val);
int32_t convert_int64_to_int32(int_64_t val);
int_64_t convert_int32_to_int64(int32_t val);
int_64_t int_64_create(int32_t msb, uint32_t lsb);
void int_64_get_words(int_64_t val, int32_t *msb, uint32_t *lsb);
int_64_t int_64_neg(int_64_t val);
int_64_t int_64_shift_left(int_64_t val, uint8_t n);
int_64_t int_64_shift_right(int_64_t val, uint8_t n);
int_64_t int_64_add(int_64_t a, int_64_t b);
int_64_t int_64_sub(int_64_t a, int_64_t b);
int_64_t int_64_mul(int_64_t a, int_64_t b);
int_64_t int_64_div(int_64_t a, int_64_t b);
int8_t int_64_cmp(int_64_t a, int_64_t b);

#endif /* _INT_64_H_ */
