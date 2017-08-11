#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "embedded_types.h"
#include "stm32f407.h"
#include "list.h"


#define USER_BUTTON_1_PORT GPIOA
#define USER_BUTTON_1_PIN 0

#define BUTTON_TIMEOUT_MS 10
#define BUTTON_TIMEOUT_NO 3


typedef enum button_state_tag
{
    BUTTON_STATE_INIT = 0,
    BUTTON_STATE_PRESSED = 1,
    BUTTON_STATE_RELEASED = 2
} button_state_t;

typedef void (*button_callback_t)(gpio_port_t, uint8_t, button_state_t);


void button_init(void);
void button_register(gpio_port_t port, uint8_t pin, button_callback_t fn);
void button_gpio_interrupt_callback(gpio_port_t port, uint8_t pin);
void button_timer_callback(void);
bool button_find_port_pin(list_elem_t *elem, void *arg);

#endif /* _BUTTON_H_ */
