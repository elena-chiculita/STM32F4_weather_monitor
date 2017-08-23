#ifndef _GPIO_INTERRUPT_H_
#define _GPIO_INTERRUPT_H_

#include "embedded_types.h"
#include "gpio.h"
#include "list.h"


typedef enum gpio_interrupt_edge_mask_tag
{
    GPIO_INTERRUPT_NONE = 0,
    GPIO_INTERRUPT_RISING = 1 << 0,
    GPIO_INTERRUPT_FALLING = 1 << 1,
    GPIO_INTERRUPT_ANY = GPIO_INTERRUPT_RISING | GPIO_INTERRUPT_FALLING
} gpio_interrupt_edge_mask_t;

typedef void (*gpio_interrupt_callback_t)(gpio_port_t, uint8_t); 

typedef struct gpio_interrupt_tag
{
    list_elem_t elem;
    gpio_port_t port;
    uint8_t pin;
    gpio_interrupt_edge_mask_t mask;
    gpio_interrupt_callback_t fn;
} gpio_interrupt_t;

typedef struct gpio_interrupt_find_tag
{
    gpio_port_t port;
    uint8_t pin;
    gpio_interrupt_edge_mask_t mask;
} gpio_interrupt_find_t;


void gpio_interrupt_init(void);
void gpio_interrupt_register(gpio_port_t port, uint8_t pin, gpio_interrupt_edge_mask_t mask,
                             gpio_interrupt_callback_t fn);
void gpio_interrupt_update(gpio_port_t port, uint8_t pin);
bool gpio_interrupt_find_elem(list_elem_t *elem, void *arg);

#endif /* _GPIO_INTERRUPT_H_ */
