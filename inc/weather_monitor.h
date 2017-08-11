#ifndef _WEATHER_MONITOR_H_
#define _WEATHER_MONITOR_H_

#include "button.h"


#define WEATHER_MONITOR_BUTTON_PORT USER_BUTTON_1_PORT
#define WEATHER_MONITOR_BUTTON_PIN USER_BUTTON_1_PIN
#define WEATHER_MONITOR_BUTTON_TIMEOUT_MS 1000


typedef enum weather_monitor_display_tag
{
    WEATHER_MONITOR_DISPLAY_FIRST = 0,
    WEATHER_MONITOR_DISPLAY_TEMP = WEATHER_MONITOR_DISPLAY_FIRST,
    WEATHER_MONITOR_DISPLAY_HUM = 1,
    WEATHER_MONITOR_DISPLAY_PRESS = 2,
    WEATHER_MONITOR_DISPLAY_LAST = WEATHER_MONITOR_DISPLAY_PRESS
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

typedef enum weather_monitor_refresh_tag
{
    WEATHER_MONITOR_REFRESH_IN_PROGRESS = 0,
    WEATHER_MONITOR_REFRESH_DONE = 1
} weather_monitor_refresh_t;


void weather_monitor_init(void);
void weather_monitor_launch(void);
void weather_monitor_display_state(gpio_port_t port, uint8_t pin, button_state_t state);
void weather_monitor_long_press(gpio_port_t port, uint8_t pin, button_state_t state);
void weather_monitor_long_press_timer_callback(void);
void weather_monitor_refresh_timer_callback(void);
uint32_t weather_monitor_get_refresh_rate_ms(weather_monitor_refresh_rate_t refresh);

#endif /* _WEATHER_MONITOR_H_ */
