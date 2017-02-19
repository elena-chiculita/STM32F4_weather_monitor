#include "led.h"
#include "gpio.h"


void led_init(gpio_port_t port, uint8_t pin)
{
    gpio_init(port, pin, GPIO_MODER_OUTPUT, GPIO_OTYPER_PUSH_PULL,
              GPIO_OSPEEDR_VERY_HIGH, GPIO_PUPDR_NO_PULL);
}

void led_on(gpio_port_t port, uint8_t pin)
{
    gpio_set(port, pin);
}

void led_off(gpio_port_t port, uint8_t pin)
{
    gpio_clear(port, pin);
}

