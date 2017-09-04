#ifndef _WEATHER_MONITOR_SYNC_H_
#define _WEATHER_MONITOR_SYNC_H_

#include "button.h"


#define WEATHER_MONITOR_BUTTON_TIMEOUT_MS 1500


typedef enum weather_monitor_display_tag
{
    WEATHER_MONITOR_DISPLAY_FIRST = 0,
    WEATHER_MONITOR_DISPLAY_TEMP = WEATHER_MONITOR_DISPLAY_FIRST,
    WEATHER_MONITOR_DISPLAY_HUM = 1,
    WEATHER_MONITOR_DISPLAY_PRESS = 2,
    WEATHER_MONITOR_DISPLAY_LAST = WEATHER_MONITOR_DISPLAY_PRESS,
} weather_monitor_display_t;

typedef enum weather_monitor_refresh_rate_tag
{
    WEATHER_MONITOR_REFRESH_RATE_FIRST = 0,
    WEATHER_MONITOR_REFRESH_RATE_156MS = WEATHER_MONITOR_REFRESH_RATE_FIRST,
    WEATHER_MONITOR_REFRESH_RATE_714MS = 1,
    WEATHER_MONITOR_REFRESH_RATE_3571MS = 2,
    WEATHER_MONITOR_REFRESH_RATE_21428MS = 3,
    WEATHER_MONITOR_REFRESH_RATE_85714MS = 4,
    WEATHER_MONITOR_REFRESH_RATE_342857MS = 5,
    WEATHER_MONITOR_REFRESH_RATE_LAST = WEATHER_MONITOR_REFRESH_RATE_342857MS
} weather_monitor_refresh_rate_t;


void weather_monitor_sync_init(void);
weather_monitor_display_t weather_monitor_get_display_state(void);
bool weather_monitor_get_poll_flag(void);
void weather_monitor_set_poll_flag(void);
weather_monitor_display_t weather_monitor_update_display_state(void);
weather_monitor_refresh_rate_t weather_monitor_get_refresh_rate(void);
void weather_monitor_start_refresh_timer(void);
void weather_monitor_update_refresh_timer(void);
void weather_monitor_refresh_timer_callback(void);
void weather_monitor_wait(void);
void weather_monitor_display_state(gpio_port_t port, uint8_t pin, button_state_t state);
void weather_monitor_long_press(gpio_port_t port, uint8_t pin, button_state_t state);
void weather_monitor_long_press_timer_callback(void);
uint32_t weather_monitor_get_refresh_rate_ms(void);
const char* weather_monitor_get_refresh_rate_string(void);

#endif /* _WEATHER_MONITOR_SYNC_H_ */
