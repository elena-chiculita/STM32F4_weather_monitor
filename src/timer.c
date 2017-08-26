#include "stm32f407.h"
#include "timer.h"
#include "hal_nvic.h"
#include "list.h"
#include "alloc.h"
#include "util.h"


volatile list_t timer_interrupt_list;


void timer_init(timer_t timer)
{
    irq_id_t irq_id;

    set_rcc_apb1enr_tim7en(RCC_CLK_EN);
    set_tim_psc(timer, timer_set_psc(timer));
    set_tim_arr(timer, 0);
    set_tim_cr1_arpe(timer, TIM_CR1_ARPE_BUFFERED);
    set_tim_cr1_opm(timer, TIM_CR1_OPM_NOT_STOPPED);
    set_tim_cr1_urs(timer, TIM_CR1_URS_ANY_REQUEST);
    set_tim_cr1_udis(timer, TIM_CR1_UDIS_UEV_ENABLE);
    set_tim_cr1_cen(timer, TIM_CR1_CEN_DISABLE);
    set_tim_dier_uie(timer, TIM_DIER_UIE_ENABLE);
    set_tim_egr_ug(timer, TIM_EGR_UG_UPDATE);
    set_tim_sr_uif(timer, TIM_SR_UIF_NO_UPDATE);

    irq_id = hal_nvic_get_tim_irq_id(timer);

    /* disable interrupts */
    _disable_irq();

    list_init((list_t *)&timer_interrupt_list);
    hal_nvic_enable(irq_id);
    set_nvic_icpr(irq_id);

    /* enable interrupts */
    _enable_irq();
}

void timer_reschedule(timer_t timer, uint16_t reschedule_period_ms)
{
    ASSERT(reschedule_period_ms > 0);

    /* disable interrupts */
    _disable_irq();

    set_tim_arr(timer, reschedule_period_ms);
    set_tim_egr_ug(timer, TIM_EGR_UG_UPDATE);
    set_tim_sr_uif(timer, TIM_SR_UIF_NO_UPDATE);
    set_nvic_icpr(hal_nvic_get_tim_irq_id(timer));

    /* enable interrupts */
    _enable_irq();
}

void timer_register(timer_t timer, uint16_t reschedule_period_ms, timer_reschedule_t reschedule,
                    timer_register_t reg, timer_callback_t fn)
{
    timer_interrupt_t *new;
    list_elem_t *elem;
    bool first_cb;

    ASSERT(fn != NULL);

    /* disable interrupts */
    _disable_irq();

    elem = list_get_elem((list_t *)&timer_interrupt_list, timer_interrupt_find_cb, (void *)fn);
    if (elem)
    {
        if (reg == TIMER_UNREGISTER)
        {
            list_remove((list_t *)&timer_interrupt_list, elem);
            free(elem);
        }
        else
        {
            list_remove((list_t *)&timer_interrupt_list, elem);

            ((timer_interrupt_t *)elem)->reschedule_period_ms = reschedule_period_ms;
            ((timer_interrupt_t *)elem)->reschedule_period_ms_left = reschedule_period_ms;

            timer_interrupt_list_parse_and_update(get_tim_cnt(timer));
            list_add_ordered((list_t *)&timer_interrupt_list, elem, timer_interrupt_find_pos);

            elem = list_get_first((list_t *)&timer_interrupt_list);
            if (elem)
            {
                timer_reschedule(timer, ((timer_interrupt_t *)elem)->reschedule_period_ms_left);
            }
        }
    }
    else
    {
        if (reg == TIMER_REGISTER)
        {
            if (list_is_empty((list_t *)&timer_interrupt_list))
            {
                first_cb = TRUE;
            }
            else
            {
                first_cb = FALSE;
            }

            new = malloc(sizeof(timer_interrupt_t));
            ASSERT(new != NULL);
            new->timer = timer;
            new->reschedule = reschedule;
            new->reschedule_period_ms = reschedule_period_ms;
            new->reschedule_period_ms_left = reschedule_period_ms;
            new->fn = fn;

            if (first_cb)
            {
                list_add_last((list_t *)&timer_interrupt_list, &new->elem);

                timer_reschedule(timer, new->reschedule_period_ms_left);
                set_tim_cr1_cen(timer, TIM_CR1_CEN_ENABLE);
            }
            else
            {
                timer_interrupt_list_parse_and_update(get_tim_cnt(timer));
                list_add_ordered((list_t *)&timer_interrupt_list, &new->elem, timer_interrupt_find_pos);

                elem = list_get_first((list_t *)&timer_interrupt_list);
                if (elem)
                {
                    timer_reschedule(timer, ((timer_interrupt_t *)elem)->reschedule_period_ms_left);
                }
            }
        }
    }

    /* enable interrupts */
    _enable_irq();
}

