#ifndef LED_H_
#define LED_H_

#include "embedded_types.h"
#include "stm32f407.h"


#define LED_GREEN_PIN 12
#define LED_ORANGE_PIN 13
#define LED_RED_PIN 14
#define LED_BLUE_PIN 15

#define LED_GREEN_PORT GPIOD
#define LED_ORANGE_PORT GPIOD
#define LED_RED_PORT GPIOD
#define LED_BLUE_PORT GPIOD

void led_init(gpio_port_t port, uint8_t pin);
void led_on(gpio_port_t port, uint8_t pin);
void led_off(gpio_port_t port, uint8_t pin);

#endif /* LED_H_ */

