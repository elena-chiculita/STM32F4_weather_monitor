#ifndef HAL_NVIC_H_
#define HAL_NVIC_H_

#include "stm32f407.h"


void hal_nvic_enable(irq_id_t irq_id);
void hal_nvic_disable(irq_id_t irq_id);

#endif /* HAL_NVIC_H_ */
