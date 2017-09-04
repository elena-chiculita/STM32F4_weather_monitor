#ifndef _WEATHER_MONITOR_GRAPHICS_H_
#define _WEATHER_MONITOR_GRAPHICS_H_

#include <stddef.h>
#include "lcd.h"


#define WEATHER_MONITOR_SAMPLE_NO SCREEN_WIDTH


void weather_monitor_graphics_init(void);
void weather_monitor_graphics_update_samples(void);
void weather_monitor_graphics_display(weather_monitor_display_t state);
void weather_monitor_get_result_string(char *output, size_t size, weather_monitor_display_t state);

#endif /* _WEATHER_MONITOR_GRAPHICS_H_ */
