#include "int_64.h"
#include "uint_64.h"
#include "util.h"


int_64_t convert_uint64_to_int64(uint_64_t val)
{
    int_64_t res;

    res.msb = (int32_t)val.msb;
    res.lsb = val.lsb;

    return res;
}

int32_t convert_int64_to_int32(int_64_t val)
{
    return ((int32_t)val.lsb);
}

int_64_t convert_int32_to_int64(int32_t val)
{
    int_64_t res;

    res.msb = (val & 0x80000000) ? 0xFFFFFFFF : 0x0;
    res.lsb = val;

    return res;
}

int_64_t int_64_create(int32_t msb, uint32_t lsb)
{
    int_64_t res;

    res.msb = msb;
    res.lsb = lsb;

    return res;
}

void int_64_get_words(int_64_t val, int32_t *msb, uint32_t *lsb)
{
    ASSERT((msb != NULL) && (lsb != NULL));

    *msb = val.msb;
    *lsb = val.lsb;
}

int_64_t int_64_neg(int_64_t val)
{
    val.msb = ~val.msb;
    val.lsb = ~val.lsb;

    return val;
}

int_64_t int_64_shift_left(int_64_t val, uint8_t n)
{
    ASSERT(n <= 64);

    if (n <= 32)
    {
        val.msb = (val.msb << n) | (val.lsb >> (32 - n));
        val.lsb = val.lsb << n;
    }
    else
    {
        val.msb = val.lsb << (n - 32);
        val.lsb = 0;
    }

    return val;
}

int_64_t int_64_shift_right(int_64_t val, uint8_t n)
{
    ASSERT(n <= 64);

    if (n <= 32)
    {
        val.lsb = (val.msb << (32 - n)) | (val.lsb >> n);
        val.msb = ((val.msb & 0x80000000) ? (0xFFFFFFFF << (32 - n)) : 0x0) | (val.msb >> n);
    }
    else
    {
        val.lsb = ((val.msb & 0x80000000) ? (0xFFFFFFFF << (64 - n)) : 0x0) | (val.msb >> (n - 32));
        val.msb = (val.msb & 0x80000000) ? 0xFFFFFFFF : 0x0;
    }

    return val;
}

int_64_t int_64_add(int_64_t a, int_64_t b)
{
    int_64_t res;

    res.lsb = a.lsb + b.lsb;

    if ((0xFFFFFFFF - a.lsb) >= b.lsb)
    {
        res.msb = 0;
    }
    else
    {
        res.msb = 1;
    }

    res.msb += a.msb + b.msb;

    return res;
}

int_64_t int_64_sub(int_64_t a, int_64_t b)
{
    int_64_t one;

    one.msb = 0x0;
    one.lsb = 0x1;
    b = int_64_neg(b);

    return int_64_add(a, int_64_add(b, one));
}

int_64_t int_64_mul(int_64_t a, int_64_t b)
{
    int_64_t res;
    uint8_t i, tmp;

    res.msb = res.lsb = 0x0;

    for (i = 0; i < 64; i++)
    {
        if (i <= 31)
        {
            tmp = (b.lsb >> i) & 0x1;
        }
        else
        {
            tmp = (b.msb >> (i - 32)) & 0x1;
        }

        if (tmp)
        {
            res = int_64_add(res, int_64_shift_left(a, i));
        }
    }

    return res;
}

int_64_t int_64_div(int_64_t a, int_64_t b)
{
    int_64_t res, one, tmp;
    uint_64_t u_res;
    bool sign;

    res.msb = res.lsb = 0;
    tmp.msb = tmp.lsb = 0;
    one.msb = 0;
    one.lsb = 1;

    ASSERT((b.msb != 0) || (b.lsb != 0));

    sign = ((a.msb & 0x80000000) ^ (b.msb & 0x80000000)) >> 31;
    if (a.msb & 0x80000000)
    {
        a = int_64_add(int_64_neg(a), one);
    }
    if (b.msb & 0x80000000)
    {
        b = int_64_add(int_64_neg(b), one);
    }

    u_res = uint_64_div(convert_int64_to_uint64(a), convert_int64_to_uint64(b));
    res = convert_uint64_to_int64(u_res);

    if (sign)
    {
        res = int_64_add(int_64_neg(res), one);
    }

    return res;
}

int8_t int_64_cmp(int_64_t a, int_64_t b)
{
    if (a.msb != b.msb)
    {
        return ((a.msb < b.msb) ? -1 : 1);
    }

    if (a.lsb != b.lsb)
    {
        return ((a.lsb < b.lsb) ? -1 : 1);
    }

    return 0;
}
