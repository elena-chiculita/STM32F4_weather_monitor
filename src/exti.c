#include "exti.h"
#include "hal_nvic.h"
#include "timer.h"


extern volatile list_t gpio_interrupt_list;


void exti_enable_line(gpio_port_t port, uint8_t line, gpio_interrupt_edge_mask_t mask)
{
    set_rcc_apb2enr_syscfgen(RCC_CLK_EN);
    set_syscfg_exticr(port, line);
    set_exti_imr(line, EXTI_IMR_NOT_MASKED);
    set_exti_emr(line, EXTI_EMR_NOT_MASKED);

    set_exti_rtsr(line, (mask & GPIO_INTERRUPT_RISING) ?
                  EXTI_RTSR_RISING_TRIGGER_EN : EXTI_RTSR_RISING_TRIGGER_DIS);
    set_exti_ftsr(line, (mask & GPIO_INTERRUPT_FALLING) ?
                  EXTI_FTSR_FALLING_TRIGGER_EN : EXTI_FTSR_FALLING_TRIGGER_DIS);

    /* disable interrupts */
    _disable_irq();

    hal_nvic_enable(hal_nvic_get_exti_irq_id(line));

    /* enable interrupts */
    _enable_irq();
}

void exti_handler(uint8_t line)
{
    gpio_port_t port;
    gpio_interrupt_line_t find_line;
    list_elem_t *elem;
    gpio_interrupt_callback_t fn;

    /* disable interrupts */
    _disable_irq();

    set_exti_pr(line, EXTI_PR_TRIGGERED);

    port = get_syscfg_exticr(line);
    find_line.port = port;
    find_line.pin = line;

    elem = NULL;

    do
    {
        elem = list_get_elems((list_t *)&gpio_interrupt_list, elem,
                              gpio_interrupt_find_line, (void *)&find_line);
        if (elem == NULL)
        {
            break;
        }

        fn = ((gpio_interrupt_t *)elem)->fn;
        ASSERT(fn != NULL);
        fn(((gpio_interrupt_t *)elem)->port, ((gpio_interrupt_t *)elem)->pin);
    } while (elem);

    /* enable interrupts */
    _enable_irq();
}

void _exti0_handler(void)
{
    exti_handler(0);
}
