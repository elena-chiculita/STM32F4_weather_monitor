#include "embedded_types.h"
#include "stm32f407.h"
#include "led.h"
#include "gpio.h"
#include "hal_lcd.h"
#include "lcd.h"
#include "util.h"


int main(void)
{
    lcd_init();

    gpio_init(GPIOA, 0, GPIO_MODER_INPUT, GPIO_OTYPER_PUSH_PULL,
              GPIO_OSPEEDR_VERY_HIGH, GPIO_PUPDR_NO_PULL);

    led_init(LED_GREEN_PORT, LED_GREEN_PIN);
    led_init(LED_ORANGE_PORT, LED_ORANGE_PIN);
    led_init(LED_RED_PORT, LED_RED_PIN);
    led_init(LED_BLUE_PORT, LED_BLUE_PIN);

    led_on(LED_GREEN_PORT, LED_GREEN_PIN);
    led_on(LED_BLUE_PORT, LED_BLUE_PIN);

    hal_lcd_backlight_on();
    lcd_set_contrast(60);

    lcd_print((uint8_t *)"abcdefghijklmnopqrstuvwxyz", 26);
    delay(10);

mainloop:
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
