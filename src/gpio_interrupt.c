#include "gpio_interrupt.h"
#include "exti.h"
#include "alloc.h"


volatile list_t gpio_interrupt_list;


void gpio_interrupt_init(void)
{
    list_init((list_t *)&gpio_interrupt_list);
}

void gpio_interrupt_register(gpio_port_t port, uint8_t pin, gpio_interrupt_edge_mask_t mask,
                             gpio_interrupt_callback_t fn)
{
    gpio_interrupt_t *new;
    list_elem_t *elem, *tmp;
    gpio_interrupt_line_t find_line;
    bool found = FALSE;

    ASSERT(fn != NULL);

    find_line.port = port;
    find_line.pin = pin;

    /* disable interrupts */
    _disable_irq();

    elem = NULL;

    do
    {
        elem = list_get_elems((list_t *)&gpio_interrupt_list, elem,
                              gpio_interrupt_find_line, (void *)&find_line);
        if (elem == NULL)
        {
            break;
        }

        if (mask == GPIO_INTERRUPT_NONE)
        {
            tmp = list_get_next_elem(elem);
            list_remove((list_t *)&gpio_interrupt_list, elem);
            free(elem);
            elem = tmp;
        }
        else
        {
            if (found == FALSE)
            {
                found = TRUE;
            }
        }
    } while (elem);

    if (mask == GPIO_INTERRUPT_NONE)
    {
        /* enable interrupts */
        _enable_irq();

        return;
    }

    new = malloc(sizeof(gpio_interrupt_t));
    ASSERT(new != NULL);
    new->port = port;
    new->pin = pin;
    new->mask = mask;
    new->fn = fn;
    list_add_last((list_t *)&gpio_interrupt_list, &new->elem);

    if (found == FALSE)
    {
        exti_enable_line(port, pin);
    }

    /* enable interrupts */
    _enable_irq();
}

bool gpio_interrupt_find_line(list_elem_t *elem, void *arg)
{
    ASSERT((elem != NULL) && (arg != NULL));

    if (((((gpio_interrupt_t *)elem)->port) == ((gpio_interrupt_line_t *)arg)->port) &&
        ((((gpio_interrupt_t *)elem)->pin) == ((gpio_interrupt_line_t *)arg)->pin))
    {
        return TRUE;
    }

    return FALSE;
}
