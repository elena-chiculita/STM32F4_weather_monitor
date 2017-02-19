#ifndef STM32f407_H_
#define STM32f407_H_

#include "embedded_types.h"


#define FIELD_MASK(len) ((1U << (len)) - 1)

#define CLEAR_FIELD(x, field_length, field_offset) \
    ((x) & ~(FIELD_MASK(field_length) << (field_offset)))

#define SET_FIELD(x, field_length, field_offset, value) \
    ((x) | (((value) & FIELD_MASK(field_length)) << (field_offset)))

#define SET_REG(reg_addr, reg_type, field_offset, field_length, value) \
        *((reg_type *)(reg_addr)) = SET_FIELD( \
                        CLEAR_FIELD(*((reg_type *)(reg_addr)), (field_length), (field_offset)), \
                        (field_length), \
                        (field_offset), \
                        (value))

#define GET_REG(reg_addr, reg_type, field_offset, field_length)	\
    ((*((reg_type *)(reg_addr)) >> (field_offset)) & FIELD_MASK(field_length))


/* GPIO */

/* GPIOx */
typedef enum gpio_port_tag
{
    GPIOA = 0x40020000,
    GPIOB = 0x40020400,
    GPIOC = 0x40020800,
    GPIOD = 0x40020C00,
    GPIOE = 0x40021000,
    GPIOF = 0x40021400,
    GPIOG = 0x40021800,
    GPIOH = 0x40021C00,
    GPIOI = 0x40022000,
    GPIOJ = 0x40022400,
    GPIOK = 0x40022800
} gpio_port_t;

/* GPIOx OFFSETs */
#define GPIO_MODER_OFFSET 0x00
#define GPIO_OTYPER_OFFSET 0x04
#define GPIO_OSPEEDR_OFFSET 0x08
#define GPIO_PUPDR_OFFSET 0x0C
#define GPIO_IDR_OFFSET 0x10
#define GPIO_ODR_OFFSET 0x14
#define GPIO_BSRR_OFFSET 0x18
#define GPIO_LCKR_OFFSET 0x1C
#define GPIO_AFRL_OFFSET 0x20
#define GPIO_AFRH_OFFSET 0x24

/* GPIOx_MODER */
typedef enum gpio_moder_tag
{
    GPIO_MODER_INPUT = 0x0,
    GPIO_MODER_OUTPUT = 0x1,
    GPIO_MODER_ALTERNATE = 0x2,
    GPIO_MODER_ANALOG = 0x3
} gpio_moder_t;

#define set_gpio_moder(port, pin, value) \
    SET_REG(((port) + GPIO_MODER_OFFSET), uint32_t, pin * 2, 2, value)
#define get_gpio_moder(port, pin) \
    GET_REG(((port) + GPIO_MODER_OFFSET), uint32_t, pin * 2, 2)

/* GPIOx_OTYPER */
typedef enum gpio_otyper_tag
{
    GPIO_OTYPER_PUSH_PULL = 0x0,
    GPIO_OTYPER_OPEN_DRAIN = 0x1
} gpio_otyper_t;

#define set_gpio_otyper(port, pin, value) \
    SET_REG(((port) + GPIO_OTYPER_OFFSET), uint32_t, pin, 1, value)
#define get_gpio_otyper(port, pin) \
    GET_REG(((port) + GPIO_OTYPER_OFFSET), uint32_t, pin, 1)

/* GPIOx_OSPEEDR */
typedef enum gpio_ospeedr_tag
{
    GPIO_OSPEEDR_LOW = 0x0,
    GPIO_OSPEEDR_MEDIUM = 0x1,
    GPIO_OSPEEDR_HIGH = 0x2,
    GPIO_OSPEEDR_VERY_HIGH = 0x3
} gpio_ospeedr_t;

#define set_gpio_ospeedr(port, pin, value) \
    SET_REG(((port) + GPIO_OSPEEDR_OFFSET), uint32_t, pin * 2, 2, value)
#define get_gpio_ospeedr(pin) \
    GET_REG(((port) + GPIO_OSPEEDR_OFFSET), uint32_t, pin * 2, 2)

/* GPIOx_PUPDR */
typedef enum gpio_pupdr_tag
{
    GPIO_PUPDR_NO_PULL = 0x0,
    GPIO_PUPDR_PULL_UP = 0x1,
    GPIO_PUPDR_PULL_DOWN = 0x2,
    GPIO_PUPDR_RESERVED = 0x3
} gpio_pupdr_t;

#define set_gpio_pupdr(port, pin, value) \
    SET_REG(((port) + GPIO_PUPDR_OFFSET), uint32_t, pin * 2, 2, value)
#define get_gpio_pupdr(port, pin) \
    GET_REG(((port) + GPIO_PUPDR_OFFSET), uint32_t, pin * 2, 2)

/* GPIOx_IDR */
#define get_gpio_idr(port, pin) GET_REG(((port) + GPIO_IDR_OFFSET), uint32_t, pin, 1)

/* GPIOx_ODR */
#define set_gpio_odr(port, pin, value) \
    SET_REG(((port) + GPIO_ODR_OFFSET), uint32_t, pin, 1, value)
#define get_gpio_odr(port, pin) \
    GET_REG(((port) + GPIO_ODR_OFFSET), uint32_t, pin, 1)

/* GPIOx_BSRR */
typedef enum gpio_bsrr_tag
{
    GPIO_BSRR_RESET = 0x0,
    GPIO_BSRR_SET = 0x1
} gpio_bsrr_t;

#define set_gpio_bsrr(port, pin, value) \
    SET_REG( \
        ((port) + GPIO_BSRR_OFFSET), \
        uint32_t, \
        pin + (((value) == GPIO_BSRR_RESET) ? 16 : 0), \
        1, 1)

/* GPIOx_LCKR */

/* GPIOx_AFRL */

/* GPIOx_AFRH */


/* RCC */
#define RCC 0x40023800

/* RCC OFFSETs */
#define RCC_AHB1ENR_OFFSET 0x30

/* RCC_AHB1ENR */
#define RCC_CLK_DIS 0x0
#define RCC_CLK_EN 0x1

#define RCC_AHB1ENR_PORT_BIT(port) \
    ((port) == GPIOA) ? 0 : \
    ((port) == GPIOB) ? 1 : \
    ((port) == GPIOC) ? 2 : \
    ((port) == GPIOD) ? 3 : \
    ((port) == GPIOE) ? 4 : \
    ((port) == GPIOF) ? 5 : \
    ((port) == GPIOG) ? 6 : \
    ((port) == GPIOH) ? 7 : \
    ((port) == GPIOI) ? 8 : \
    ((port) == GPIOJ) ? 9 : 10

#define set_rcc_ahb1enr(port, value) \
    SET_REG((RCC + RCC_AHB1ENR_OFFSET), uint32_t, RCC_AHB1ENR_PORT_BIT(port), 1, value)
#define get_rcc_ahb1enr(port) \
    GET_REG((RCC + RCC_AHB1ENR_OFFSET), uint32_t, RCC_AHB1ENR_PORT_BIT(port), 1)

#endif /* STM32f407_H_ */

