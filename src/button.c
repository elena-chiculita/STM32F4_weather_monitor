#include "button.h"
#include "gpio_interrupt.h"
#include "timer.h"
#include "list.h"
#include "alloc.h"


typedef struct button_store_tag
{
    list_elem_t elem;
    gpio_port_t port;
    uint8_t pin;
    bool is_timer_active;
    uint8_t timeout_no;
    button_callback_t fn;
    button_state_t state;
    button_state_t prev_state;
} button_store_t;

typedef struct button_store_find_port_pin_tag
{
    gpio_port_t port;
    uint8_t pin;
} button_store_find_port_pin_t;


volatile list_t button_list;
volatile bool button_timer_active = FALSE;


void button_init(void)
{
    list_init((list_t *)&button_list);
}

void button_register(gpio_port_t port, uint8_t pin, button_callback_t fn)
{
    button_store_find_port_pin_t button_find;
    button_store_t *new;
    list_elem_t *elem;

    new = malloc(sizeof(button_store_t));
    ASSERT(new != NULL);
    new->port = port;
    new->pin = pin;
    new->is_timer_active = FALSE;
    new->timeout_no = 0;
    new->fn = fn;
    new->prev_state = new->state = BUTTON_STATE_INIT;

    /* disable interrupts */
    _disable_irq();

    button_find.port = port;
    button_find.pin = pin;

    elem = list_get_elem((list_t *)&button_list, button_find_port_pin, (void *)&button_find);

    list_add_last((list_t *)&button_list, &new->elem);

    if (elem == NULL)
    {
        gpio_init(port, pin, GPIO_MODER_INPUT, GPIO_OTYPER_PUSH_PULL, GPIO_OSPEEDR_VERY_HIGH, GPIO_PUPDR_NO_PULL);
        gpio_interrupt_register(port, pin, GPIO_INTERRUPT_ANY, button_gpio_interrupt_callback);
    }

    /* enable interrupts */
    _enable_irq();
}

void button_gpio_interrupt_callback(gpio_port_t port, uint8_t pin)
{
    button_store_t *bs;
    list_elem_t *elem;
    button_store_find_port_pin_t button_find;

    button_find.port = port;
    button_find.pin = pin;

    elem = NULL;

    do
    {
        elem = list_get_elems((list_t *)&button_list, elem,
                              button_find_port_pin, (void *)&button_find);
        if (elem == NULL)
        {
            break;
        }

        bs = (button_store_t *)elem;
        if (bs->is_timer_active == FALSE)
        {
            bs->is_timer_active = TRUE;
            bs->state = BUTTON_STATE_PRESSED;
        }
        bs->timeout_no = 0;

    } while (elem);

    if (button_timer_active == FALSE)
    {
        timer_register(TIM7, BUTTON_TIMEOUT_MS, TIMER_RESCHEDULE_PERIOD, TIMER_REGISTER, button_timer_callback);
        button_timer_active = TRUE;
    }
}

void button_timer_callback(void)
{
    button_store_t *bs;
    list_elem_t *elem;
    bool found = FALSE, count = 0;

    elem = list_get_first((list_t *)&button_list);
    while (elem)
    {
        bs = (button_store_t *)elem;
        if (bs->is_timer_active == TRUE)
        {
            found = TRUE;
            count++;
            bs->timeout_no++;
            if (bs->timeout_no == BUTTON_TIMEOUT_NO)
            {
                bs->is_timer_active = FALSE;
                bs->timeout_no = 0;
                count--;

                bs->state = (gpio_get(bs->port, bs->pin) == TRUE) ? BUTTON_STATE_PRESSED : BUTTON_STATE_RELEASED;

                ASSERT(bs->fn != NULL);

                if (bs->prev_state == bs->state)
                {
                    if (bs->state == BUTTON_STATE_PRESSED)
                    {
                        bs->fn(bs->port, bs->pin, BUTTON_STATE_RELEASED);
                    }
                    else if (bs->state == BUTTON_STATE_RELEASED)
                    {
                        bs->fn(bs->port, bs->pin, BUTTON_STATE_PRESSED);
                    }
                }

                bs->prev_state = bs->state;
                bs->fn(bs->port, bs->pin, bs->state);
            }
        }

        elem = list_get_next_elem(elem);
    }

    if ((found == TRUE) && (count == 0))
    {
        timer_register(TIM7, BUTTON_TIMEOUT_MS, TIMER_RESCHEDULE_PERIOD, TIMER_UNREGISTER, button_timer_callback);
        button_timer_active = FALSE;
    }
}

bool button_find_port_pin(list_elem_t *elem, void *arg)
{
    ASSERT((elem != NULL) && (arg != NULL));

    if ((((button_store_t *)elem)->port == ((button_store_find_port_pin_t *)arg)->port) &&
        (((button_store_t *)elem)->pin == ((button_store_find_port_pin_t *)arg)->pin))
    {
        return TRUE;
    }

    return FALSE;
}
