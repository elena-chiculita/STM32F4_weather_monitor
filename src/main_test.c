#include "embedded_types.h"
#include "stm32f407.h"
#include "led.h"
#include "gpio.h"
#include "hal_lcd.h"
#include "lcd.h"
#include "util.h"
#include "util_test.h"
#include "int_64_test.h"
#include "list_test.h"
#include "lib.h"
#include "alloc.h"
#include "spi.h"


uint32_t testId;


int main(void)
{
    alloc_init();

    spi_init(LCD_SPI_ID);

    lcd_init();
    hal_lcd_backlight_on();
    lcd_set_contrast(60);

    printf("memcmp ");
    if (memcmp_test() != PASS)
    {
        printf("FAILED %d\n", testId);
        goto mainloop;
    }
    printf("OK\n");

    printf("memset ");
    if (memset_test() != PASS)
    {
        printf("FAILED %d\n", testId);
        goto mainloop;
    }
    printf("OK\n");

    printf("memcpy ");
    if (memcpy_test() != PASS)
    {
        printf("FAILED %d\n", testId);
        goto mainloop;
    }
    printf("OK\n");

#if 0
    printf("memmove ");
    if (memmove_test() != PASS)
    {
        printf("FAILED %d\n", testId);
        goto mainloop;
    }
    printf("OK\n");
#endif

    printf("64<->32 conv. ");
    if (int_64_conversions_test() != PASS)
    {
        printf("FAILED %d\n", testId);
        goto mainloop;
    }
    printf("OK\n");

    printf("int64 math ");
    if (int_64_math_test() != PASS)
    {
        printf("FAILED %d\n", testId);
        goto mainloop;
    }
    printf("OK\n");

    printf("int64 bit ");
    if (int_64_bitwise_test() != PASS)
    {
        printf("FAILED %d\n", testId);
        goto mainloop;
    }
    printf("OK\n");

    printf("list ");
    if (list_test() != PASS)
    {
        printf("FAILED %d\n", testId);
        goto mainloop;
    }
    printf("OK\n");

mainloop:

    goto mainloop;

    return 0;
}

