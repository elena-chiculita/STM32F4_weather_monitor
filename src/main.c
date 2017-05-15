#include "embedded_types.h"
#include "stm32f407.h"
#include "led.h"
#include "gpio.h"
#include "hal_lcd.h"
#include "lcd.h"
#include "util.h"
#include "lib.h"
#include "alloc.h"
#include "spi.h"


int main(void)
{
    uint8_t data_tx[] = {1, 4, 24, 255}, data_rx[] = {35, 69, 103, 137};

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

    lcd_init();
    lcd_backlight_on();
    lcd_set_contrast(60);

    printf("debug build\n");

    led_on(LED_ORANGE_PORT, LED_ORANGE_PIN);
    delay(1000);
    led_off(LED_ORANGE_PORT, LED_ORANGE_PIN);

    spi_txrx(data_tx, data_rx, sizeof(data_tx), SPI_DEVICE_SENSOR, hal_lcd_spi_callback);
    printf("%d %d %d %d", data_rx[0], data_rx[1], data_rx[2], data_rx[3]);

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
