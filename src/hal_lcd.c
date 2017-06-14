#include "hal_lcd.h"
#include "spi.h"
#include "gpio.h"
#include "util.h"


lcd_function_set_h_t H = LCD_FUNCTION_SET_H_BASIC_INSTR_SET;
lcd_function_set_v_t V = LCD_FUNCTION_SET_V_HORIZONTAL;
lcd_function_set_pd_t PD = LCD_FUNCTION_SET_PD_POWER_DOWN;

static volatile uint8_t hal_lcd_spi_transaction_flag = LCD_SPI_TRANSACTION_DONE;


void hal_lcd_init(void)
{
#ifdef LCD_BIT_BANGING
    gpio_init(LCD_CLK_PORT, LCD_CLK_PIN, GPIO_MODER_OUTPUT, GPIO_OTYPER_PUSH_PULL,
              GPIO_OSPEEDR_VERY_HIGH, GPIO_PUPDR_NO_PULL);
    gpio_init(LCD_DIN_PORT, LCD_DIN_PIN, GPIO_MODER_OUTPUT, GPIO_OTYPER_PUSH_PULL,
              GPIO_OSPEEDR_VERY_HIGH, GPIO_PUPDR_NO_PULL);
#endif /* LCD_BIT_BANGING */
    gpio_init(LCD_DC_PORT, LCD_DC_PIN, GPIO_MODER_OUTPUT, GPIO_OTYPER_PUSH_PULL,
              GPIO_OSPEEDR_VERY_HIGH, GPIO_PUPDR_NO_PULL);
#ifdef LCD_BIT_BANGING
    gpio_init(LCD_CS_PORT, LCD_CS_PIN, GPIO_MODER_OUTPUT, GPIO_OTYPER_PUSH_PULL,
              GPIO_OSPEEDR_VERY_HIGH, GPIO_PUPDR_NO_PULL);
#endif /* LCD_BIT_BANGING */
    gpio_init(LCD_RST_PORT, LCD_RST_PIN, GPIO_MODER_OUTPUT, GPIO_OTYPER_PUSH_PULL,
              GPIO_OSPEEDR_VERY_HIGH, GPIO_PUPDR_NO_PULL);
    gpio_init(LCD_LED_PORT, LCD_LED_PIN, GPIO_MODER_OUTPUT, GPIO_OTYPER_PUSH_PULL,
              GPIO_OSPEEDR_VERY_HIGH, GPIO_PUPDR_NO_PULL);

    gpio_set_value(LCD_RST_PORT, LCD_RST_PIN, LCD_RST_EN);
#ifdef LCD_BIT_BANGING
    gpio_clear(LCD_CLK_PORT, LCD_CLK_PIN);
    gpio_clear(LCD_DIN_PORT, LCD_DIN_PIN);
#endif /* LCD_BIT_BANGING */
    gpio_set_value(LCD_DC_PORT, LCD_DC_PIN, LCD_DC_DATA);
#ifdef LCD_BIT_BANGING
    gpio_set_value(LCD_CS_PORT, LCD_CS_PIN, LCD_CS_DIS);
#endif /* LCD_BIT_BANGING */
    gpio_clear(LCD_LED_PORT, LCD_LED_PIN);

#ifndef LCD_BIT_BANGING
    spi_device_init(SPI_DEVICE_LCD);
#endif /* LCD_BIT_BANGING */
}

void hal_lcd_reset(void)
{
    gpio_set_value(LCD_RST_PORT, LCD_RST_PIN, LCD_RST_DIS);
    gpio_set_value(LCD_RST_PORT, LCD_RST_PIN, LCD_RST_EN);
    gpio_set_value(LCD_RST_PORT, LCD_RST_PIN, LCD_RST_DIS);
}

void hal_lcd_backlight_on(void)
{
    gpio_set(LCD_LED_PORT, LCD_LED_PIN);
}

void hal_lcd_backlight_off(void)
{
    gpio_clear(LCD_LED_PORT, LCD_LED_PIN);
}

void hal_lcd_send_data(uint8_t *buf, uint16_t size)
{
    ASSERT(buf != NULL);

    hal_lcd_data_serializer(buf, size, LCD_DC_DATA);
}

void hal_lcd_send_command_nop(void)
{
    uint8_t buf = 0x0;

    hal_lcd_data_serializer(&buf, 1, LCD_DC_COMMAND);
}

void hal_lcd_send_command_function_set(lcd_function_set_pd_t pd, 
                                       lcd_function_set_v_t v,
                                       lcd_function_set_h_t h)
{
    uint8_t buf = (1 << 5);

    if (pd != LCD_FUNCTION_SET_PD_PRESERVE)
    {
        PD = pd;
    }
    buf |= (PD << 2);

    if (v != LCD_FUNCTION_SET_V_PRESERVE)
    {
        V = v;
    }
    buf |= (V << 1);

    if (h != LCD_FUNCTION_SET_H_PRESERVE)
    {
        H = h;
    }
    buf |= H;

    hal_lcd_data_serializer(&buf, 1, LCD_DC_COMMAND);
}

