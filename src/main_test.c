#include "embedded_types.h"
#include "stm32f407.h"
#include "alloc.h"
#include "spi.h"
#include "hal_lcd.h"
#include "lcd.h"
#include "lib.h"
#include "lib_test.h"
#include "int_64_test.h"
#include "list_test.h"
#include "util.h"


typedef struct test_matrix_tag
{
    uint32_t (*fn)();
    const char *name;
} test_matrix_t;


test_matrix_t test[] = {
    {memcmp_test, "memcmp"},
    {memset_test, "memset"},
    {memcpy_test, "memcpy"},
    {memmove_test, "memmove"},
    {int_64_conversions_test, "64<->32 conv."},
    {int_64_math_test, "int64 math"},
    {int_64_bitwise_test, "int64 bit"},
    {list_test, "list"},
    {snprintf_test, "snprintf"}
};

uint32_t testId;


int main(void)
{
    uint32_t i;

    alloc_init();
    spi_init(LCD_SPI_ID);
    lcd_init();
    hal_lcd_backlight_on();
    lcd_set_contrast(60);

    for (i = 0; i < (sizeof(test) / sizeof(test[0])); i++)
    {
        printf("%s ", test[i].name);

        if ((*(test[i].fn))() != PASS)
        {
            printf("FAILED %d\n", testId);
            goto mainloop;
        }

        printf("OK\n");
        delay(1000);
    }

mainloop:

    goto mainloop;

    return 0;
}
