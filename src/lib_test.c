#include "lib_test.h"
#include "lib.h"
#include "util.h"


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
    bool res_safe_memcpy;

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

    res_safe_memcpy = memcpy_s(dst, sizeof(dst), src, (sizeof(dst) + 1 * (sizeof(dst) / sizeof(dst[0]))));
    TEST(memcmp(dst, src, sizeof(dst)) == 0)
    TEST(res_safe_memcpy == FALSE)

    memset(dst, 0x0, sizeof(dst));
    res_safe_memcpy = memcpy_s(dst, sizeof(dst), src, sizeof(dst));
    TEST(memcmp(dst, src, sizeof(dst)) == 0)
    TEST(res_safe_memcpy == TRUE)

    return PASS;
}

uint32_t memmove_test(void)
{
    uint8_t dst[] = {0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D};
    uint8_t res[] = {0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D};
    uint8_t original[] = {0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D};
    uint8_t i, j;

    for (i = 0; i <= 8; i++)
    {
        memcpy(res, dst + 5, i);
        memmove(dst, dst + 5, i);
        TEST(memcmp(dst, res, sizeof(dst)) == 0)
        memcpy(dst, original, sizeof(dst));
        memcpy(res, original, sizeof(res));
    }

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

uint32_t snprintf_test(void)
{
    char buf[255] = "";
    const char *format[3] = {"1234%%abcd%d%s_*!%", "1234%%abcd%d%s_", "1234%%abcd%d%s"};
    const char *res[3] = {"1234%abcd1213_*!%", "1234%abcd1213_", "1234%abcd1213"};
    size_t size[3];
    uint8_t count, i;

    for (i = 0; i < 3; i++)
    {
        size[i] = strlen(res[i]);
        count = snprintf(buf, size[i] + 1, format[i], 12, "13");
        TEST(count == size[i])
        TEST(memcmp(buf, res[i], count) == 0)
        TEST(strlen(buf) == size[i])
        memset(buf, 0xa, sizeof(buf));

        count = snprintf(buf, sizeof(buf), format[i], 12, "13");
        TEST(count == size[i])
        TEST(memcmp(buf, res[i], count) == 0)
        TEST(strlen(buf) == count)
        memset(buf, 0xa, sizeof(buf));

        count = snprintf(buf, size[i], format[i], 12, "13");
        TEST(count == size[i])
        TEST(memcmp(buf, res[i], count - 1) == 0)
        TEST(strlen(buf) == (size_t)(count - 1))
        memset(buf, 0xa, sizeof(buf));
    }

    count = snprintf(buf, 1, format[0], 12, "13");
    TEST(count == 0)    

    return PASS;
}
