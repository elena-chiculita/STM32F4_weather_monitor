#include "embedded_types.h"
#include "util.h"


void uint_to_str(uint32_t n, uint8_t *str, uint8_t *size)
{
    uint8_t count = 0, i = 0, aux;

    ASSERT(str != NULL);
    ASSERT(size != NULL);

    while (1)
    {
        *(str + count) = (n % 10) + '0';
        n /= 10;
        count++;
        if (n == 0)
        {
            break;
        }
    }

    *(str + count) = '\0';
    *size = count;

    count--;
    while (i < count)
    {
        aux = *(str + i);
        *(str + i) = *(str + count);
        *(str + count) = aux;
        i++;
        count--;
    }
}

void int_to_str(int32_t n, uint8_t *str, uint8_t *size)
{
    uint8_t count = 0, i = 0, neg = 0, aux;

    ASSERT(str != NULL);
    ASSERT(size != NULL);

    if (n < 0)
    {
        neg = 1;
        n = 0 - n;
    }

    while (1)
    {
        *(str + count) = (n % 10) + '0';
        n /= 10;
        count++;
        if (n == 0)
        {
            break;
        }
    }

    if (neg)
    {
        *(str + count) = '-';
        count++;
    }
    *(str + count) = '\0';
    *size = count;

    count--;
    while (i < count)
    {
        aux = *(str + i);
        *(str + i) = *(str + count);
        *(str + count) = aux;
        i++;
        count--;
    }
}

void hex_to_str(uint32_t n, uint8_t *str, uint8_t *size, bool uppercase)
{
    uint8_t count = 0, i = 0, mod = 0, aux;

    ASSERT(str != NULL);
    ASSERT(size != NULL);

    while (1)
    {
        mod = (n % 16);
        if (mod <= 9)
        {
            mod += '0';
        }
        else
        {
            if (uppercase)
            {
                mod += ('A' - 10);
            }
            else
            {
                mod += ('a' - 10);
            }
        }
        *(str + count) = mod;
        n /= 16;
        count++;
        if (n == 0)
        {
            break;
        }
    }

    *(str + count) = '\0';
    *size = count;

    count--;
    while (i < count)
    {
        aux = *(str + i);
        *(str + i) = *(str + count);
        *(str + count) = aux;
        i++;
        count--;
    }
}
