#include <stddef.h>
#include <stdarg.h>
#include "lib.h"
#include "alloc.h"
#include "util.h"
#include "lcd.h"


int printf(const char *format, ...)
{
    uint8_t buf[PRINTF_MAX_BUF];
    va_list arg;
    size_t count, max_count;

    ASSERT(format != NULL);

    va_start(arg, format);
    print_cpy_buf((char *)buf, PRINTF_MAX_BUF, &max_count, &count, format, arg);
    va_end(arg);

    lcd_putb(buf, count);

    if (max_count > count)
    {
        cpu_halt(__FILE__, __LINE__, "buffer size exceeded");
    }

    return count;
}

int snprintf(char *s, size_t n, const char *format, ...)
{
    va_list arg;
    size_t count, max_count;

    ASSERT((format != NULL) && (n > 0));

    va_start(arg, format);
    print_cpy_buf(s, n - 1, &max_count, &count, format, arg);
    va_end(arg);

    *(s + count) = '\0';

    return max_count;
}

void print_cpy_buf(char *s, size_t n, size_t *max_chars, size_t *no_chars, const char *format, va_list arg)
{
    const char *p;
    uint8_t *tmp, size;
    char *str;
    size_t max, count, partial_count;
    bool is_format_arg, is_memcpy_s_done, done;

    ASSERT((s != NULL) && (max_chars != NULL) && (no_chars != NULL) && (format != NULL));

    if (n == 0)
    {
        *no_chars = *max_chars = 0;
        return;
    }

    tmp = malloc(n * sizeof(uint8_t));
    ASSERT(tmp != NULL);

    p = format;
    max = count = partial_count = 0;
    is_format_arg = FALSE;
    is_memcpy_s_done = TRUE;
    done = FALSE;

    while (*p)
    {
        switch (*p)
        {
            case '%':
                is_format_arg = TRUE;
                p++;

                switch (*p)
                {
                    case '%':
                        size = 1;
                        tmp[0] = '%';
                        break;

                    case 'd':
                        int_to_str(va_arg(arg, int), tmp, &size);
                        break;

                    case 'x':
                    case 'X':
                        hex_to_str(va_arg(arg, int), tmp, &size, ((*p == 'x') ? FALSE : TRUE));
                        break;

                    case 'c':
                        size = 1;
                        tmp[0] = (char)va_arg(arg, int);
                        break;

                    case 's':
                        str = va_arg(arg, char *);
                        size = strlen(str);
                        if (done == FALSE)
                        {
                            memcpy_s(tmp, n, str, size);
                        }
                        break;

                    case '\0':
                        is_format_arg = FALSE;
                        p--;
                        break;

                    default:
                        break;
                }

                break;

            default:
                break;
        }

        if (is_format_arg)
        {
            if (p > (format + 1))
            {
                partial_count = p - (format + 1);
                if (done == FALSE)
                {
                    is_memcpy_s_done = memcpy_s(s, n, format, partial_count);
                    if (is_memcpy_s_done == FALSE)
                    {
                        max += (partial_count - n);
                        done = TRUE;
                        count += n;
                        s += n;
                        n = 0;
                    }
                    else
                    {
                        count += partial_count;
                        s += partial_count;
                        n -= partial_count;
                    }
                }
                else
                {
                    max += partial_count;
                }
            }

            format = p + 1;
            partial_count = size;
            if (done == FALSE)
            {
                is_memcpy_s_done = memcpy_s(s, n, tmp, partial_count);
                if (is_memcpy_s_done == FALSE)
                {
                    max += (partial_count - n);
                    done = TRUE;
                    count += n;
                    s += n;
                    n = 0;
                }
                else
                {
                    count += partial_count;
                    s += partial_count;
                    n -= partial_count;
                }
            }
            else
            {
                max += partial_count;
            }

            is_format_arg = FALSE;
        }

        p++;

        if (*p == '\0')
        {
            if (format < p)
            {
                partial_count = p - format;
                
                if (done == FALSE)
                {
                    is_memcpy_s_done = memcpy_s(s, n, format, partial_count);
                    if (is_memcpy_s_done == FALSE)
                    {
                        max += (partial_count - n);
                        done = TRUE;
                        count += n;
                        s += n;
                        n = 0;
                    }
                    else
                    {
                        count += partial_count;
                        s += partial_count;
                        n -= partial_count;
                    }
                }
                else
                {
                    max += partial_count;
                }
            }

            break;
        }
    }

    free(tmp);

    *no_chars = count;
    *max_chars = max + count;
}
