#include "embedded_types.h"
#include "util.h"


__attribute__((used,interrupt("IRQ")))
void _nmi_handler(uint32_t *stack)
{
    UNUSED(stack);
    while (1);
}

__attribute__((used,interrupt("IRQ")))
void _hardfault_handler(uint32_t *stack)
{
    UNUSED(stack);
    while (1);
}

__attribute__((used,interrupt("IRQ")))
void _memmgtfault_handler(uint32_t *stack)
{
    UNUSED(stack);
    while (1);
}
__attribute__((used,interrupt("IRQ")))
void _busfault_handler(uint32_t *stack)
{
    UNUSED(stack);
    while (1);
}

__attribute__((used,interrupt("IRQ")))
void _usagefault_handler(uint32_t *stack)
{
    UNUSED(stack);
    while (1);
}

__attribute__((used,interrupt("IRQ")))
void _svcall_handler(uint32_t *stack)
{
    UNUSED(stack);
    while (1);
}

__attribute__((used,interrupt("IRQ")))
void _pendsv_handler(uint32_t *stack)
{
    UNUSED(stack);
    while (1);
}

__attribute__((used,interrupt("IRQ")))
void _systick_handler(uint32_t *stack)
{
    UNUSED(stack);
    while (1);
}
