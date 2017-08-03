#include "uint_64.h"
#include "util.h"


uint_64_t convert_int64_to_uint64(int_64_t val)
{
    uint_64_t res;

    res.msb = (uint32_t)val.msb;
    res.lsb = val.lsb;

    return res;
}

uint_64_t uint_64_neg(uint_64_t val)
{
    val.msb = ~val.msb;
    val.lsb = ~val.lsb;

    return val;
}

uint_64_t uint_64_shift_left(uint_64_t val, uint8_t n)
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

uint_64_t uint_64_shift_right(uint_64_t val, uint8_t n)
{
    ASSERT(n <= 64);

    if (n <= 32)
    {
        val.lsb = (val.msb << (32 - n)) | (val.lsb >> n);
        val.msb = val.msb >> n;
    }
    else
    {
        val.lsb = val.msb >> (n - 32);
        val.msb = 0;
    }

    return val;
}

uint_64_t uint_64_add(uint_64_t a, uint_64_t b)
{
    uint_64_t res;

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

uint_64_t uint_64_sub(uint_64_t a, uint_64_t b)
{
    uint_64_t one;

    one.msb = 0x0;
    one.lsb = 0x1;
    b = uint_64_neg(b);

    return uint_64_add(a, uint_64_add(b, one));
}

uint_64_t uint_64_div(uint_64_t a, uint_64_t b)
{
    uint_64_t res, one, tmp, aux;
    int8_t cmp, i;

    res.msb = res.lsb = 0;
    tmp.msb = tmp.lsb = 0;
    one.msb = 0;
    one.lsb = 1;

    ASSERT((b.msb != 0) || (b.lsb != 0));

    for (i = 63; i >= 0; i--)
    {
        tmp = uint_64_shift_left(tmp, 1);
        aux = uint_64_shift_right(a, i);
        aux.msb = 0;
        aux.lsb = aux.lsb & 0x1;
        tmp = uint_64_add(tmp, aux);
        res = uint_64_shift_left(res, 1);
        cmp = uint_64_cmp(tmp, b);
        if (cmp >= 0)
        {
            tmp = uint_64_sub(tmp, b);
            res = uint_64_add(res, one);
        }
    }

    return res;
}

int8_t uint_64_cmp(uint_64_t a, uint_64_t b)
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
