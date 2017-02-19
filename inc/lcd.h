#ifndef LCD_H_
#define LCD_H_

#include "embedded_types.h"


void lcd_screen_erase(void);
void lcd_init(void);
void lcd_set_contrast(uint8_t vop);
void lcd_display_chars(uint8_t y_addr, uint8_t x_addr, uint8_t *buf, uint16_t size);
void lcd_print(uint8_t *buf, uint16_t size);
void lcd_display_uint(uint8_t y_addr, uint8_t x_addr, uint32_t n);
void lcd_display_int(uint8_t y_addr, uint8_t x_addr, int32_t n);
void lcd_dot(uint8_t x, uint8_t y);
void lcd_line(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
void lcd_circle(int16_t x0, int16_t y0, uint8_t r);
void lcd_refresh(void);

#endif /* LCD_H_ */
