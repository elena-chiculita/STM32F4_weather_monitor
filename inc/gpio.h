#ifndef GPIO_H_
#define GPIO_H_

#include "stm32f407.h"


void gpio_init(gpio_port_t port, uint8_t pin, gpio_moder_t moder,
               gpio_otyper_t otyper, gpio_ospeedr_t ospeedr, gpio_pupdr_t pupdr);
bool gpio_get(gpio_port_t port, uint8_t pin);
void gpio_set(gpio_port_t port, uint8_t pin);
void gpio_clear(gpio_port_t port, uint8_t pin);
void gpio_set_value(gpio_port_t port, uint8_t pin, uint8_t val);

#endif /* GPIO_H_ */

