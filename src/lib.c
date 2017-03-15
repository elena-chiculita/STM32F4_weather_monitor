#include <stdarg.h>
#include "lib.h"
#include "util.h"
#include "lcd.h"


int printf(const char *format, ...)
{
    va_list ap;
    const char *p;
    uint32_t count;

    ASSERT(format != NULL);

    va_start(ap, format);
    p = format;
    count = 0;

    while (*p)
    {
        switch (*p)
        {
            case '%':
                p++;

                if (*p == 0)
                {
                    count += (p - format - 1);
                    lcd_putb((uint8_t *)format, p - format - 1);
                    format = p;
                    break;
                }
                if (*p == '%')
                {
                    count += (p - format - 1);
                    lcd_putb((uint8_t *)format, p - format - 1);
                    format = p;
                    p++;
                    continue;
                }

                switch (*p)
                {
                    case 'd':
                    {
                        uint8_t buf[255], size;
                        int n;

                        n = va_arg(ap, int);
                        int_to_str(n, buf, &size);
                        if (p > (format + 1))
                        {
                            count += (p - format - 1);
                            lcd_putb((uint8_t *)format, p - format - 1);
                        }
                        format = p + 1;
                        lcd_putb(buf, size);
                        count += size;
                        break;
                    }
                    case 's':
                    {
                        char *str;

                        str = va_arg(ap, char *);
                        if (p > (format + 1))
                        {
                            count += (p - format - 1);
                            lcd_putb((uint8_t *)format, p - format - 1);
                        }
                        format = p + 1;
                        lcd_putb((uint8_t *)str, strlen(str));
                        count += strlen(str);
                        break;
                    }
                    default:
                        break;
                }
                break;

            default:
                break;
        }

        p++;
    }

    va_end(ap);

    if (format < p)
    {
        lcd_putb((uint8_t *)format, (p - format));
        count += (p - format);
    }

    return count;
}
