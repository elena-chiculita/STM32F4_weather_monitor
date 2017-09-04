#ifndef _TIMER_H_
#define _TIMER_H_

#include "embedded_types.h"
#include "stm32f407.h"
#include "list.h"


#define TIM6_7_PSC_1MS 16100


typedef enum timer_register_tag
{
    TIMER_UNREGISTER = 0,
    TIMER_REGISTER = 1
} timer_register_t;

typedef enum timer_reschedule_tag
{
    TIMER_RESCHEDULE_SINGLE = 0,
    TIMER_RESCHEDULE_PERIOD = 1
} timer_reschedule_t;

typedef void (*timer_callback_t)(void);

typedef struct timer_interrupt_tag
{
    list_elem_t elem;
    timer_t timer;
    timer_reschedule_t reschedule;
    uint32_t reschedule_period_ms;
    uint32_t reschedule_period_ms_left;
    timer_callback_t fn;
} timer_interrupt_t;

typedef uint16_t timer_ms_size_t;


#define MAX_TIMER_HW_CNT 0xFFFF


void timer_init(timer_t timer);
void timer_reschedule(timer_t timer, timer_ms_size_t reschedule_period_ms);
void timer_register(timer_t timer, uint32_t reschedule_period_ms, timer_reschedule_t reschedule,
                    timer_register_t reg, timer_callback_t fn);
bool timer_interrupt_find_cb(list_elem_t *elem, void *arg);
int timer_interrupt_find_pos(list_elem_t *elem, list_elem_t *new);
void timer_interrupt_update(list_elem_t *elem, void *arg);
timer_ms_size_t timer_set_psc(timer_t timer);
void timer_interrupt_list_parse_and_update(timer_ms_size_t passed_period_ms);
void _tim_handler(timer_t timer);
void _tim7_handler(void);

#endif /* _TIMER_H_ */
