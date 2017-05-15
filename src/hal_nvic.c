#include "hal_nvic.h"


void hal_nvic_enable(irq_id_t irq_id)
{
    set_nvic_iser(irq_id, NVIC_IRQ_SET);
}

void hal_nvic_disable(irq_id_t irq_id)
{
    set_nvic_icer(irq_id, NVIC_IRQ_CLEAR);
}
