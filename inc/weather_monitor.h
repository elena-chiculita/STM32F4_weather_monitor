#ifndef _WEATHER_MONITOR_H_
#define _WEATHER_MONITOR_H_

#include "button.h"


#define WEATHER_MONITOR_BUTTON_PORT USER_BUTTON_1_PORT
#define WEATHER_MONITOR_BUTTON_PIN USER_BUTTON_1_PIN


void weather_monitor_init(void);
void weather_monitor_launch(void);

#endif /* _WEATHER_MONITOR_H_ */
