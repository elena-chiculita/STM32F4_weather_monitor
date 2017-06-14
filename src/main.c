#include "embedded_types.h"
#include "stm32f407.h"
#include "led.h"
#include "gpio.h"
#include "hal_lcd.h"
#include "lcd.h"
#include "spi.h"
#include "util.h"
#include "lib.h"
#include "alloc.h"
#include "bme280.h"


int main(void)
{
    int32_t temp, press, hum, div;
    uint16_t mod_hum;
    uint8_t mod_temp, mod_press;

    alloc_init();

    led_init(LED_GREEN_PORT, LED_GREEN_PIN);
    led_init(LED_ORANGE_PORT, LED_ORANGE_PIN);
    led_init(LED_RED_PORT, LED_RED_PIN);
    led_init(LED_BLUE_PORT, LED_BLUE_PIN);

    led_on(LED_BLUE_PORT, LED_BLUE_PIN);

    gpio_init(GPIOA, 0, GPIO_MODER_INPUT, GPIO_OTYPER_PUSH_PULL,
              GPIO_OSPEEDR_VERY_HIGH, GPIO_PUPDR_NO_PULL);

    if (core_reg_get_control() == CONTROL_PRIV_UNPRIVILEGED)
    {
        /* unprivileged mode */
        led_on(LED_RED_PORT, LED_RED_PIN);
    }
    else
    {
        /* privileged mode */
        led_on(LED_GREEN_PORT, LED_GREEN_PIN);
    }

    spi_init(LCD_SPI_ID);

    lcd_init();
    lcd_backlight_on();
    lcd_set_contrast(60);

    led_on(LED_ORANGE_PORT, LED_ORANGE_PIN);
    delay(1000);
    led_off(LED_ORANGE_PORT, LED_ORANGE_PIN);

    bme280_init(BME280_MODE_FORCED, BME280_OSRS_1, BME280_OSRS_1, BME280_OSRS_1);

mainloop:

    bme280_poll(&press, &temp, &hum);

    div = temp / 100;
    mod_temp = (uint8_t)(temp - (div * 100));
    printf("\n%d.%d%cC ", div, mod_temp, 248);

    mod_hum = (((uint16_t)hum & 0x3FF) * 99) / 1023;
    div = hum >> 10;
    printf("%d.%d%%RH", div, mod_hum);

    mod_press = (((uint8_t)press) * 99) / 255;
    div = press >> 8;
    printf("\n%d.%d Pa", div, mod_press);

    delay(2000);

    if (gpio_get(GPIOA, 0))
    {
        led_on(LED_BLUE_PORT, LED_BLUE_PIN);
    }
    else
    {
        led_off(LED_BLUE_PORT, LED_BLUE_PIN);
    }

    goto mainloop;

    return 0;
}
