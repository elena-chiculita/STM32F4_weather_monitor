#include "lcd.h"
#include "hal_lcd.h"
#include "util.h"
#include "letters.c"


extern lcd_function_set_v_t V;


#define SCREEN_WIDTH 84
#define SCREEN_ROWS 6
#define SCREEN_SIZE (SCREEN_ROWS * SCREEN_WIDTH)
#define SCREEN_MAX_X 83
#define SCREEN_MAX_Y ((SCREEN_ROWS * 8) - 1)

#ifdef TARGET_TEST
#define SCREEN_ROWS_TEXT_LENGTH SCREEN_ROWS
#else /* TARGET_TEST */
#define SCREEN_ROWS_TEXT_LENGTH 2
#endif /* TARGET_TEST */

#if SCREEN_ROWS_TEXT_LENGTH > SCREEN_ROWS
#error Cannot have more text rows than screen rows
#endif

#define SCREEN_ROWS_TEXT_BEGIN 0
#define SCREEN_ROWS_TEXT_END (SCREEN_ROWS_TEXT_BEGIN + SCREEN_ROWS_TEXT_LENGTH - 1)
#define SCREEN_ROWS_GRAPHICS_BEGIN (SCREEN_ROWS_TEXT_END + 1)
#define SCREEN_ROWS_GRAPHICS_LENGTH (SCREEN_ROWS - SCREEN_ROWS_GRAPHICS_BEGIN)


static uint8_t X, Y, screen[SCREEN_SIZE];


void lcd_screen_erase(void)
{
    memset(screen, 0, sizeof(screen));
}

void lcd_init(void)
{
    hal_lcd_init();
    hal_lcd_reset();
    lcd_screen_erase();
    lcd_refresh();
    hal_lcd_send_command_function_set(LCD_FUNCTION_SET_PD_ACTIVE,
        LCD_FUNCTION_SET_V_HORIZONTAL, LCD_FUNCTION_SET_H_PRESERVE);
    hal_lcd_send_command_display_control(LCD_COMMAND_DISPLAY_DE_ALL_ON);
    hal_lcd_send_command_set_y_addr(0);
    hal_lcd_send_command_set_x_addr(0);
    hal_lcd_send_command_temp_control(LCD_TEMP_CONTROL_TC_0);
    hal_lcd_send_command_bias_system(4);
    hal_lcd_send_command_set_vop(50);
}

void lcd_set_contrast(uint8_t vop)
{
    hal_lcd_send_command_set_vop(vop);
}

void lcd_putb(uint8_t *buf, uint32_t size)
{
    uint32_t count, chars_left, pos;
    uint16_t max_pixels, pixels;
    uint8_t *head, *tail, is_new_line;

    ASSERT((((int8_t) Y) >= SCREEN_ROWS_TEXT_BEGIN) && (Y <= SCREEN_ROWS_TEXT_END));
    ASSERT(X < SCREEN_WIDTH);

    max_pixels = SCREEN_WIDTH * SCREEN_ROWS_TEXT_LENGTH;
    head = tail = buf;

    while (head < (buf + size))
    {
        while ((*tail != '\n') && ((uint32_t)(tail - buf) < size))
        {
            tail++;
        }

        if ((uint32_t)(tail - buf) == size)
        {
            is_new_line = 0;
        }
        else
        {
            is_new_line = 1;
        }
        tail--;

        count = 0;
        pos = tail - head + 1;

        while (count < pos)
        {
            chars_left = pos - count;
            pixels = max_pixels - ((Y * SCREEN_WIDTH) + X);

            lcd_display_chars(head, &chars_left, X, Y, &pixels);
            lcd_refresh();

            if ((chars_left == 0) && (pixels == 0))
            {
                X = 0;
                Y++;
                if (Y == SCREEN_ROWS_GRAPHICS_BEGIN)
                {
                    lcd_scroll_text();
                    lcd_refresh();
                    Y = SCREEN_ROWS_TEXT_END;
                }
            }
            else
            {
                pixels += X;
                while (pixels >= SCREEN_WIDTH)
                {
                    pixels -= SCREEN_WIDTH;
                    Y++;
                    if (Y == SCREEN_ROWS_GRAPHICS_BEGIN)
                    {
                        lcd_scroll_text();
                        lcd_refresh();
                        Y = SCREEN_ROWS_TEXT_END;
                    }
                }
                X = pixels;

                count += chars_left;
                head += chars_left;
            }
        }

        if (is_new_line)
        {
            tail++;
            X = 0;
            Y++;
            if (Y == SCREEN_ROWS_GRAPHICS_BEGIN)
            {
                lcd_scroll_text();
                lcd_refresh();
                Y = SCREEN_ROWS_TEXT_END;
                X = 0;
            }
        }

        tail++;
        head = tail;
    }
}

