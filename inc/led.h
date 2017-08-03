#ifndef _LED_H_
#define _LED_H_

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

#define LED_GREEN_TIMEOUT_MS 7000
#define LED_ORANGE_TIMEOUT_MS 5000
#define LED_RED_TIMEOUT_MS 2000
#define LED_BLUE_TIMEOUT_MS 5000


void led_init(gpio_port_t port, uint8_t pin);
void led_on(gpio_port_t port, uint8_t pin);
void led_off(gpio_port_t port, uint8_t pin);
void led_toggle(gpio_port_t port, uint8_t pin);
void led_green_toggle_callback(void);
void led_orange_toggle_callback(void);
void led_red_toggle_callback(void);
void led_blue_toggle_callback(void);

#endif /* _LED_H_ */

