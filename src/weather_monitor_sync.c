#include "weather_monitor_sync.h"
#include "button.h"
#include "timer.h"
#include "semaphore.h"
#include "util.h"


static volatile weather_monitor_display_t weather_monitor_new_display = WEATHER_MONITOR_DISPLAY_FIRST;
static weather_monitor_display_t weather_monitor_display = WEATHER_MONITOR_DISPLAY_FIRST;
static volatile weather_monitor_refresh_rate_t weather_monitor_refresh_rate = WEATHER_MONITOR_REFRESH_RATE_FIRST;
static volatile bool weather_monitor_changed_refresh = FALSE;
static volatile sem_handle_t weather_monitor_refresh_sem;


void weather_monitor_sem_init(void)
{
    weather_monitor_refresh_sem = sem_init(SEM_TYPE_BINARY, 0);
}

weather_monitor_display_t weather_monitor_update_display_state(void)
{
    if (weather_monitor_display != weather_monitor_new_display)
    {
        weather_monitor_display = weather_monitor_new_display;
    }

    return weather_monitor_display;
}

weather_monitor_refresh_rate_t weather_monitor_get_refresh_rate(void)
{
    return weather_monitor_refresh_rate;
}

void weather_monitor_start_refresh_timer(void)
{
    timer_register(TIM7,
                   weather_monitor_get_refresh_rate_ms(),
                   TIMER_RESCHEDULE_PERIOD,
                   TIMER_REGISTER,
                   weather_monitor_refresh_timer_callback);
}

void weather_monitor_update_refresh_timer(void)
{
    timer_register(TIM7,
                   weather_monitor_get_refresh_rate_ms(),
                   TIMER_RESCHEDULE_PERIOD,
                   TIMER_REGISTER,
                   weather_monitor_refresh_timer_callback);
}

void weather_monitor_refresh_timer_callback(void)
{
    sem_give(weather_monitor_refresh_sem);
}

void weather_monitor_wait(void)
{
    sem_take(weather_monitor_refresh_sem);
}

void weather_monitor_display_state(gpio_port_t port, uint8_t pin, button_state_t state)
{
    UNUSED(port && pin);

    if (state == BUTTON_STATE_PRESSED)
    {
        return;
    }

    if (weather_monitor_changed_refresh)
    {
        weather_monitor_changed_refresh = FALSE;
        return;
    }

    weather_monitor_update_refresh_timer();

    if (weather_monitor_new_display < WEATHER_MONITOR_DISPLAY_LAST)
    {
        weather_monitor_new_display++;
    }
    else
    {
        weather_monitor_new_display = WEATHER_MONITOR_DISPLAY_FIRST;
    }

    sem_give(weather_monitor_refresh_sem);
}

void weather_monitor_long_press(gpio_port_t port, uint8_t pin, button_state_t state)
{
    UNUSED(port && pin);

    if (state == BUTTON_STATE_PRESSED)
    {
        timer_register(TIM7,
                       WEATHER_MONITOR_BUTTON_TIMEOUT_MS,
                       TIMER_RESCHEDULE_PERIOD,
                       TIMER_REGISTER,
                       weather_monitor_long_press_timer_callback);
    }
    else
    {
        timer_register(TIM7,
                       WEATHER_MONITOR_BUTTON_TIMEOUT_MS,
                       TIMER_RESCHEDULE_PERIOD,
                       TIMER_UNREGISTER,
                       weather_monitor_long_press_timer_callback);
    }
}

void weather_monitor_long_press_timer_callback(void)
{
    if (weather_monitor_refresh_rate < WEATHER_MONITOR_REFRESH_RATE_LAST)
    {
        weather_monitor_refresh_rate++;
    }
    else
    {
        weather_monitor_refresh_rate = WEATHER_MONITOR_REFRESH_RATE_FIRST;
    }

    weather_monitor_update_refresh_timer();

    weather_monitor_changed_refresh = TRUE;

    sem_give(weather_monitor_refresh_sem);
}

uint32_t weather_monitor_get_refresh_rate_ms(void)
{
    switch (weather_monitor_refresh_rate)
    {
        case WEATHER_MONITOR_REFRESH_RATE_156MS:
            return 156;

        case WEATHER_MONITOR_REFRESH_RATE_714MS:
            return 714;

        case WEATHER_MONITOR_REFRESH_RATE_3571MS:
            return 3571;

        case WEATHER_MONITOR_REFRESH_RATE_21428MS:
            return 21428;

        case WEATHER_MONITOR_REFRESH_RATE_85714MS:
            return 85714;

        case WEATHER_MONITOR_REFRESH_RATE_342857MS:
        default:
            return 342857;
    }
}
