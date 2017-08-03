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

void led_toggle(gpio_port_t port, uint8_t pin)
{
    gpio_toggle(port, pin);
}

void led_green_toggle_callback(void)
{
    led_toggle(LED_GREEN_PORT, LED_GREEN_PIN);
}

void led_orange_toggle_callback(void)
{
    led_toggle(LED_ORANGE_PORT, LED_ORANGE_PIN);
}

void led_red_toggle_callback(void)
{
    led_toggle(LED_RED_PORT, LED_RED_PIN);
}

void led_blue_toggle_callback(void)
{
    led_toggle(LED_BLUE_PORT, LED_BLUE_PIN);
}
