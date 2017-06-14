#ifndef UINT_64_H_
#define UINT_64_H_

#include "embedded_types.h"
#include "64bit.h"


uint_64_t convert_int64_to_uint64(int_64_t val);
uint_64_t uint_64_neg(uint_64_t val);
uint_64_t uint_64_shift_left(uint_64_t val, uint8_t n);
uint_64_t uint_64_shift_right(uint_64_t val, uint8_t n);
uint_64_t uint_64_add(uint_64_t a, uint_64_t b);
uint_64_t uint_64_sub(uint_64_t a, uint_64_t b);
uint_64_t uint_64_div(uint_64_t a, uint_64_t b);
int8_t uint_64_cmp(uint_64_t a, uint_64_t b);

#endif /* UINT_64_H_ */
