#ifndef UTIL_TEST_H_
#define UTIL_TEST_H_

extern uint32_t testId;

#define TEST(cond) \
    { \
        testId++; \
        if (!(cond)) \
        { \
            return FALSE; \
        } \
    }

uint32_t memset_test(void);
uint32_t memcpy_test(void);
uint32_t memmove_test(void);
uint32_t memcmp_test(void);

#endif /* UTIL_TEST_H_ */
