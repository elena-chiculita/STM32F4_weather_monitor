#ifndef _EXTI_H_
#define _EXTI_H_

#include "embedded_types.h"
#include "gpio.h"
#include "gpio_interrupt.h"


void exti_enable_line(gpio_port_t port, uint8_t line, gpio_interrupt_edge_mask_t mask);

#endif /* _EXTI_H_ */
