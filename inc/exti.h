#ifndef _EXTI_H_
#define _EXTI_H_

#include "embedded_types.h"
#include "gpio.h"


void exti_enable_line(gpio_port_t port, uint8_t line);

#endif /* _EXTI_H_ */
