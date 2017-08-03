#include "gpio.h"
#include "util.h"


void gpio_init(gpio_port_t port, uint8_t pin, gpio_moder_t moder,
               gpio_otyper_t otyper, gpio_ospeedr_t ospeedr, gpio_pupdr_t pupdr)
{
    ASSERT(pin <= 15);

    set_rcc_ahb1enr(port, RCC_CLK_EN);
    set_gpio_moder(port, pin, moder);
    set_gpio_otyper(port, pin, otyper);
    set_gpio_ospeedr(port, pin, ospeedr);
    set_gpio_pupdr(port, pin, pupdr);
}

bool gpio_get(gpio_port_t port, uint8_t pin)
{
    ASSERT(pin <= 15);

    if (get_gpio_moder(port, pin) == GPIO_MODER_INPUT)
    {
        return get_gpio_idr(port, pin);
    }
    else
    {
        return get_gpio_odr(port, pin);
    }
}

void gpio_set(gpio_port_t port, uint8_t pin)
{
    ASSERT(pin <= 15);
    ASSERT(get_gpio_moder(port, pin) == GPIO_MODER_OUTPUT);

    set_gpio_bsrr(port, pin, GPIO_BSRR_SET);
}

void gpio_clear(gpio_port_t port, uint8_t pin)
{
    ASSERT(pin <= 15);
    ASSERT(get_gpio_moder(port, pin) == GPIO_MODER_OUTPUT);

    set_gpio_bsrr(port, pin, GPIO_BSRR_RESET);
}

void gpio_set_value(gpio_port_t port, uint8_t pin, uint8_t value)
{
    ASSERT(pin <= 15);
    ASSERT(value <= 1);
    ASSERT(get_gpio_moder(port, pin) == GPIO_MODER_OUTPUT);

    set_gpio_bsrr(port, pin, (value) ? GPIO_BSRR_SET : GPIO_BSRR_RESET);
}

void gpio_toggle(gpio_port_t port, uint8_t pin)
{
    ASSERT(pin <= 15);
    ASSERT(get_gpio_moder(port, pin) == GPIO_MODER_OUTPUT);

    if (gpio_get(port, pin))
    {
        gpio_clear(port, pin);
    }
    else
    {
        gpio_set(port, pin);
    }
}
