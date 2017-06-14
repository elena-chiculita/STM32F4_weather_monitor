#ifndef TEST_H_
#define TEST_H_

#include "embedded_types.h"


typedef enum test_status_tag
{
    PASS = 0,
    FAIL = 1
} test_status_t;

extern uint32_t testId;


#define TEST(cond) \
    { \
        testId++; \
        if (!(cond)) \
        { \
            return FAIL; \
        } \
    }

#endif /* TEST_H_ */
