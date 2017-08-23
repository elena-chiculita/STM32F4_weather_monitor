#ifndef _IRQ_H_
#define _IRQ_H_

#include "embedded_types.h"
#include "stm32f407.h"


void _disable_irq(void);
void _enable_irq(void);
void cpu_halt(const char * const file, const uint32_t line, const char * const expr);
uint32_t core_reg_get_control(void);
void core_reg_set_control(control_priv_t mode);

#endif /* _IRQ_H_ */
