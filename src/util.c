#include "embedded_types.h"
#include "util.h"


void cpu_halt(const char * const file, const uint32_t line, const char * const expr)
{
    UNUSED(file);
    UNUSED(line);
    UNUSED(expr);
    while (1);
}

void delay(uint32_t ms)
{
    uint32_t i, j;

    for (i = 0; i < ms; i++)
    {
        for (j = 0; j < 300000U; j++);
    }
}

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
