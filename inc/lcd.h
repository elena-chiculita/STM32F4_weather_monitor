#ifndef _LCD_H_
#define _LCD_H_

#include "embedded_types.h"


#define SCREEN_WIDTH 84
#define SCREEN_ROWS 6
#define SCREEN_SIZE (SCREEN_ROWS * SCREEN_WIDTH)

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

#define SCREEN_GRAPHICS_Y_ORIGIN_OFFSET (SCREEN_ROWS_TEXT_LENGTH * 8)
#define SCREEN_MAX_X (SCREEN_WIDTH - 1)
#define SCREEN_MAX_Y ((SCREEN_ROWS_GRAPHICS_LENGTH * 8) - 1)


void lcd_screen_erase(void);
void lcd_init(void);
void lcd_set_contrast(uint8_t vop);
void lcd_backlight_on(void);
void lcd_backlight_off(void);
void lcd_putb(uint8_t *buf, uint32_t size);
void lcd_display_chars(uint8_t *buf, uint32_t *size, uint8_t x, uint8_t y, uint16_t *pixels);
void lcd_scroll_text(void);
void lcd_dot(uint8_t x, uint8_t y);
void lcd_line(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
void lcd_circle(int16_t x0, int16_t y0, uint8_t r);
void lcd_clear_graphics(void);
void lcd_refresh(void);

#endif /* _LCD_H_ */
