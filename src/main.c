#include "embedded_types.h"
#include "stm32f407.h"
#include "irq.h"
#include "alloc.h"
#include "led.h"
#include "lcd.h"
#include "hal_lcd.h"
#include "spi.h"
#include "timer.h"
#include "button.h"
#include "gpio_interrupt.h"
#include "bme280.h"
#include "weather_monitor.h"


int main(void)
{
    led_init(LED_GREEN_PORT, LED_GREEN_PIN);
    led_init(LED_ORANGE_PORT, LED_ORANGE_PIN);
    led_init(LED_RED_PORT, LED_RED_PIN);
    led_init(LED_BLUE_PORT, LED_BLUE_PIN);

    led_off(LED_GREEN_PORT, LED_GREEN_PIN);
    led_off(LED_ORANGE_PORT, LED_ORANGE_PIN);
    led_off(LED_RED_PORT, LED_RED_PIN);
    led_off(LED_BLUE_PORT, LED_BLUE_PIN);

    alloc_init();
    timer_init(TIM7);
    gpio_interrupt_init();
    button_init();
    spi_init(LCD_SPI_ID);
    bme280_init(BME280_MODE_FORCED, BME280_OSRS_1, BME280_OSRS_1, BME280_OSRS_1);
    lcd_init();
    lcd_backlight_on();
    lcd_set_contrast(60);

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

    timer_register(TIM7, LED_GREEN_TIMEOUT_MS, TIMER_RESCHEDULE_PERIOD, TIMER_REGISTER, led_green_toggle_callback);
    timer_register(TIM7, LED_ORANGE_TIMEOUT_MS, TIMER_RESCHEDULE_PERIOD, TIMER_REGISTER, led_orange_toggle_callback);
    timer_register(TIM7, LED_RED_TIMEOUT_MS, TIMER_RESCHEDULE_PERIOD, TIMER_REGISTER, led_red_toggle_callback);
    timer_register(TIM7, LED_BLUE_TIMEOUT_MS, TIMER_RESCHEDULE_PERIOD, TIMER_REGISTER, led_blue_toggle_callback);

    weather_monitor_init();
    weather_monitor_launch();

    while (1);

    return 0;
}
