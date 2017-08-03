#ifndef _LCD_H_
#define _LCD_H_

#include "embedded_types.h"


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
void lcd_refresh(void);

#endif /* _LCD_H_ */
