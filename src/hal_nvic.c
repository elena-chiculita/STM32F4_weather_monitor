#include "hal_nvic.h"
#include "util.h"


void hal_nvic_enable(irq_id_t irq_id)
{
    set_nvic_iser(irq_id);
}

void hal_nvic_disable(irq_id_t irq_id)
{
    set_nvic_icer(irq_id);
}

irq_id_t hal_nvic_get_exti_irq_id(uint8_t line)
{
    ASSERT(line < 15);

    switch (line)
    {
        case 0:
            return IRQ_ID_EXTI0;

        case 1:
            return IRQ_ID_EXTI1;

        case 2:
            return IRQ_ID_EXTI2;

        case 3:
            return IRQ_ID_EXTI3;

        case 4:
            return IRQ_ID_EXTI4;

        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            return IRQ_ID_EXTI9_5;

        default:
            return IRQ_ID_EXTI15_10;
    }
}

irq_id_t hal_nvic_get_tim_irq_id(timer_t timer)
{
    switch (timer)
    {
        case TIM1:
            return IRQ_ID_TIM1_CC;

        case TIM2:
            return IRQ_ID_TIM2;

        case TIM3:
            return IRQ_ID_TIM3;

        case TIM4:
            return IRQ_ID_TIM4;

        case TIM5:
            return IRQ_ID_TIM5;

        case TIM6:
            return IRQ_ID_TIM6_DAC;

        case TIM7:
            return IRQ_ID_TIM7;

        case TIM8:
            return IRQ_ID_TIM8_CC;

        case TIM9:
            return IRQ_ID_TIM1_BRK_TIM9;

        case TIM10:
            return IRQ_ID_TIM1_UP_TIM10;

        case TIM11:
            return IRQ_ID_TIM1_TRG_COM_TIM11;

        case TIM12:
            return IRQ_ID_TIM8_BRK_TIM12;

        case TIM13:
            return IRQ_ID_TIM8_UP_TIM13;

        case TIM14:
        default:
            return IRQ_ID_TIM8_TRG_COM_TIM14;
    }
}