bool timer_interrupt_find_cb(list_elem_t *elem, void *arg)
{
    ASSERT((elem != NULL) && (arg != NULL));

    if (((timer_interrupt_t *)elem)->fn == (timer_callback_t)arg)
    {
        return TRUE;
    }

    return FALSE;
}

int timer_interrupt_find_pos(list_elem_t *elem, list_elem_t *new)
{
    ASSERT((elem != NULL) && (new != NULL));

    if (((timer_interrupt_t *)elem)->reschedule_period_ms_left <
        ((timer_interrupt_t *)new)->reschedule_period_ms_left)
    {
        return -1;
    }
    else if (((timer_interrupt_t *)elem)->reschedule_period_ms_left >
             ((timer_interrupt_t *)new)->reschedule_period_ms_left)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void timer_interrupt_update(list_elem_t *elem, void *arg)
{
    ASSERT((elem != NULL) && (arg != NULL));

    ASSERT(((timer_interrupt_t *)elem)->reschedule_period_ms_left >= *((uint16_t *)arg));
    ((timer_interrupt_t *)elem)->reschedule_period_ms_left -= *((uint16_t *)arg);
}

uint16_t timer_set_psc(timer_t timer)
{
    switch (timer)
    {
        case TIM7:
            return TIM6_7_PSC_1MS;

        default:
            ASSERT(FALSE);
            return 0;
    }
}

void timer_interrupt_list_parse_and_update(size_t reschedule_period_ms_left)
{
    list_elem_t *elem;
    timer_interrupt_t *tm;
    timer_callback_t fn;

    if (reschedule_period_ms_left == 0)
    {
        return;
    }

    list_parse((list_t *)&timer_interrupt_list, timer_interrupt_update, &reschedule_period_ms_left);

    while (1)
    {
        elem = list_get_first((list_t *)&timer_interrupt_list);
        if (elem == NULL)
        {
            break;
        }

        tm = (timer_interrupt_t *)elem;
        fn = tm->fn;

        if (tm->reschedule_period_ms_left == 0)
        {
            tm->reschedule_period_ms_left = tm->reschedule_period_ms;
            list_remove((list_t *)&timer_interrupt_list, elem);
            if (tm->reschedule == TIMER_RESCHEDULE_PERIOD)
            {
                list_add_ordered((list_t *)&timer_interrupt_list, elem, timer_interrupt_find_pos);
            }
            else
            {
                free(elem);
            }

            ASSERT(fn != NULL);
            fn();
        }
        else
        {
            break;
        }
    }
}

void _tim_handler(timer_t timer)
{
    list_elem_t *elem;

    elem = list_get_first((list_t *)&timer_interrupt_list);
    if (elem == NULL)
    {
        set_tim_cr1_cen(timer, TIM_CR1_CEN_DISABLE);

        return;
    }

    timer_interrupt_list_parse_and_update(((timer_interrupt_t *)elem)->reschedule_period_ms_left);

    elem = list_get_first((list_t *)&timer_interrupt_list);
    if (elem)
    {
        timer_reschedule(timer, ((timer_interrupt_t *)elem)->reschedule_period_ms_left);
    }
}

void _tim7_handler(void)
{
    /* disable interrupts */
    _disable_irq();

    set_tim_sr_uif(TIM7, TIM_SR_UIF_NO_UPDATE);

    _tim_handler(TIM7);

    /* enable interrupts */
    _enable_irq();
}