void hal_lcd_send_command_display_control(lcd_display_control_de_t de)
{
    uint8_t buf = (1 << 3) | ((de << 1) & 0x4) | (de & 0x1);

    hal_lcd_send_command_function_set(LCD_FUNCTION_SET_PD_PRESERVE,
        LCD_FUNCTION_SET_V_PRESERVE, LCD_FUNCTION_SET_H_BASIC_INSTR_SET);

    hal_lcd_data_serializer(&buf, 1, LCD_DC_COMMAND);
}

void hal_lcd_send_command_set_y_addr(uint8_t y_addr)
{
    uint8_t buf = 1 << 6;

    ASSERT(y_addr <= 5);
    buf |= y_addr;

    hal_lcd_send_command_function_set(LCD_FUNCTION_SET_PD_PRESERVE,
        LCD_FUNCTION_SET_V_PRESERVE, LCD_FUNCTION_SET_H_BASIC_INSTR_SET);

    hal_lcd_data_serializer(&buf, 1, LCD_DC_COMMAND);
}

void hal_lcd_send_command_set_x_addr(uint8_t x_addr)
{
    uint8_t buf = 1 << 7;

    ASSERT(x_addr <= 83);
    buf |= x_addr;

    hal_lcd_send_command_function_set(LCD_FUNCTION_SET_PD_PRESERVE,
        LCD_FUNCTION_SET_V_PRESERVE, LCD_FUNCTION_SET_H_BASIC_INSTR_SET);

    hal_lcd_data_serializer(&buf, 1, LCD_DC_COMMAND);
}

void hal_lcd_send_command_temp_control(lcd_temp_control_tc_t tc)
{
    uint8_t buf = (1 << 2) | tc;

    hal_lcd_send_command_function_set(LCD_FUNCTION_SET_PD_PRESERVE,
        LCD_FUNCTION_SET_V_PRESERVE, LCD_FUNCTION_SET_H_EXT_INSTR_SET);

    hal_lcd_data_serializer(&buf, 1, LCD_DC_COMMAND);
}

void hal_lcd_send_command_bias_system(uint8_t val)
{
    uint8_t buf = (1 << 4);

    ASSERT(val <= 5);
    buf |= val;

    hal_lcd_send_command_function_set(LCD_FUNCTION_SET_PD_PRESERVE,
        LCD_FUNCTION_SET_V_PRESERVE, LCD_FUNCTION_SET_H_EXT_INSTR_SET);

    hal_lcd_data_serializer(&buf, 1, LCD_DC_COMMAND);
}

void hal_lcd_send_command_set_vop(uint8_t vop)
{
    uint8_t buf = (1 << 7);

    ASSERT(vop <= 127);
    buf |= vop;

    hal_lcd_send_command_function_set(LCD_FUNCTION_SET_PD_PRESERVE,
        LCD_FUNCTION_SET_V_PRESERVE, LCD_FUNCTION_SET_H_EXT_INSTR_SET);

    hal_lcd_data_serializer(&buf, 1, LCD_DC_COMMAND);
}

void hal_lcd_data_serializer(uint8_t *buf, uint16_t size, lcd_dc_t dc)
{
    uint16_t n;
    int8_t i;

    ASSERT(buf != NULL);

    gpio_set_value(LCD_DC_PORT, LCD_DC_PIN, dc);

#ifdef LCD_BIT_BANGING
    gpio_clear(LCD_CLK_PORT, LCD_CLK_PIN);
    gpio_set_value(LCD_DIN_PORT, LCD_DIN_PIN, ((*buf >> 7) & 0x1));
    gpio_set_value(LCD_CS_PORT, LCD_CS_PIN, LCD_CS_EN);

    for (n = 0; n < size; n++)
    {
        for (i = 7; i >= 0; i--)
        {
            gpio_clear(LCD_CLK_PORT, LCD_CLK_PIN);
            gpio_set_value(LCD_DIN_PORT, LCD_DIN_PIN, (*(buf + n) >> i) & 0x1);
            gpio_set(LCD_CLK_PORT, LCD_CLK_PIN);
            gpio_set_value(LCD_DIN_PORT, LCD_DIN_PIN, (*(buf + n) >> i) & 0x1);
        }
    }
    gpio_clear(LCD_CLK_PORT, LCD_CLK_PIN);
    gpio_clear(LCD_DIN_PORT, LCD_DIN_PIN);
    gpio_set_value(LCD_CS_PORT, LCD_CS_PIN, LCD_CS_DIS);
#else
    UNUSED(n);
    UNUSED(i);

    while (hal_lcd_spi_transaction_flag != LCD_SPI_TRANSACTION_DONE);
    hal_lcd_spi_transaction_flag = LCD_SPI_TRANSACTION_IN_PROGRESS;

    spi_tx(buf, (size_t)size, SPI_DEVICE_LCD, hal_lcd_spi_callback);
#endif /* LCD_BIT_BANGING */
}

#ifndef LCD_BIT_BANGING
void hal_lcd_spi_callback(uint8_t *data)
{
    UNUSED(data);
    hal_lcd_spi_transaction_flag = LCD_SPI_TRANSACTION_DONE;
}
#endif /* LCD_BIT_BANGING */
