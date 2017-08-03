#ifndef _WEATHER_MONITOR_H_
#define _WEATHER_MONITOR_H_

#include "embedded_types.h"
#include "stm32f407.h"
#include "button.h"


typedef enum weather_monitor_display_tag
{
    WEATHER_MONITOR_DISPLAY_ALL = 0,
    WEATHER_MONITOR_DISPLAY_TEMP = 1,
    WEATHER_MONITOR_DISPLAY_HUM = 2,
    WEATHER_MONITOR_DISPLAY_PRESS = 3
} weather_monitor_display_t;


void weather_monitor_init(void);
void weather_monitor_launch(void);
void weather_monitor_display_state(gpio_port_t port, uint8_t pin, button_state_t state);

#endif /* _WEATHER_MONITOR_H_ */
