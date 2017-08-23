#include "embedded_types.h"
#include "util.h"
#include "util_test.h"
#include "int_64.h"


uint32_t memset_test(void)
{
    uint8_t dst[] = {0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40};
    uint8_t res[] = {0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40};
    uint8_t val = 0x41;
    uint8_t i, j;

    for (i = 0; i < sizeof(dst); i++)
    {
        memset(dst, val, i);
        TEST(memcmp(dst, res, sizeof(dst)) == 0)
        res[i] = val;
    }

    for (i = 0; i < sizeof(dst); i++)
    {
        dst[i] = res[i] = 0x40;
    }

    for (i = 0; i <= 5; i++)
    {
        memset(dst + i, val, 8);
        for (j = 0; j < 8; j++)
        {
            res[j + i] = val;
        }
        TEST(memcmp(dst, res, sizeof(dst)) == 0)

        for (j = 0; j < sizeof(dst); j++)
        {
            dst[j] = res[j] = 0x40;
        }
    }

    return PASS;
}

uint32_t memcpy_test(void)
{
    uint8_t dst[] = {0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40};
    uint8_t src[] = {0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D};
    uint8_t res[] = {0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40};
    uint8_t i, j, k;

    for (i = 0; i < sizeof(dst); i++)
    {
        for (j = 0; j <= i; j++)
        {
            res[j] = src[j];
        }
        memcpy(dst, src, i + 1);
        TEST(memcmp(dst, res, i + 1) == 0)
        memset(dst, 0x40, sizeof(dst));
        memset(res, 0x40, sizeof(res));
    }

    for (i = 0; i <= 5; i++)
    {
        for (j = 0; j <= 5; j++)
        {
            for (k = 0; k < 8; k++)
            {
                res[k + i] = src[k + j];
            }
            memcpy(dst + i, src + j, 8);
            TEST(memcmp(dst, res, sizeof(dst)) == 0)
            memset(dst, 0x40, sizeof(dst));
            memset(res, 0x40, sizeof(res));
        }
    }

    return PASS;
}

uint32_t memmove_test(void)
{
    uint8_t dst[] = {0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D};
    uint8_t res[] = {0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D};
    uint8_t original[] = {0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D};
    uint8_t i, j;
    
#if 0
    for (i = 0; i <= 8; i++)
    {
        memcpy(res, dst + 5, i);
        memmove(dst, dst + 5, i);
        TEST(memcmp(dst, res, sizeof(dst)) == 0)
        memcpy(dst, original, sizeof(dst));
        memcpy(res, original, sizeof(res));
    }
#endif
    for (i = 0; i <= 8; i++)
    {
        memcpy(res + 5, dst, i);
        memmove(dst + 5, dst, i);
        TEST(memcmp(dst, res, sizeof(dst)) == 0)
        memcpy(dst, original, sizeof(dst));
        memcpy(res, original, sizeof(res));
    }

    for (i = 0; i <= 5; i++)
    {
        for (j = 0; j <= 5; j++)
        {
            memcpy(res + i, dst + j, 8);
            memmove(dst + i, dst + j, 8);
            TEST(memcmp(dst, res, sizeof(dst)) == 0)
            memcpy(dst, original, sizeof(dst));
            memcpy(res, original, sizeof(res));
        }
    }

    return PASS;
}

uint32_t memcmp_test(void)
{
    uint8_t dst[] = {0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40};
    uint8_t src[] = {0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40};
    uint8_t i, j;

    for (i = 0; i < sizeof(dst); i++)
    {
        dst[i] = 0x3F;
        TEST(memcmp(dst, src, sizeof(dst)) < 0)
        dst[i] = 0x41;
        TEST(memcmp(dst, src, sizeof(dst)) > 0)
        dst[i] = 0x40;
        TEST(memcmp(dst, src, sizeof(dst)) == 0)
    }

    for (i = 0; i <= 5; i++)
    {
        for (j = 0; j <= 5; j++)
        {
            TEST(memcmp(dst + i, src + j, 8) == 0)
        }
    }

    return PASS;
}
