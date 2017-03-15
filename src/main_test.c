#include "embedded_types.h"
#include "stm32f407.h"
#include "led.h"
#include "gpio.h"
#include "hal_lcd.h"
#include "lcd.h"
#include "util.h"
#include "util_test.h"
#include "lib.h"


uint32_t testId;


int main(void)
{
    lcd_init();
    hal_lcd_backlight_on();
    lcd_set_contrast(60);

    printf("memcmp ");
    if (memcmp_test())
    {
        printf("FAILED %d\n", testId);
        goto mainloop;
    }
    printf("OK\n");

    printf("memset ");
    if (memset_test())
    {
        printf("FAILED %d\n", testId);
        goto mainloop;
    }
    printf("OK\n");

    printf("memcpy ");
    if (memcpy_test())
    {
        printf("FAILED %d\n", testId);
        goto mainloop;
    }
    printf("OK\n");

    printf("memmove ");
    if (memmove_test())
    {
        printf("FAILED %d\n", testId);
        goto mainloop;
    }
    printf("OK\n");

mainloop:
    goto mainloop;

    return 0;
}

