#ifndef _HAL_NVIC_H_
#define _HAL_NVIC_H_

#include "stm32f407.h"


void hal_nvic_enable(irq_id_t irq_id);
void hal_nvic_disable(irq_id_t irq_id);
irq_id_t hal_nvic_get_exti_irq_id(uint8_t line);
irq_id_t hal_nvic_get_tim_irq_id(timer_t timer);

#endif /* _HAL_NVIC_H_ */
