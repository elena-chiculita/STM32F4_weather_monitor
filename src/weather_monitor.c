#include "weather_monitor.h"
#include "button.h"
#include "gpio.h"
#include "lib.h"
#include "bme280.h"
#include "timer.h"


volatile weather_monitor_display_t weather_monitor_display = WEATHER_MONITOR_DISPLAY_FIRST;
weather_monitor_display_t weather_monitor_display_old = WEATHER_MONITOR_DISPLAY_FIRST;
volatile weather_monitor_refresh_rate_t weather_monitor_refresh_rate = WEATHER_MONITOR_REFRESH_RATE_FIRST;
volatile weather_monitor_refresh_t weather_monitor_refresh;
volatile bool weather_monitor_changed_refresh = FALSE;


void weather_monitor_init(void)
{
    button_register(WEATHER_MONITOR_BUTTON_PORT, WEATHER_MONITOR_BUTTON_PIN, weather_monitor_display_state);
    button_register(WEATHER_MONITOR_BUTTON_PORT, WEATHER_MONITOR_BUTTON_PIN, weather_monitor_long_press);
}

void weather_monitor_launch(void)
{
    int32_t temp, press, hum, div;
    uint16_t mod_hum;
    uint8_t mod_temp, mod_press;

    timer_register(TIM7,
                   weather_monitor_get_refresh_rate_ms(weather_monitor_refresh_rate),
                   TIMER_RESCHEDULE_PERIOD,
                   TIMER_REGISTER,
                   weather_monitor_refresh_timer_callback);

    while (1)
    {
        bme280_poll(&press, &temp, &hum);

        if (weather_monitor_display_old != weather_monitor_display)
        {
            weather_monitor_display_old = weather_monitor_display;
        }

        printf("\n\n");

        if (weather_monitor_display_old == WEATHER_MONITOR_DISPLAY_TEMP)
        {
            div = temp / 100;
            mod_temp = (uint8_t)(temp - (div * 100));
            printf("%d.%d%cC", div, mod_temp, 248);
        }

        if (weather_monitor_display_old == WEATHER_MONITOR_DISPLAY_HUM)
        {
            mod_hum = (((uint16_t)hum & 0x3FF) * 99) / 1023;
            div = hum >> 10;
            printf("%d.%d%%RH", div, mod_hum);
        }

        if (weather_monitor_display_old == WEATHER_MONITOR_DISPLAY_PRESS)
        {
            mod_press = (((uint8_t)press) * 99) / 255;
            div = press >> 8;
            printf("%d.%d Pa", div, mod_press);
        }

        weather_monitor_refresh = WEATHER_MONITOR_REFRESH_IN_PROGRESS;
        while (weather_monitor_refresh != WEATHER_MONITOR_REFRESH_DONE);
    }
}

void weather_monitor_display_state(gpio_port_t port, uint8_t pin, button_state_t state)
{
    UNUSED(port && pin);

    if (state == BUTTON_STATE_PRESSED)
    {
        return;
    }

    if (weather_monitor_changed_refresh)
    {
        weather_monitor_changed_refresh = FALSE;
        return;
    }

    if (weather_monitor_display < WEATHER_MONITOR_DISPLAY_LAST)
    {
        weather_monitor_display++;
    }
    else
    {
        weather_monitor_display = WEATHER_MONITOR_DISPLAY_FIRST;
    }

    weather_monitor_refresh = WEATHER_MONITOR_REFRESH_DONE;

    timer_register(TIM7,
                   weather_monitor_get_refresh_rate_ms(weather_monitor_refresh_rate),
                   TIMER_RESCHEDULE_PERIOD,
                   TIMER_REGISTER,
                   weather_monitor_refresh_timer_callback);
}

void weather_monitor_long_press(gpio_port_t port, uint8_t pin, button_state_t state)
{
    UNUSED(port && pin);

    if (state == BUTTON_STATE_PRESSED)
    {
        timer_register(TIM7, WEATHER_MONITOR_BUTTON_TIMEOUT_MS, TIMER_RESCHEDULE_SINGLE,
                       TIMER_REGISTER, weather_monitor_long_press_timer_callback);
    }
    else
    {
        timer_register(TIM7, WEATHER_MONITOR_BUTTON_TIMEOUT_MS, TIMER_RESCHEDULE_SINGLE,
                       TIMER_UNREGISTER, weather_monitor_long_press_timer_callback);
    }
}

void weather_monitor_long_press_timer_callback(void)
{
    if (weather_monitor_refresh_rate < WEATHER_MONITOR_REFRESH_RATE_LAST)
    {
        weather_monitor_refresh_rate++;
    }
    else
    {
        weather_monitor_refresh_rate = WEATHER_MONITOR_REFRESH_RATE_FIRST;
    }

    weather_monitor_changed_refresh = TRUE;
    weather_monitor_refresh = WEATHER_MONITOR_REFRESH_DONE;

    timer_register(TIM7,
                   weather_monitor_get_refresh_rate_ms(weather_monitor_refresh_rate),
                   TIMER_RESCHEDULE_PERIOD,
                   TIMER_REGISTER,
                   weather_monitor_refresh_timer_callback);
}

void weather_monitor_refresh_timer_callback(void)
{
    weather_monitor_refresh = WEATHER_MONITOR_REFRESH_DONE;
}

uint32_t weather_monitor_get_refresh_rate_ms(weather_monitor_refresh_rate_t refresh)
{
    switch (refresh)
    {
        case WEATHER_MONITOR_REFRESH_RATE_156MS:
            return 156;

        case WEATHER_MONITOR_REFRESH_RATE_714MS:
            return 714;

        case WEATHER_MONITOR_REFRESH_RATE_3571MS:
            return 3571;

        case WEATHER_MONITOR_REFRESH_RATE_21428MS:
            return 21428;

        case WEATHER_MONITOR_REFRESH_RATE_85714MS:
            return 85714;

        case WEATHER_MONITOR_REFRESH_RATE_342857MS:
        default:
            return 342857;
    }
}
