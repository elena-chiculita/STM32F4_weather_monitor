#include "weather_monitor.h"
#include "weather_monitor_sync.h"
#include "weather_monitor_graphics.h"
#include "lib.h"


void weather_monitor_init(void)
{
    weather_monitor_sync_init();
    weather_monitor_graphics_init();
}

void weather_monitor_launch(void)
{
    weather_monitor_display_t state;
    char output[PRINTF_MAX_BUF];

    weather_monitor_start_refresh_timer();

    weather_monitor_graphics_update_samples();

    while (1)
    {
        state = weather_monitor_update_display_state();

        if (weather_monitor_get_poll_flag())
        {
            weather_monitor_graphics_update_samples();
        }
        else
        {
            weather_monitor_set_poll_flag();
        }

        weather_monitor_get_result_string(output, PRINTF_MAX_BUF, state);
        printf("%s", output);

        weather_monitor_graphics_display(state);

        weather_monitor_wait();
    }
}
