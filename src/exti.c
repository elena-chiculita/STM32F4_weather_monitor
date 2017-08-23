#include "exti.h"
#include "hal_nvic.h"
#include "timer.h"
#include "util.h"


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
    /* disable interrupts */
    _disable_irq();

    set_exti_pr(line, EXTI_PR_TRIGGERED);

    gpio_interrupt_update(get_syscfg_exticr(line), line);

    /* enable interrupts */
    _enable_irq();
}

void _exti0_handler(void)
{
    exti_handler(0);
}
