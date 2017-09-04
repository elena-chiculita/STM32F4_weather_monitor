#include "weather_monitor.h"
#include "weather_monitor_sync.h"
#include "weather_monitor_graphics.h"
#include "bme280.h"
#include "lib.h"
#include "util.h"


static int32_t samples[WEATHER_MONITOR_DISPLAY_LAST + 1][WEATHER_MONITOR_SAMPLE_NO];
static int32_t min_val[WEATHER_MONITOR_DISPLAY_LAST + 1];
static int32_t max_val[WEATHER_MONITOR_DISPLAY_LAST + 1];


void weather_monitor_graphics_init()
{
    int32_t temp, press, hum;
    uint8_t i;

    bme280_poll(&press, &temp, &hum);

    for (i = 0; i < WEATHER_MONITOR_SAMPLE_NO; i++)
    {
        samples[WEATHER_MONITOR_DISPLAY_TEMP][i] = temp;
        samples[WEATHER_MONITOR_DISPLAY_HUM][i] = hum;
        samples[WEATHER_MONITOR_DISPLAY_PRESS][i] = press;
    }

    min_val[WEATHER_MONITOR_DISPLAY_TEMP] = max_val[WEATHER_MONITOR_DISPLAY_TEMP] = temp;
    min_val[WEATHER_MONITOR_DISPLAY_HUM] = max_val[WEATHER_MONITOR_DISPLAY_HUM] = hum;
    min_val[WEATHER_MONITOR_DISPLAY_PRESS] = max_val[WEATHER_MONITOR_DISPLAY_PRESS] = press;
}

void weather_monitor_graphics_update_samples()
{
    weather_monitor_display_t state;
    int32_t temp, press, hum;
    uint8_t i;

    bme280_poll(&press, &temp, &hum);
    
    for (state = WEATHER_MONITOR_DISPLAY_FIRST; state <= WEATHER_MONITOR_DISPLAY_LAST; state++)
    {
        memmove((uint8_t *)&samples[state][0],
                (uint8_t *)&samples[state][1],
                (WEATHER_MONITOR_SAMPLE_NO - 1) * sizeof(samples[state][0]));

        if (state == WEATHER_MONITOR_DISPLAY_TEMP)
        {
            samples[state][WEATHER_MONITOR_SAMPLE_NO - 1] = temp;
        }
        else if (state == WEATHER_MONITOR_DISPLAY_HUM)
        {
            samples[state][WEATHER_MONITOR_SAMPLE_NO - 1] = hum;
        }
        else
        {
            samples[state][WEATHER_MONITOR_SAMPLE_NO - 1] = press;
        }

        min_val[state] = max_val[state] = samples[state][0];

        for (i = 1; i < WEATHER_MONITOR_SAMPLE_NO; i++)
        {
            if (min_val[state] > samples[state][i])
            {
                min_val[state] = samples[state][i];
            }

            if (max_val[state] < samples[state][i])
            {
                max_val[state] = samples[state][i];
            }
        }
    }
}

void weather_monitor_graphics_display(weather_monitor_display_t state)
{
    uint8_t x0 = 0, y0 = 0, y, i;

    lcd_clear_graphics();

    for (i = 0; i < WEATHER_MONITOR_SAMPLE_NO; i++)
    {
        if (min_val[state] == max_val[state])
        {
            y = SCREEN_MAX_Y / 2;
        }
        else
        {
            if (samples[state][i] == min_val[state])
            {
                y = SCREEN_MAX_Y;
            }
            else if (samples[state][i] == max_val[state])
            {
                y = 0;
            }
            else
            {
                y = (uint8_t)((SCREEN_MAX_Y * (max_val[state] - samples[state][i])) /
                              (max_val[state] - min_val[state]));
            }
        }

        if (i > 0)
        {
            lcd_line(x0, y0, i, y);
        }

        x0 = i;
        y0 = y;
    }

    lcd_refresh();
}

void weather_monitor_get_result_string(char *output, size_t size, weather_monitor_display_t state)
{
    char unit[6], mod_str[3];
    size_t count, total;
    int32_t div;
    uint8_t mod, screen_left_chars_no, screen_right_chars_no, screen_chars[9], spaces_no, n;

    ASSERT(output != NULL);

    switch (state)
    {
        case WEATHER_MONITOR_DISPLAY_TEMP:
            snprintf(unit, sizeof(unit) - 1, "%cC", 248);
            break;

        case WEATHER_MONITOR_DISPLAY_HUM:
            snprintf(unit, sizeof(unit) - 1, "%%RH");
            break;

        case WEATHER_MONITOR_DISPLAY_PRESS:
            snprintf(unit, sizeof(unit) - 1, "hPa");
            break;

        default:
            ASSERT(FALSE);
            break;
    }

    total = count = 0;

    div = samples[state][WEATHER_MONITOR_SAMPLE_NO - 1] / 100;
    mod = samples[state][WEATHER_MONITOR_SAMPLE_NO - 1] - (div * 100);
    if ((int8_t)mod < 0)
    {
        mod = 0 - mod;
    }
    if (mod < 10)
    {
        mod_str[0] = '0';
        mod_str[1] = '\0';
    }
    else
    {
        mod_str[0] = '\0';
    }

    count = snprintf(output, size - total, "\n%d.%s%d %s", div, mod_str, mod, unit);
    output += count;
    total += count;

    screen_left_chars_no = count - 2;
    screen_right_chars_no = strlen(weather_monitor_get_refresh_rate_string());
    spaces_no = ((SCREEN_WIDTH / 6) - screen_left_chars_no - screen_right_chars_no) * 2;

    while (spaces_no)
    {
        count = snprintf(output, size - total, " ");
        output += count;
        total += count;
        spaces_no--;
    }

    count = snprintf(output, size - total, "%s\n", weather_monitor_get_refresh_rate_string());
    output += count;
    total += count;

    div = min_val[state] / 100;
    int_to_str(div, screen_chars, &screen_left_chars_no);
    mod = min_val[state] - (div * 100);
    if ((int8_t)mod < 0)
    {
        mod = 0 - mod;
    }
    if (mod < 10)
    {
        mod_str[0] = '0';
        mod_str[1] = '\0';
    }
    else
    {
        mod_str[0] = '\0';
    }

    count = snprintf(output, size - total, "%d.%s%d", div, mod_str, mod);
    output += count;
    total += count;

    div = max_val[state] / 100;
    int_to_str(div, screen_chars, &screen_right_chars_no);
    mod = max_val[state] - (div * 100);
    if ((int8_t)mod < 0)
    {
        mod = 0 - mod;
    }
    if (mod < 10)
    {
        mod_str[0] = '0';
        mod_str[1] = '\0';
    }
    else
    {
        mod_str[0] = '\0';
    }

    spaces_no = (8 - screen_left_chars_no - screen_right_chars_no) * 2;

    n = spaces_no / 2;
    while (n)
    {
        count = snprintf(output, size - total, " ");
        output += count;
        total += count;
        n--;
    }

    count = snprintf(output, size - total, "-");
    output += count;
    total += count;

    n = spaces_no / 2;
    while (n)
    {
        count = snprintf(output, size - total, " ");
        output += count;
        total += count;
        n--;
    }

    snprintf(output, size - total, "%d.%s%d", div, mod_str, mod);
}
