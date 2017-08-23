#include <stddef.h>
#include "irq.h"
#include "util.h"


volatile size_t count_irq_dis_en = 0;
volatile size_t count_sem = 0;


void _disable_irq(void)
{
    __asm("CPSID i");
    count_irq_dis_en++;
}

void _enable_irq(void)
{
    ASSERT(count_irq_dis_en != 0);

    count_irq_dis_en--;
    if (count_irq_dis_en == 0)
    {
        __asm("CPSIE i");
    }
}

void cpu_halt(const char * const file, const uint32_t line, const char * const expr)
{
    UNUSED(file);
    UNUSED(line);
    UNUSED(expr);

    /* disable interrupts */
    _disable_irq();

    while (1);
}
