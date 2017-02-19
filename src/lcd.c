#include "lcd.h"
#include "hal_lcd.h"
#include "util.h"
#include "letters.c"

extern lcd_function_set_v_t V;

#define SCREEN_ROWS 6
#define SCREEN_ROWS_TEXT_BEGIN 0
#define SCREEN_ROWS_TEXT_END 1
#define SCREEN_ROWS_GRAPHICS_BEGIN 2
#define SCREEN_ROWS_GRAPHICS_END 5
#define SCREEN_MAX_Y (SCREEN_ROWS * 8)
#define SCREEN_MAX_X 84
#define SCREEN_SIZE (SCREEN_ROWS * SCREEN_MAX_X)

static uint8_t screen[SCREEN_SIZE];
uint8_t X, Y;


void lcd_screen_erase(void)
{
    uint16_t i;

    for (i = 0; i < SCREEN_SIZE; i++)
    {
        screen[i] = 0;
    }
}

void lcd_init(void)
{
    hal_lcd_init();
    hal_lcd_reset();
    lcd_screen_erase();
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

void lcd_display_chars(uint8_t y_addr, uint8_t x_addr, uint8_t *buf, uint16_t size)
{
    uint16_t i;
    uint8_t j, c, char_width, line_offset, line;
    uint8_t *ptr;

    ASSERT(V == LCD_FUNCTION_SET_V_HORIZONTAL);
    ASSERT((((int8_t) y_addr) >= SCREEN_ROWS_TEXT_BEGIN) && (y_addr <= SCREEN_ROWS_TEXT_END));
    ASSERT(x_addr < SCREEN_MAX_X);
    ASSERT(buf != NULL);

    line_offset = x_addr;
    line = y_addr;
    ptr = screen + (y_addr * SCREEN_MAX_X);

    for (i = 0; i < size; i++)
    {
        c = *(buf + i);
        if (c < 32)
        {
            continue;
        }
        char_width = chars_map[c - 32][0];

        if (! ((line_offset + char_width) < SCREEN_MAX_X))
        {
            ptr += SCREEN_MAX_X;
            line++;
            X = line_offset = 0;

            if (line > SCREEN_ROWS_TEXT_END)
            {
                Y = 0;
                break;
            }

            Y++;
        }

        for (j = 0; j < char_width; j++)
        {
            *(ptr + line_offset + j) = chars[chars_map[c - 32][1] + j];
        }
        line_offset += char_width + 1;
        X += char_width + 1;
    }
}

void lcd_print(uint8_t *buf, uint16_t size)
{
    lcd_display_chars(Y, X, buf, size);
    lcd_refresh();
}

void lcd_display_int(uint8_t y_addr, uint8_t x_addr, int32_t n)
{
    if (n < 0)
    {
        n = 0 - n;
        lcd_display_chars(y_addr, x_addr, (uint8_t *)"-", 1);
        x_addr += chars_map['-' - 32][0];
    }

    lcd_display_uint(y_addr, x_addr, n);
}

void lcd_display_uint(uint8_t y_addr, uint8_t x_addr, uint32_t n)
{
    uint8_t buf[255], size;
    
    memset(buf, 0, sizeof(buf));
    uint_to_str(n, buf, &size);
    lcd_display_chars(y_addr, x_addr, buf, size);
}

void lcd_dot(uint8_t x, uint8_t y)
{
    uint8_t row, offset;

    ASSERT(x < SCREEN_MAX_X);
    ASSERT(y < SCREEN_MAX_Y);

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

            if ((x >= 0) && (min_y >= 0) && (x < SCREEN_MAX_X) && (min_y < SCREEN_MAX_Y))
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

            if ((min_x >= 0) && (y >= 0) && (min_x < SCREEN_MAX_X) && (y < SCREEN_MAX_Y))
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
