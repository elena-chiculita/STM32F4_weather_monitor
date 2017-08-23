#include "weather_monitor.h"
#include "weather_monitor_sync.h"
#include "bme280.h"
#include "lib.h"
#include "util.h"


void weather_monitor_init(void)
{
    weather_monitor_sem_init();
    button_register(WEATHER_MONITOR_BUTTON_PORT, WEATHER_MONITOR_BUTTON_PIN, weather_monitor_display_state);
    button_register(WEATHER_MONITOR_BUTTON_PORT, WEATHER_MONITOR_BUTTON_PIN, weather_monitor_long_press);
}

void weather_monitor_launch(void)
{
    weather_monitor_display_t state;
    int32_t temp, press, hum, div;
    uint16_t mod_hum;
    uint8_t mod_temp, mod_press;

    weather_monitor_start_refresh_timer();

    while (1)
    {
        printf("\n%d ms\n", weather_monitor_get_refresh_rate_ms());

        bme280_poll(&press, &temp, &hum);

        state = weather_monitor_update_display_state();
        switch (state)
        {
            case WEATHER_MONITOR_DISPLAY_TEMP:
                div = temp / 100;
                mod_temp = (uint8_t)(temp - (div * 100));
                printf("%d.%d %cC", div, mod_temp, 248);
                break;

            case WEATHER_MONITOR_DISPLAY_HUM:
                mod_hum = (((uint16_t)hum & 0x3FF) * 99) / 1023;
                div = hum >> 10;
                printf("%d.%d %%RH", div, mod_hum);
                break;

            case WEATHER_MONITOR_DISPLAY_PRESS:
                press >>= 8;
                div = press / 100;
                mod_press = (uint8_t)(press - (div * 100));
                printf("%d.%d hPa", div, mod_press);
                break;

            default:
                ASSERT(FALSE);
                break;
        }

        weather_monitor_wait();
    }
}
