#ifndef _64_BIT_H_
#define _64_BIT_H_

#include "embedded_types.h"


typedef struct uint_64_tag
{
    uint32_t lsb;
    uint32_t msb;
} uint_64_t;

typedef struct int_64_tag
{
    uint32_t lsb;
    int32_t msb;
} int_64_t;

#endif /* _64_BIT_H_ */