void lcd_display_chars(uint8_t *buf, uint32_t *size, uint8_t x, uint8_t y, uint16_t *pixels)
{
    uint32_t i;
    uint16_t count_chars, count_pixels;
    uint8_t j, c, char_width, char_spacing, *ptr, line_offset, offset; 

    ASSERT(V == LCD_FUNCTION_SET_V_HORIZONTAL);
    ASSERT(buf != NULL);
    ASSERT(size != NULL);
    ASSERT(pixels != NULL);

    count_chars = count_pixels = 0;
    line_offset = x;
    ptr = screen + (y * SCREEN_WIDTH);

    for (i = 0; i < *size; i++)
    {
        c = *(buf + i);
        if (c < 32)
        {
            /* non-printable char */
            count_chars++;
            continue;
        }
        char_width = chars_map[c - 32][0];
        char_spacing = ((line_offset + char_width) == SCREEN_WIDTH) ? 0 : 1;

        if ((count_pixels + char_width + char_spacing) > *pixels)
        {
            break;
        }

        if ((line_offset + char_width + char_spacing) > SCREEN_WIDTH)
        {
            ptr += SCREEN_WIDTH;
            offset = SCREEN_WIDTH - line_offset;
            if ((count_pixels + offset) > *pixels)
            {
                break;
            }
            count_pixels += offset;
            line_offset = 0;
        }

        for (j = 0; j < char_width; j++)
        {
            *(ptr + line_offset + j) = chars[chars_map[c - 32][1] + j];
        }

        line_offset += char_width + char_spacing;
        count_pixels += char_width + char_spacing;
        count_chars++;
    }

    *size = count_chars;
    *pixels = count_pixels;
}

void lcd_scroll_text(void)
{
    uint8_t line;

    for (line = SCREEN_ROWS_TEXT_BEGIN; line < SCREEN_ROWS_TEXT_END; line++)
    {
        memcpy(screen + (SCREEN_WIDTH * line), screen + (SCREEN_WIDTH * (line + 1)), SCREEN_WIDTH);
    }
    memset(screen + (SCREEN_WIDTH * SCREEN_ROWS_TEXT_END), 0, SCREEN_WIDTH);
}

void lcd_dot(uint8_t x, uint8_t y)
{
    uint8_t row, offset;

    ASSERT(x <= SCREEN_MAX_X);
    ASSERT(y <= SCREEN_MAX_Y);

    row = y / 8;
    offset = y % 8;

    *(screen + (row * SCREEN_MAX_X) + x) = 1 << offset;
}

void lcd_line(int16_t x0, int16_t y0, int16_t x1, int16_t y1)
{
    int16_t x, y, start_x, end_x, start_y, end_y, min_x, min_y, d_x, d_y;
    int32_t res, min_res;

    start_x = MIN(x0, x1);
    end_x = MAX(x0, x1);
    start_y = MIN(y0, y1);
    end_y = MAX(y0, y1);
    d_x = end_x - start_x;
    d_y = end_y - start_y;

    if (d_x > d_y)
    {
        for (x = start_x; x <= end_x; x++)
        {
            min_y = start_y;
            min_res = 0x7FFFFFFF;

            for (y = start_y; y <= end_y; y++)
            {
                res = ((x - x0) * (y1 - y0)) - ((y - y0) * (x1 - x0));

                if (res < 0)
                {
                    res = 0 - res;
                }
                if (res < min_res)
                {
                    min_res = res;
                    min_y = y;
                }
            }

            if ((x >= 0) && (min_y >= 0) && (x <= SCREEN_MAX_X) && (min_y <= SCREEN_MAX_Y))
            {
                *(screen + ((min_y / 8) * SCREEN_MAX_X) + x) |= 1 << (min_y % 8);
            }
        }
    }
    else
    {
        for (y = start_y; y <= end_y; y++)
        {
            min_x = start_x;
            min_res = 0x7FFFFFFF;

            for (x = start_x; x <= end_x; x++)
            {
                res = ((x - x0) * (y1 - y0)) - ((y - y0) * (x1 - x0));

                if (res < 0)
                {
                    res = 0 - res;
                }
                if (res < min_res)
                {
                    min_res = res;
                    min_x = x;
                }
            }

            if ((min_x >= 0) && (y >= 0) && (min_x <= SCREEN_MAX_X) && (y <= SCREEN_MAX_Y))
            {
                *(screen + ((y / 8) * SCREEN_MAX_X) + min_x) |= 1 << (y % 8);
            }
        }
    }
}

void lcd_circle(int16_t x0, int16_t y0, uint8_t r)
{
    int16_t x, y, y1, y2, y3, y4;
    int32_t res, min_res, square_r;

    square_r = r * r;
    y2 = y1 = (y0 - r);
    y3 = y4 = y0;

    for (x = (x0 - r); x <= (x0 + r); x++)
    {
        min_res = 0x7FFFFFFF;
        for (y = (y0 - r); y <= y0; y++)
        {
            res = (x - x0) * (x - x0) + (y - y0) * (y - y0) - square_r;

            if (res < 0)
            {
                res = 0 - res;
            }
            if (res < min_res)
            {
                min_res = res;
                y2 = y;
            }
        }

        if (x == (x0 - r))
        {
            y1 = y2;
            continue;
        }

        min_res = 0x7FFFFFFF;
        for (y = y0; y <= (y0 + r); y++)
        {
            res = (x - x0) * (x - x0) + (y - y0) * (y - y0) - square_r;

            if (res < 0)
            {
                res = 0 - res;
            }
            if (res < min_res)
            {
                min_res = res;
                y4 = y;
            }
        }

        lcd_line(x - 1, y1, x, y2);
        lcd_line(x - 1, y3, x, y4);

        y1 = y2;
        y3 = y4;
    }
}

void lcd_refresh(void)
{
    hal_lcd_send_data(screen, sizeof(screen));
}
