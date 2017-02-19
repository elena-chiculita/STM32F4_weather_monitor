#ifndef HAL_LCD_H_
#define HAL_LCD_H_

#include "stm32f407.h"


#define LCD_CLK_PIN 13
#define LCD_CLK_PORT GPIOB

#define LCD_DIN_PIN 15
#define LCD_DIN_PORT GPIOB

#define LCD_DC_PIN 10
#define LCD_DC_PORT GPIOE

typedef enum lcd_dc_tag
{
    LCD_DC_COMMAND = 0,
    LCD_DC_DATA = 1
} lcd_dc_t;

#define LCD_DC_COMMAND 0
#define LCD_DC_DATA 1

#define LCD_CS_PIN 12
#define LCD_CS_PORT GPIOB

typedef enum lcd_cs_tag
{
    LCD_CS_EN = 0,
    LCD_CS_DIS = 1
} lcd_cs_t;

#define LCD_RST_PIN 12
#define LCD_RST_PORT GPIOE

typedef enum lcd_rst_tag
{
    LCD_RST_EN = 0,
    LCD_RST_DIS = 1
} lcd_rst_t;

#define LCD_LED_PIN 14
#define LCD_LED_PORT GPIOE


/* to be used with LCD_DC_COMMAND */
typedef enum lcd_dc_command_tag
{
    LCD_DC_COMMAND_NOP = 0,
    LCD_DC_COMMAND_FUNCTION_SET = 1,
    LCD_DC_COMMAND_DISPLAY_CONTROL = 2,
    LCD_DC_COMMAND_SET_Y_ADDR = 3,
    LCD_DC_COMMAND_SET_X_ADDR = 4,
    LCD_DC_COMMAND_TEMP_CONTROL = 5,
    LCD_DC_COMMAND_BIAS_SYSTEM = 6,
    LCD_DC_COMMAND_SET_VOP = 7
} lcd_dc_command_t;

/* to be used with LCD_CD_COMMAND_FUNCTION_SET */
typedef enum lcd_function_set_h_tag
{
    LCD_FUNCTION_SET_H_BASIC_INSTR_SET = 0,
    LCD_FUNCTION_SET_H_EXT_INSTR_SET = 1,
    LCD_FUNCTION_SET_H_PRESERVE = 2
} lcd_function_set_h_t;

typedef enum lcd_function_set_v_tag
{
    LCD_FUNCTION_SET_V_HORIZONTAL = 0,
    LCD_FUNCTION_SET_V_VERTICAL = 1,
    LCD_FUNCTION_SET_V_PRESERVE = 2
} lcd_function_set_v_t;

typedef enum lcd_function_set_pd_tag
{
    LCD_FUNCTION_SET_PD_ACTIVE = 0,
    LCD_FUNCTION_SET_PD_POWER_DOWN = 1,
    LCD_FUNCTION_SET_PD_PRESERVE = 2
} lcd_function_set_pd_t;

/* to be used with LCD_CD_COMMAND_DISPLAY_CONTROL */
typedef enum lcd_display_control_de_tag
{
    LCD_COMMAND_DISPLAY_DE_BLANK = 0,
    LCD_COMMAND_DISPLAY_DE_NORMAL = 1,
    LCD_COMMAND_DISPLAY_DE_ALL_ON = 2,
    LCD_COMMAND_DISPLAY_DE_INVERSE = 3
} lcd_display_control_de_t;

/* to be used with LCD_CD_COMMAND_TEMP_CONTROL */
typedef enum lcd_temp_control_tc_tag
{
    LCD_TEMP_CONTROL_TC_0 = 0,
    LCD_TEMP_CONTROL_TC_1 = 1,
    LCD_TEMP_CONTROL_TC_2 = 2,
    LCD_TEMP_CONTROL_TC_3 = 3
} lcd_temp_control_tc_t;


void lcd_screen_erase(void);
void hal_lcd_init(void);
void hal_lcd_reset(void);
void hal_lcd_backlight_on(void);
void hal_lcd_backlight_off(void);
void hal_lcd_pre_serializer(uint8_t buf, lcd_dc_t dc);
void hal_lcd_serializer(uint8_t buf);
void hal_lcd_post_serializer(void);
void hal_lcd_send_data(uint8_t *buf, uint16_t size);
void hal_lcd_send_command_nop(void);
void hal_lcd_send_command_function_set(lcd_function_set_pd_t pd, 
                                       lcd_function_set_v_t v,
                                       lcd_function_set_h_t h);
void hal_lcd_send_command_display_control(lcd_display_control_de_t de);
void hal_lcd_send_command_set_y_addr(uint8_t y_addr);
void hal_lcd_send_command_set_x_addr(uint8_t x_addr);
void hal_lcd_send_command_temp_control(lcd_temp_control_tc_t tc);
void hal_lcd_send_command_bias_system(uint8_t val);
void hal_lcd_send_command_set_vop(uint8_t vop);

#endif /* HAL_LCD_H_ */

