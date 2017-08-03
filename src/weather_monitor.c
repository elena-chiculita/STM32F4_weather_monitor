#include "weather_monitor.h"
#include "button.h"
#include "gpio.h"
#include "lib.h"
#include "bme280.h"
#include "gpio_interrupt.h"
#include "timer.h"


volatile weather_monitor_display_t weather_monitor_display;
weather_monitor_display_t weather_monitor_display_old;


void weather_monitor_init(void)
{
    button_register(USER_BUTTON_1_PORT, USER_BUTTON_1_PIN, weather_monitor_display_state);
}

void weather_monitor_launch(void)
{
    int32_t temp, press, hum, div;
    uint16_t mod_hum;
    uint8_t mod_temp, mod_press;

    while (1)
    {
        bme280_poll(&press, &temp, &hum);

        if (weather_monitor_display_old != weather_monitor_display)
        {
            weather_monitor_display_old = weather_monitor_display;
            printf("\n");
        }
        printf("\n");

        if ((weather_monitor_display_old == WEATHER_MONITOR_DISPLAY_TEMP) ||
            (weather_monitor_display_old == WEATHER_MONITOR_DISPLAY_ALL))
        {
            div = temp / 100;
            mod_temp = (uint8_t)(temp - (div * 100));
            printf("%d.%d%cC ", div, mod_temp, 248);
        }

        if ((weather_monitor_display_old == WEATHER_MONITOR_DISPLAY_HUM) ||
            (weather_monitor_display_old == WEATHER_MONITOR_DISPLAY_ALL))
        {
            mod_hum = (((uint16_t)hum & 0x3FF) * 99) / 1023;
            div = hum >> 10;
            printf("%d.%d%%RH", div, mod_hum);

            if (weather_monitor_display_old == WEATHER_MONITOR_DISPLAY_ALL)
            {
                printf("\n");
            }
        }

        if ((weather_monitor_display_old == WEATHER_MONITOR_DISPLAY_PRESS) ||
            (weather_monitor_display_old == WEATHER_MONITOR_DISPLAY_ALL))
        {
            mod_press = (((uint8_t)press) * 99) / 255;
            div = press >> 8;
            printf("%d.%d Pa", div, mod_press);
        }

        delay(500);
    }
}

void weather_monitor_display_state(gpio_port_t port, uint8_t pin, button_state_t state)
{
    UNUSED(port && pin && state);

    if (weather_monitor_display < WEATHER_MONITOR_DISPLAY_PRESS)
    {
        weather_monitor_display++;
    }
    else
    {
        weather_monitor_display = WEATHER_MONITOR_DISPLAY_ALL;
    }
}
