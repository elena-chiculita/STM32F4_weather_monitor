#ifndef _STM32f407_H_
#define _STM32f407_H_

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

#define GET_REG(reg_addr, reg_type, field_offset, field_length) \
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
typedef enum gpio_offset_tag
{
    GPIO_MODER_OFFSET = 0x00,
    GPIO_OTYPER_OFFSET = 0x04,
    GPIO_OSPEEDR_OFFSET = 0x08,
    GPIO_PUPDR_OFFSET = 0x0C,
    GPIO_IDR_OFFSET = 0x10,
    GPIO_ODR_OFFSET = 0x14,
    GPIO_BSRR_OFFSET = 0x18,
    GPIO_LCKR_OFFSET = 0x1C,
    GPIO_AFRL_OFFSET = 0x20,
    GPIO_AFRH_OFFSET = 0x24
} gpio_offset_t;

/* GPIO_MODER */

typedef enum gpio_moder_tag
{
    GPIO_MODER_INPUT = 0x0,
    GPIO_MODER_OUTPUT = 0x1,
    GPIO_MODER_ALTERNATE = 0x2,
    GPIO_MODER_ANALOG = 0x3
} gpio_moder_t;

#define GPIO_MODER_TYPE volatile uint32_t
#define GPIO_MODER_FIELD_LENGTH 2

#define set_gpio_moder(port, pin, value) \
    SET_REG(((port) + GPIO_MODER_OFFSET), GPIO_MODER_TYPE, \
        pin * GPIO_MODER_FIELD_LENGTH, GPIO_MODER_FIELD_LENGTH, value)
#define get_gpio_moder(port, pin) \
    GET_REG(((port) + GPIO_MODER_OFFSET), GPIO_MODER_TYPE, \
        pin * GPIO_MODER_FIELD_LENGTH, GPIO_MODER_FIELD_LENGTH)

/* GPIO_OTYPER */

typedef enum gpio_otyper_tag
{
    GPIO_OTYPER_PUSH_PULL = 0x0,
    GPIO_OTYPER_OPEN_DRAIN = 0x1
} gpio_otyper_t;

#define GPIO_OTYPER_TYPE volatile uint32_t
#define GPIO_OTYPER_FIELD_LENGTH 1

#define set_gpio_otyper(port, pin, value) \
    SET_REG(((port) + GPIO_OTYPER_OFFSET), GPIO_OTYPER_TYPE, pin, GPIO_OTYPER_FIELD_LENGTH, value)
#define get_gpio_otyper(port, pin) \
    GET_REG(((port) + GPIO_OTYPER_OFFSET), GPIO_OTYPER_TYPE, pin, GPIO_OTYPER_FIELD_LENGTH)

/* GPIO_OSPEEDR */

typedef enum gpio_ospeedr_tag
{
    GPIO_OSPEEDR_LOW = 0x0,
    GPIO_OSPEEDR_MEDIUM = 0x1,
    GPIO_OSPEEDR_HIGH = 0x2,
    GPIO_OSPEEDR_VERY_HIGH = 0x3
} gpio_ospeedr_t;

#define GPIO_OSPEEDR_TYPE volatile uint32_t
#define GPIO_OSPEEDR_FIELD_LENGTH 2

#define set_gpio_ospeedr(port, pin, value) \
    SET_REG(((port) + GPIO_OSPEEDR_OFFSET), GPIO_OSPEEDR_TYPE, \
        pin * GPIO_OSPEEDR_FIELD_LENGTH, GPIO_OSPEEDR_FIELD_LENGTH, value)
#define get_gpio_ospeedr(pin) \
    GET_REG(((port) + GPIO_OSPEEDR_OFFSET), GPIO_OSPEEDR_TYPE, \
        pin * GPIO_OSPEEDR_FIELD_LENGTH, GPIO_OSPEEDR_FIELD_LENGTH)

/* GPIO_PUPDR */

typedef enum gpio_pupdr_tag
{
    GPIO_PUPDR_NO_PULL = 0x0,
    GPIO_PUPDR_PULL_UP = 0x1,
    GPIO_PUPDR_PULL_DOWN = 0x2,
    GPIO_PUPDR_RESERVED = 0x3
} gpio_pupdr_t;

#define GPIO_PUPDR_TYPE volatile uint32_t
#define GPIO_PUPDR_FIELD_LENGTH 2

#define set_gpio_pupdr(port, pin, value) \
    SET_REG(((port) + GPIO_PUPDR_OFFSET), GPIO_PUPDR_TYPE, \
        pin * GPIO_PUPDR_FIELD_LENGTH, GPIO_PUPDR_FIELD_LENGTH, value)
#define get_gpio_pupdr(port, pin) \
    GET_REG(((port) + GPIO_PUPDR_OFFSET), GPIO_PUPDR_TYPE, \
        pin * GPIO_PUPDR_FIELD_LENGTH, GPIO_PUPDR_FIELD_LENGTH)

/* GPIO_IDR */

#define GPIO_IDR_TYPE volatile uint32_t
#define GPIO_IDR_FIELD_LENGTH 1

#define get_gpio_idr(port, pin) \
    GET_REG(((port) + GPIO_IDR_OFFSET), GPIO_IDR_TYPE, pin, GPIO_IDR_FIELD_LENGTH)

/* GPIO_ODR */

#define GPIO_ODR_TYPE volatile uint32_t
#define GPIO_ODR_FIELD_LENGTH 1

#define set_gpio_odr(port, pin, value) \
    SET_REG(((port) + GPIO_ODR_OFFSET), GPIO_ODR_TYPE, pin, GPIO_ODR_FIELD_LENGTH, value)
#define get_gpio_odr(port, pin) \
    GET_REG(((port) + GPIO_ODR_OFFSET), GPIO_ODR_TYPE, pin, GPIO_ODR_FIELD_LENGTH)

/* GPIO_BSRR */

typedef enum gpio_bsrr_tag
{
    GPIO_BSRR_RESET = 0x0,
    GPIO_BSRR_SET = 0x1
} gpio_bsrr_t;

#define GPIO_BSRR_TYPE volatile uint32_t
#define GPIO_BSRR_FIELD_LENGTH 1

#define set_gpio_bsrr(port, pin, value) \
    SET_REG( \
        ((port) + GPIO_BSRR_OFFSET), \
        GPIO_BSRR_TYPE, \
        pin + (((value) == GPIO_BSRR_RESET) ? 16 : 0), \
        GPIO_BSRR_FIELD_LENGTH, \
        1)

/* GPIOx_AFRL & GPIOx_AFRH */

#define GPIO_AFR_TYPE volatile uint32_t
#define GPIO_AFR_FIELD_LENGTH 4

#define set_gpio_afrl(port, pin, value) \
    SET_REG(((port) + GPIO_AFRL_OFFSET), GPIO_AFR_TYPE, pin * GPIO_AFR_FIELD_LENGTH, GPIO_AFR_FIELD_LENGTH, value)
#define get_gpio_afrl(port, pin) \
    GET_REG(((port) + GPIO_AFRL_OFFSET), GPIO_AFR_TYPE, pin * GPIO_AFR_FIELD_LENGTH, GPIO_AFR_FIELD_LENGTH)

#define set_gpio_afrh(port, pin, value) \
    SET_REG(((port) + GPIO_AFRH_OFFSET), GPIO_AFR_TYPE, (pin - 8) * GPIO_AFR_FIELD_LENGTH, GPIO_AFR_FIELD_LENGTH, value)
#define get_gpio_afrh(port, pin) \
    GET_REG(((port) + GPIO_AFRH_OFFSET), GPIO_AFR_TYPE, (pin - 8) * GPIO_AFR_FIELD_LENGTH, GPIO_AFR_FIELD_LENGTH)

#define set_gpio_afr(port, pin, value) \
    (pin >= 8) ? (set_gpio_afrh(port, pin, value)) : (set_gpio_afrl(port, pin, value))

/* Alternate functions mapping */
typedef enum gpio_af_tag
{
    GPIO_AF_SYS = 0,
    GPIO_AF_SPI1 = 5,
    GPIO_AF_SPI2 = GPIO_AF_SPI1,
    GPIO_AF_SPI3 = 6
} gpio_af_t;


/* RCC */
#define RCC 0x40023800

#define RCC_CLK_DIS 0x0
#define RCC_CLK_EN 0x1

/* RCC OFFSETs */
typedef enum rcc_offset_tag
{
    RCC_AHB1ENR_OFFSET = 0x30,
    RCC_APB1ENR_OFFSET = 0x40,
    RCC_APB2ENR_OFFSET = 0x44
} rcc_offset_t;

/* RCC_AHB1ENR */

#define RCC_AHB1ENR_TYPE volatile uint32_t
#define RCC_AHB1ENR_FIELD_LENGTH 1

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
    SET_REG((RCC + RCC_AHB1ENR_OFFSET), RCC_AHB1ENR_TYPE, RCC_AHB1ENR_PORT_BIT(port), RCC_AHB1ENR_FIELD_LENGTH, value)
#define get_rcc_ahb1enr(port) \
    GET_REG((RCC + RCC_AHB1ENR_OFFSET), RCC_AHB1ENR_TYPE, RCC_AHB1ENR_PORT_BIT(port), RCC_AHB1ENR_FIELD_LENGTH)

/* RCC_APB1ENR */

#define RCC_APB1ENR_TYPE volatile uint32_t
#define RCC_APB1ENR_FIELD_LENGTH 1

typedef enum rcc_apb1enr_offset_tag
{
    RCC_APB1ENR_SPI3EN_OFFSET = 15,
    RCC_APB1ENR_SPI2EN_OFFSET = 14,
    RCC_APB1ENR_TIM7EN_OFFSET = 5
} rcc_apb1enr_offset_t;

/* 15 */
typedef enum rcc_apb1enr_spi3en_tag
{
    RCC_APB1ENR_SPI3EN_DISABLE = 0,
    RCC_APB1ENR_SPI3EN_ENABLE = 1
} rcc_apb1enr_spi3en_t;

#define set_rcc_apb1enr_spi3en(value) \
    SET_REG((RCC + RCC_APB1ENR_OFFSET), RCC_APB1ENR_TYPE, RCC_APB1ENR_SPI3EN_OFFSET, RCC_APB1ENR_FIELD_LENGTH, value)
#define get_rcc_apb1enr_spi3en() \
    GET_REG((RCC + RCC_APB1ENR_OFFSET), RCC_APB1ENR_TYPE, RCC_APB1ENR_SPI3EN_OFFSET, RCC_APB1ENR_FIELD_LENGTH)

/* 14 */
typedef enum rcc_apb1enr_spi2en_tag
{
    RCC_APB1ENR_SPI2EN_DISABLE = 0,
    RCC_APB1ENR_SPI2EN_ENABLE = 1
} rcc_apb1enr_spi2en_t;

#define set_rcc_apb1enr_spi2en(value) \
    SET_REG((RCC + RCC_APB1ENR_OFFSET), RCC_APB1ENR_TYPE, RCC_APB1ENR_SPI2EN_OFFSET, RCC_APB1ENR_FIELD_LENGTH, value)
#define get_rcc_apb1enr_spi2en() \
    GET_REG((RCC + RCC_APB1ENR_OFFSET), RCC_APB1ENR_TYPE, RCC_APB1ENR_SPI2EN_OFFSET, RCC_APB1ENR_FIELD_LENGTH)

/* 5 */
typedef enum rcc_apb1enr_tim7en_tag
{
    RCC_APB1ENR_TIM7EN_DISABLE = 0,
    RCC_APB1ENR_TIM7EN_ENABLE = 1
} rcc_apb1enr_tim7en_t;

#define set_rcc_apb1enr_tim7en(value) \
    SET_REG((RCC + RCC_APB1ENR_OFFSET), RCC_APB1ENR_TYPE, RCC_APB1ENR_TIM7EN_OFFSET, RCC_APB1ENR_FIELD_LENGTH, value)
#define get_rcc_apb1enr_tim7en() \
    GET_REG((RCC + RCC_APB1ENR_OFFSET), RCC_APB1ENR_TYPE, RCC_APB1ENR_TIM7EN_OFFSET, RCC_APB1ENR_FIELD_LENGTH)

/* RCC_APB2ENR */

#define RCC_APB2ENR_TYPE volatile uint32_t
#define RCC_APB2ENR_FIELD_LENGTH 1

typedef enum rcc_apb2enr_offset_tag
{
    RCC_APB2ENR_SPI6EN_OFFSET = 21,
    RCC_APB2ENR_SPI5EN_OFFSET = 20,
    RCC_APB2ENR_SYSCFGEN_OFFSET = 14,
    RCC_APB2ENR_SPI4EN_OFFSET = 13,
    RCC_APB2ENR_SPI1EN_OFFSET = 12
} rcc_apb2enr_offset_t;

/* 21 */
typedef enum rcc_apb2enr_spi6en_tag
{
    RCC_APB2ENR_SPI6EN_DISABLE = 0,
    RCC_APB2ENR_SPI6EN_ENABLE = 1
} rcc_apb2enr_spi6en_t;

#define set_rcc_apb2enr_spi6en(value) \
    SET_REG((RCC + RCC_APB2ENR_OFFSET), RCC_APB2ENR_TYPE, RCC_APB2ENR_SPI6EN_OFFSET, RCC_APB2ENR_FIELD_LENGTH, value)
#define get_rcc_apb2enr_spi6en() \
    GET_REG((RCC + RCC_APB2ENR_OFFSET), RCC_APB2ENR_TYPE, RCC_APB2ENR_SPI6EN_OFFSET, RCC_APB2ENR_FIELD_LENGTH)

/* 20 */
typedef enum rcc_apb2enr_spi5en_tag
{
    RCC_APB2ENR_SPI5EN_DISABLE = 0,
    RCC_APB2ENR_SPI5EN_ENABLE = 1
} rcc_apb2enr_spi5en_t;

#define set_rcc_apb2enr_spi5en(value) \
    SET_REG((RCC + RCC_APB2ENR_OFFSET), RCC_APB2ENR_TYPE, RCC_APB2ENR_SPI5EN_OFFSET, RCC_APB2ENR_FIELD_LENGTH, value)
#define get_rcc_apb2enr_spi5en() \
    GET_REG((RCC + RCC_APB2ENR_OFFSET), RCC_APB2ENR_TYPE, RCC_APB2ENR_SPI5EN_OFFSET, RCC_APB2ENR_FIELD_LENGTH)

/* 14 */
typedef enum rcc_apb2enr_syscfgen_tag
{
    RCC_APB2ENR_SYSCFGEN_DISABLE = 0,
    RCC_APB2ENR_SYSCFGEN_ENABLE = 1
} rcc_apb2enr_syscfgen_t;

#define set_rcc_apb2enr_syscfgen(value) \
    SET_REG((RCC + RCC_APB2ENR_OFFSET), RCC_APB2ENR_TYPE, RCC_APB2ENR_SYSCFGEN_OFFSET, RCC_APB2ENR_FIELD_LENGTH, value)
#define get_rcc_apb2enr_syscfgen() \
    GET_REG((RCC + RCC_APB2ENR_OFFSET), RCC_APB2ENR_TYPE, RCC_APB2ENR_SYSCFGEN_OFFSET, RCC_APB2ENR_FIELD_LENGTH)

/* 13 */
typedef enum rcc_apb2enr_spi4en_tag
{
    RCC_APB2ENR_SPI4EN_DISABLE = 0,
    RCC_APB2ENR_SPI4EN_ENABLE = 1
} rcc_apb2enr_spi4en_t;

#define set_rcc_apb2enr_spi4en(value) \
    SET_REG((RCC + RCC_APB2ENR_OFFSET), RCC_APB2ENR_TYPE, RCC_APB2ENR_SPI4EN_OFFSET, RCC_APB2ENR_FIELD_LENGTH, value)
#define get_rcc_apb2enr_spi4en() \
    GET_REG((RCC + RCC_APB2ENR_OFFSET), RCC_APB2ENR_TYPE, RCC_APB2ENR_SPI4EN_OFFSET, RCC_APB2ENR_FIELD_LENGTH)

/* 12 */
typedef enum rcc_apb2enr_spi1en_tag
{
    RCC_APB2ENR_SPI1EN_DISABLE = 0,
    RCC_APB2ENR_SPI1EN_ENABLE = 1
} rcc_apb2enr_spi1en_t;

#define set_rcc_apb2enr_spi1en(value) \
    SET_REG((RCC + RCC_APB2ENR_OFFSET), RCC_APB2ENR_TYPE, RCC_APB2ENR_SPI1EN_OFFSET, RCC_APB2ENR_FIELD_LENGTH, value)
#define get_rcc_apb2enr_spi1en() \
    GET_REG((RCC + RCC_APB2ENR_OFFSET), RCC_APB2ENR_TYPE, RCC_APB2ENR_SPI1EN_OFFSET, RCC_APB2ENR_FIELD_LENGTH)


/* SPI */

/* SPIx */
typedef enum spi_id_tag
{
    SPI1 = 0x40013000,
    SPI2 = 0x40003800,
    SPI3 = 0x40003C00,
    SPI4 = 0x40013400,
    SPI5 = 0x40015000,
    SPI6 = 0x40015400
} spi_id_t;

#define spi_clk_enable(spi_id) \
    ((spi_id) == SPI1) ? set_rcc_apb2enr_spi1en(RCC_APB2ENR_SPI1EN_ENABLE) : \
    ((spi_id) == SPI2) ? set_rcc_apb1enr_spi2en(RCC_APB1ENR_SPI2EN_ENABLE) : \
    ((spi_id) == SPI3) ? set_rcc_apb1enr_spi3en(RCC_APB1ENR_SPI3EN_ENABLE) : \
    ((spi_id) == SPI4) ? set_rcc_apb2enr_spi4en(RCC_APB2ENR_SPI4EN_ENABLE) : \
    ((spi_id) == SPI5) ? set_rcc_apb2enr_spi5en(RCC_APB2ENR_SPI5EN_ENABLE) : \
    ((spi_id) == SPI6) ? set_rcc_apb2enr_spi6en(RCC_APB2ENR_SPI6EN_ENABLE) : ASSERT(FALSE)

/* SPI1 */ 
#define SPI1_MOSI_PORT GPIOA
#define SPI1_MOSI_PIN 7
#define SPI1_MISO_PORT GPIOA
#define SPI1_MISO_PIN 6
#define SPI1_CLK_PORT GPIOA
#define SPI1_CLK_PIN 5
#define SPI1_NSS_PORT GPIOA
#define SPI1_NSS_PIN 4

/* SPI2 */
#define SPI2_MOSI_PORT GPIOB
#define SPI2_MOSI_PIN 15
#define SPI2_MISO_PORT GPIOB
#define SPI2_MISO_PIN 14
#define SPI2_CLK_PORT GPIOB
#define SPI2_CLK_PIN 13
#define SPI2_NSS_PORT_LCD GPIOB
#define SPI2_NSS_PIN_LCD 12
#define SPI2_NSS_PORT_BME280 GPIOE
#define SPI2_NSS_PIN_BME280 15

/* SPI3 */
#define SPI3_MOSI_PORT GPIOB
#define SPI3_MOSI_PIN 5
#define SPI3_MISO_PORT GPIOB
#define SPI3_MISO_PIN 4
#define SPI3_CLK_PORT GPIOB
#define SPI3_CLK_PIN 3
#define SPI3_NSS_PORT GPIOA
#define SPI3_NSS_PIN 15

/* SPIx OFFSETs */
typedef enum spi_offset_tag
{
    SPI_CR1_OFFSET = 0x00,
    SPI_CR2_OFFSET = 0x04,
    SPI_SR_OFFSET = 0x08,
    SPI_DR_OFFSET = 0x0C,
    SPI_CRCPR_OFFSET = 0x10,
    SPI_RXCRCR_OFFSET = 0x14,
    SPI_TXCRCR_OFFSET = 0x18,
    SPI_I2SCFGR_OFFSET = 0x1C,
    SPI_I2SPR_OFFSET = 0x20
} spi_offset_t;

/* SPI_CR1 */

typedef enum spi_cr1_offset_tag
{
    SPI_CR1_BIDIMODE_OFFSET = 15,
    SPI_CR1_BIDIOE_OFFSET = 14,
    SPI_CR1_CRCEN_OFFSET = 13,
    SPI_CR1_CRCNEXT_OFFSET = 12,
    SPI_CR1_DFF_OFFSET = 11,
    SPI_CR1_RXONLY_OFFSET = 10,
    SPI_CR1_SSM_OFFSET = 9,
    SPI_CR1_SSI_OFFSET = 8,
    SPI_CR1_LSBFIRST_OFFSET = 7,
    SPI_CR1_SPE_OFFSET = 6,
    SPI_CR1_BR_OFFSET = 3,
    SPI_CR1_MSTR_OFFSET = 2,
    SPI_CR1_CPOL_OFFSET = 1,
    SPI_CR1_CPHA_OFFSET = 0
} spi_cr1_offset_t;

typedef enum spi_cr1_length_tag
{
    SPI_CR1_BIDIMODE_LENGTH = 1,
    SPI_CR1_BIDIOE_LENGTH = 1,
    SPI_CR1_CRCEN_LENGTH = 1,
    SPI_CR1_CRCNEXT_LENGTH = 1,
    SPI_CR1_DFF_LENGTH = 1,
    SPI_CR1_RXONLY_LENGTH = 1,
    SPI_CR1_SSM_LENGTH = 1,
    SPI_CR1_SSI_LENGTH = 1,
    SPI_CR1_LSBFIRST_LENGTH = 1,
    SPI_CR1_SPE_LENGTH = 1,
    SPI_CR1_BR_LENGTH = 3,
    SPI_CR1_MSTR_LENGTH = 1,
    SPI_CR1_CPOL_LENGTH = 1,
    SPI_CR1_CPHA_LENGTH = 1
} spi_cr1_length_t;

#define SPI_CR1_TYPE volatile uint16_t

/* 15 */
typedef enum spi_cr1_bidimode_tag
{
    SPI_CR1_BIDIMODE_UNI = 0,
    SPI_CR1_BIDIMODE_BI = 1
} spi_cr1_bidimode_t;

#define set_spi_cr1_bidimode(spi_id, value) \
    SET_REG(((spi_id) + SPI_CR1_OFFSET), SPI_CR1_TYPE, SPI_CR1_BIDIMODE_OFFSET, SPI_CR1_BIDIMODE_LENGTH, value)
#define get_spi_cr1_bidimode(spi_id) \
    GET_REG(((spi_id) + SPI_CR1_OFFSET), SPI_CR1_TYPE, SPI_CR1_BIDIMODE_OFFSET, SPI_CR1_BIDIMODE_LENGTH)

/* 14 */
typedef enum spi_cr1_bidioe_tag
{
    SPI_CR1_BIDIOE_DISABLE = 0,
    SPI_CR1_BIDIOE_ENABLE = 1
} spi_cr1_bidioe_t;

#define set_spi_cr1_bidioe(spi_id, value) \
    SET_REG(((spi_id) + SPI_CR1_OFFSET), SPI_CR1_TYPE, SPI_CR1_BIDIOE_OFFSET, SPI_CR1_BIDIOE_LENGTH, value)
#define get_spi_cr1_bidioe(spi_id) \
    GET_REG(((spi_id) + SPI_CR1_OFFSET), SPI_CR1_TYPE, SPI_CR1_BIDIOE_OFFSET, SPI_CR1_BIDIOE_LENGTH)

/* 13 */
typedef enum spi_cr1_crcen_tag
{
    SPI_CR1_CRCEN_DISABLE = 0,
    SPI_CR1_CRCEN_ENABLE = 1
} spi_cr1_crcen_t;

#define set_spi_cr1_crcen(spi_id, value) \
    SET_REG(((spi_id) + SPI_CR1_OFFSET), SPI_CR1_TYPE, SPI_CR1_CRCEN_OFFSET, SPI_CR1_CRCEN_LENGTH, value)
#define get_spi_cr1_crcen(spi_id) \
    GET_REG(((spi_id) + SPI_CR1_OFFSET), SPI_CR1_TYPE, SPI_CR1_CRCEN_OFFSET, SPI_CR1_CRCEN_LENGTH)

/* 12 */
typedef enum spi_cr1_crcnext_tag
{
    SPI_CR1_CRCNEXT_DISABLE = 0,
    SPI_CR1_CRCNEXT_ENABLE = 1
} spi_cr1_crcnext_t;

#define set_spi_cr1_crcnext(spi_id, value) \
    SET_REG(((spi_id) + SPI_CR1_OFFSET), SPI_CR1_TYPE, SPI_CR1_CRCNEXT_OFFSET, SPI_CR1_CRCNEXT_LENGTH, value)
#define get_spi_cr1_crcnext(spi_id) \
    GET_REG(((spi_id) + SPI_CR1_OFFSET), SPI_CR1_TYPE, SPI_CR1_CRCNEXT_OFFSET, SPI_CR1_CRCNEXT_LENGTH)

/* 11 */
typedef enum spi_cr1_dff_tag
{
    SPI_CR1_DFF_8_BIT = 0,
    SPI_CR1_DFF_16_BIT = 1
} spi_cr1_dff_t;

#define set_spi_cr1_dff(spi_id, value) \
    SET_REG(((spi_id) + SPI_CR1_OFFSET), SPI_CR1_TYPE, SPI_CR1_CRCNEXT_OFFSET, SPI_CR1_CRCNEXT_LENGTH, value)
#define get_spi_cr1_dff(spi_id) \
    GET_REG(((spi_id) + SPI_CR1_OFFSET), SPI_CR1_TYPE, SPI_CR1_CRCNEXT_OFFSET, SPI_CR1_CRCNEXT_LENGTH)

/* 10 */
typedef enum spi_cr1_rxonly_tag
{
    SPI_CR1_RXONLY_FULL_DUPLEX = 0,
    SPI_CR1_RXONLY_OUTPUT_DISABLED = 1
} spi_cr1_rxonly_t;

#define set_spi_cr1_rxonly(spi_id, value) \
    SET_REG(((spi_id) + SPI_CR1_OFFSET), SPI_CR1_TYPE, SPI_CR1_RXONLY_OFFSET, SPI_CR1_RXONLY_LENGTH, value)
#define get_spi_cr1_rxonly(spi_id) \
    GET_REG(((spi_id) + SPI_CR1_OFFSET), SPI_CR1_TYPE, SPI_CR1_RXONLY_OFFSET, SPI_CR1_RXONLY_LENGTH)

/* 9 */
typedef enum spi_cr1_ssm_tag
{
    SPI_CR1_SSM_DISABLE = 0,
    SPI_CR1_SSM_ENABLE = 1
} spi_cr1_ssm_t;

#define set_spi_cr1_ssm(spi_id, value) \
    SET_REG(((spi_id) + SPI_CR1_OFFSET), SPI_CR1_TYPE, SPI_CR1_SSM_OFFSET, SPI_CR1_SSM_LENGTH, value)
#define get_spi_cr1_ssm(spi_id) \
    GET_REG(((spi_id) + SPI_CR1_OFFSET), SPI_CR1_TYPE, SPI_CR1_SSM_OFFSET, SPI_CR1_SSM_LENGTH)

/* 8 */
typedef enum spi_cr1_ssi_tag
{
    SPI_CR1_SSI_DISABLE = 0,
    SPI_CR1_SSI_ENABLE = 1
} spi_cr1_ssi_t;

#define set_spi_cr1_ssi(spi_id, value) \
    SET_REG(((spi_id) + SPI_CR1_OFFSET), SPI_CR1_TYPE, SPI_CR1_SSI_OFFSET, SPI_CR1_SSI_LENGTH, value)
#define get_spi_cr1_ssi(spi_id) \
    GET_REG(((spi_id) + SPI_CR1_OFFSET), SPI_CR1_TYPE, SPI_CR1_SSI_OFFSET, SPI_CR1_SSI_LENGTH)

/* 7 */
typedef enum spi_cr1_lsbfirst_tag
{
    SPI_CR1_LSBFIRST_MSB = 0,
    SPI_CR1_LSBFIRST_LSB = 1
} spi_cr1_lsbfirst_t;

#define set_spi_cr1_lsbfirst(spi_id, value) \
    SET_REG(((spi_id) + SPI_CR1_OFFSET), SPI_CR1_TYPE, SPI_CR1_LSBFIRST_OFFSET, SPI_CR1_LSBFIRST_LENGTH, value)
#define get_spi_cr1_lsbfirst(spi_id) \
    GET_REG(((spi_id) + SPI_CR1_OFFSET), SPI_CR1_TYPE, SPI_CR1_LSBFIRST_OFFSET, SPI_CR1_LSBFIRST_LENGTH)

/* 6 */
typedef enum spi_cr1_spe_tag
{
    SPI_CR1_SPE_DISABLE = 0,
    SPI_CR1_SPE_ENABLE = 1
} spi_cr1_spe_t;

#define set_spi_cr1_spe(spi_id, value) \
    SET_REG(((spi_id) + SPI_CR1_OFFSET), SPI_CR1_TYPE, SPI_CR1_SPE_OFFSET, SPI_CR1_SPE_LENGTH, value)
#define get_spi_cr1_spe(spi_id) \
    GET_REG(((spi_id) + SPI_CR1_OFFSET), SPI_CR1_TYPE, SPI_CR1_SPE_OFFSET, SPI_CR1_SPE_LENGTH)

/* 5:3 */
typedef enum spi_cr1_br_tag
{
    SPI_CR1_BR_PCLK_BY_2 = 0,
    SPI_CR1_BR_PCLK_BY_4 = 1,
    SPI_CR1_BR_PCLK_BY_8 = 2,
    SPI_CR1_BR_PCLK_BY_16 = 3,
    SPI_CR1_BR_PCLK_BY_32 = 4,
    SPI_CR1_BR_PCLK_BY_64 = 5,
    SPI_CR1_BR_PCLK_BY_128 = 6,
    SPI_CR1_BR_PCLK_BY_256 = 7
} spi_cr1_br_t;

#define set_spi_cr1_br(spi_id, value) \
    SET_REG(((spi_id) + SPI_CR1_OFFSET), SPI_CR1_TYPE, SPI_CR1_BR_OFFSET, SPI_CR1_BR_LENGTH, value)
#define get_spi_cr1_br(spi_id) \
    GET_REG(((spi_id) + SPI_CR1_OFFSET), SPI_CR1_TYPE, SPI_CR1_BR_OFFSET, SPI_CR1_BR_LENGTH)

/* 2 */
typedef enum spi_cr1_mstr_tag
{
    SPI_CR1_MSTR_SLAVE = 0,
    SPI_CR1_MSTR_MASTER = 1
} spi_cr1_mstr_t;

#define set_spi_cr1_mstr(spi_id, value) \
    SET_REG(((spi_id) + SPI_CR1_OFFSET), SPI_CR1_TYPE, SPI_CR1_MSTR_OFFSET, SPI_CR1_MSTR_LENGTH, value)
#define get_spi_cr1_mstr(spi_id) \
    GET_REG(((spi_id) + SPI_CR1_OFFSET), SPI_CR1_TYPE, SPI_CR1_MSTR_OFFSET, SPI_CR1_MSTR_LENGTH)

/* 1 */
typedef enum spi_cr1_cpol_tag
{
    SPI_CR1_CPOL_IDLE_LOW = 0,
    SPI_CR1_CPOL_IDLE_HIGH = 1
} spi_cr1_cpol_t;

#define set_spi_cr1_cpol(spi_id, value) \
    SET_REG(((spi_id) + SPI_CR1_OFFSET), SPI_CR1_TYPE, SPI_CR1_CPOL_OFFSET, SPI_CR1_CPOL_LENGTH, value)
#define get_spi_cr1_cpol(spi_id) \
    GET_REG(((spi_id) + SPI_CR1_OFFSET), SPI_CR1_TYPE, SPI_CR1_CPOL_OFFSET, SPI_CR1_CPOL_LENGTH)

/* 0 */
typedef enum spi_cr1_cpha_tag
{
    SPI_CR1_CPHA_CAPTURE_FIRST_EDGE = 0,
    SPI_CR1_CPHA_CAPTURE_SECOND_EDGE = 1
} spi_cr1_cpha_t;

#define set_spi_cr1_cpha(spi_id, value) \
    SET_REG(((spi_id) + SPI_CR1_OFFSET), SPI_CR1_TYPE, SPI_CR1_CPHA_OFFSET, SPI_CR1_CPHA_LENGTH, value)
#define get_spi_cr1_cpha(spi_id) \
    GET_REG(((spi_id) + SPI_CR1_OFFSET), SPI_CR1_TYPE, SPI_CR1_CPHA_OFFSET, SPI_CR1_CPHA_LENGTH)

/* SPI_CR2 */

typedef enum spi_cr2_offset_tag
{
    SPI_CR2_TXEIE_OFFSET = 7,
    SPI_CR2_RXNEIE_OFFSET = 6,
    SPI_CR2_ERRIE_OFFSET = 5,
    SPI_CR2_FRF_OFFSET = 4,
    SPI_CR2_SSOE_OFFSET = 2,
    SPI_CR2_TXDMAEN_OFFSET = 1,
    SPI_CR2_RXDMAEN_OFFSET = 0,
} spi_cr2_offset_t;

typedef enum spi_cr2_length_tag
{
    SPI_CR2_TXEIE_LENGTH = 1,
    SPI_CR2_RXNEIE_LENGTH = 1,
    SPI_CR2_ERRIE_LENGTH = 1,
    SPI_CR2_FRF_LENGTH = 1,
    SPI_CR2_SSOE_LENGTH = 1,
    SPI_CR2_TXDMAEN_LENGTH = 1,
    SPI_CR2_RXDMAEN_LENGTH = 1,
} spi_cr2_length_t;

#define SPI_CR2_TYPE volatile uint16_t

/* 7 */
typedef enum spi_cr2_txeie_tag
{
    SPI_CR2_TXEIE_MASKED = 0,
    SPI_CR2_TXEIE_NOT_MASKED = 1
} spi_cr2_txeie_t;

#define set_spi_cr2_txeie(spi_id, value) \
    SET_REG(((spi_id) + SPI_CR2_OFFSET), SPI_CR2_TYPE, SPI_CR2_TXEIE_OFFSET, SPI_CR2_TXEIE_LENGTH, value)
#define get_spi_cr2_txeie(spi_id) \
    GET_REG(((spi_id) + SPI_CR2_OFFSET), SPI_CR2_TYPE, SPI_CR2_TXEIE_OFFSET, SPI_CR2_TXEIE_LENGTH)

/* 6 */
typedef enum spi_cr2_rxneie_tag
{
    SPI_CR2_RXNEIE_MASKED = 0,
    SPI_CR2_RXNEIE_NOT_MASKED = 1
} spi_cr2_rxneie_t;

#define set_spi_cr2_rxneie(spi_id, value) \
    SET_REG(((spi_id) + SPI_CR2_OFFSET), SPI_CR2_TYPE, SPI_CR2_RXNEIE_OFFSET, SPI_CR2_RXNEIE_LENGTH, value)
#define get_spi_cr2_rxneie(spi_id) \
    GET_REG(((spi_id) + SPI_CR2_OFFSET), SPI_CR2_TYPE, SPI_CR2_RXNEIE_OFFSET, SPI_CR2_RXNEIE_LENGTH)

/* 5 */
typedef enum spi_cr2_errie_tag
{
    SPI_CR2_ERRIE_MASKED = 0,
    SPI_CR2_ERRIE_NOT_MASKED = 1
} spi_cr2_errie_t;

#define set_spi_cr2_errie(spi_id, value) \
    SET_REG(((spi_id) + SPI_CR2_OFFSET), SPI_CR2_TYPE, SPI_CR2_ERRIE_OFFSET, SPI_CR2_ERRIE_LENGTH, value)
#define get_spi_cr2_errie(spi_id) \
    GET_REG(((spi_id) + SPI_CR2_OFFSET), SPI_CR2_TYPE, SPI_CR2_ERRIE_OFFSET, SPI_CR2_ERRIE_LENGTH)

/* 4 */
typedef enum spi_cr2_frf_tag
{
    SPI_CR2_FRF_MOTOROLA = 0,
    SPI_CR2_FRF_TI = 1
} spi_cr2_frf_t;

#define set_spi_cr2_frf(spi_id, value) \
    SET_REG(((spi_id) + SPI_CR2_OFFSET), SPI_CR2_TYPE, SPI_CR2_FRF_OFFSET, SPI_CR2_FRF_LENGTH, value)
#define get_spi_cr2_frf(spi_id) \
    GET_REG(((spi_id) + SPI_CR2_OFFSET), SPI_CR2_TYPE, SPI_CR2_FRF_OFFSET, SPI_CR2_FRF_LENGTH)

/* 2 */
typedef enum spi_cr2_ssoe_tag
{
    SPI_CR2_SSOE_DISABLE = 0,
    SPI_CR2_SSOE_ENABLE = 1
} spi_cr2_ssoe_t;

#define set_spi_cr2_ssoe(spi_id, value) \
    SET_REG(((spi_id) + SPI_CR2_OFFSET), SPI_CR2_TYPE, SPI_CR2_SSOE_OFFSET, SPI_CR2_SSOE_LENGTH, value)
#define get_spi_cr2_ssoe(spi_id) \
    GET_REG(((spi_id) + SPI_CR2_OFFSET), SPI_CR2_TYPE, SPI_CR2_SSOE_OFFSET, SPI_CR2_SSOE_LENGTH)

/* 1 */
typedef enum spi_cr2_txdmaen_tag
{
    SPI_CR2_TXDMAEN_DISABLE = 0,
    SPI_CR2_TXDMAEN_ENABLE = 1
} spi_cr2_txdmaen_t;

#define set_spi_cr2_txdmaen(spi_id, value) \
    SET_REG(((spi_id) + SPI_CR2_OFFSET), SPI_CR2_TYPE, SPI_CR2_TXDMAEN_OFFSET, SPI_CR2_TXDMAEN_LENGTH, value)
#define get_spi_cr2_txdmaen(spi_id) \
    GET_REG(((spi_id) + SPI_CR2_OFFSET), SPI_CR2_TYPE, SPI_CR2_TXDMAEN_OFFSET, SPI_CR2_TXDMAEN_LENGTH)

/* 0 */
typedef enum spi_cr2_rxdmaen_tag
{
    SPI_CR2_RXDMAEN_DISABLE = 0,
    SPI_CR2_RXDMAEN_ENABLE = 1
} spi_cr2_rxdmaen_t;

#define set_spi_cr2_rxdmaen(spi_id, value) \
    SET_REG(((spi_id) + SPI_CR2_OFFSET), SPI_CR2_TYPE, SPI_CR2_RXDMAEN_OFFSET, SPI_CR2_RXDMAEN_LENGTH, value)
#define get_spi_cr2_rxdmaen(spi_id) \
    GET_REG(((spi_id) + SPI_CR2_OFFSET), SPI_CR2_TYPE, SPI_CR2_RXDMAEN_OFFSET, SPI_CR2_RXDMAEN_LENGTH)

/* SPI_SR */

typedef enum spi_sr_offset_tag
{
    SPI_SR_FRE_OFFSET = 8,
    SPI_SR_BSY_OFFSET = 7,
    SPI_SR_OVR_OFFSET = 6,
    SPI_SR_MODF_OFFSET = 5,
    SPI_SR_CRCERR_OFFSET = 4,
    SPI_SR_UDR_OFFSET = 3,
    SPI_SR_CHSIDE_OFFSET = 2,
    SPI_SR_TXE_OFFSET = 1,
    SPI_SR_RXNE_OFFSET = 0
} spi_sr_offset_t;

typedef enum spi_sr_length_tag
{
    SPI_SR_FRE_LENGTH = 1,
    SPI_SR_BSY_LENGTH = 1,
    SPI_SR_OVR_LENGTH = 1,
    SPI_SR_MODF_LENGTH = 1,
    SPI_SR_CRCERR_LENGTH = 1,
    SPI_SR_UDR_LENGTH = 1,
    SPI_SR_CHSIDE_LENGTH = 1,
    SPI_SR_TXE_LENGTH = 1,
    SPI_SR_RXNE_LENGTH = 1
} spi_sr_length_t;

#define SPI_SR_TYPE volatile uint16_t

/* 8 */
typedef enum spi_sr_fre_tag
{
    SPI_SR_FRE_OK = 0,
    SPI_SR_FRE_ERROR = 1
} spi_sr_fre_t;

#define get_spi_sr_fre(spi_id) \
    GET_REG(((spi_id) + SPI_SR_OFFSET), SPI_SR_TYPE, SPI_SR_FRE_OFFSET, SPI_SR_FRE_LENGTH)

/* 7 */
typedef enum spi_sr_bsy_tag
{
    SPI_SR_BSY_IDLE = 0,
    SPI_SR_BSY_BUSY = 1
} spi_sr_bsy_t;

#define get_spi_sr_bsy(spi_id) \
    GET_REG(((spi_id) + SPI_SR_OFFSET), SPI_SR_TYPE, SPI_SR_BSY_OFFSET, SPI_SR_BSY_LENGTH)

/* 6 */
typedef enum spi_sr_ovr_tag
{
    SPI_SR_OVR_OK = 0,
    SPI_SR_OVR_ERROR = 1
} spi_sr_ovr_t;

#define get_spi_sr_ovr(spi_id) \
    GET_REG(((spi_id) + SPI_SR_OFFSET), SPI_SR_TYPE, SPI_SR_OVR_OFFSET, SPI_SR_OVR_LENGTH)

/* 5 */
typedef enum spi_sr_modf_tag
{
    SPI_SR_MODF_OK = 0,
    SPI_SR_MODF_ERROR = 1
} spi_sr_modf_t;

#define get_spi_sr_modf(spi_id) \
    GET_REG(((spi_id) + SPI_SR_OFFSET), SPI_SR_TYPE, SPI_SR_MODF_OFFSET, SPI_SR_MODF_LENGTH)

/* 4 */
typedef enum spi_sr_crcerr_tag
{
    SPI_SR_CRCERR_OK = 0,
    SPI_SR_CRCERR_ERROR = 1
} spi_sr_crcerr_t;

#define set_spi_sr_crcerr(spi_id, value) \
    SET_REG(((spi_id) + SPI_SR_OFFSET), SPI_SR_TYPE, SPI_SR_CRCERR_OFFSET, SPI_SR_CRCERR_LENGTH, value)
#define get_spi_sr_crcerr(spi_id) \
    GET_REG(((spi_id) + SPI_SR_OFFSET), SPI_SR_TYPE, SPI_SR_CRCERR_OFFSET, SPI_SR_CRCERR_LENGTH)

/* 3 */
typedef enum spi_sr_udr_tag
{
    SPI_SR_UDR_OK = 0,
    SPI_SR_UDR_ERROR = 1
} spi_sr_udr_t;

#define get_spi_sr_udr(spi_id) \
    GET_REG(((spi_id) + SPI_SR_OFFSET), SPI_SR_TYPE, SPI_SR_UDR_OFFSET, SPI_SR_UDR_LENGTH)

/* 2 */
typedef enum spi_sr_chside_tag
{
    SPI_SR_CHSIDE_LEFT = 0,
    SPI_SR_CHSIDE_RIGHT = 1
} spi_sr_chside_t;

#define get_spi_sr_chside(spi_id) \
    GET_REG(((spi_id) + SPI_SR_OFFSET), SPI_SR_TYPE, SPI_SR_CHSIDE_OFFSET, SPI_SR_CHSIDE_LENGTH)

/* 1 */
typedef enum spi_sr_txe_tag
{
    SPI_SR_TXE_NOT_EMPTY = 0,
    SPI_SR_TXE_EMPTY = 1
} spi_sr_txe_t;

#define get_spi_sr_txe(spi_id) \
    GET_REG(((spi_id) + SPI_SR_OFFSET), SPI_SR_TYPE, SPI_SR_TXE_OFFSET, SPI_SR_TXE_LENGTH)

/* 0 */
typedef enum spi_sr_rxne_tag
{
    SPI_SR_RXNE_EMPTY = 0,
    SPI_SR_RXNE_NOT_EMPTY = 1
} spi_sr_rxne_t;

#define get_spi_sr_rxne(spi_id) \
    GET_REG(((spi_id) + SPI_SR_OFFSET), SPI_SR_TYPE, SPI_SR_RXNE_OFFSET, SPI_SR_RXNE_LENGTH)

/* SPI_DR */

#define SPI_DR_FIELD_OFFSET 0
#define SPI_DR_FIELD_LENGTH 16

#define set_spi_dr(spi_id, value) \
    SET_REG(((spi_id) + SPI_DR_OFFSET), SPI_SR_TYPE, SPI_DR_FIELD_OFFSET, SPI_DR_FIELD_LENGTH, value)
#define get_spi_dr(spi_id) \
    GET_REG(((spi_id) + SPI_DR_OFFSET), SPI_SR_TYPE, SPI_DR_FIELD_OFFSET, SPI_DR_FIELD_LENGTH)


/* NVIC */

#define NVIC 0xE000E100

typedef enum irq_id_tag
{
    IRQ_ID_WWDG = 0,
    IRQ_ID_PVD = 1,
    IRQ_ID_TAMP_STAMP = 2,
    IRQ_ID_RTC_WKUP = 3,
    IRQ_ID_FLASH = 4,
    IRQ_ID_RCC = 5,
    IRQ_ID_EXTI0 = 6,
    IRQ_ID_EXTI1 = 7,
    IRQ_ID_EXTI2 = 8,
    IRQ_ID_EXTI3 = 9,
    IRQ_ID_EXTI4 = 10,
    IRQ_ID_DMA1_Stream0 = 11,
    IRQ_ID_DMA1_Stream1 = 12,
    IRQ_ID_DMA1_Stream2 = 13,
    IRQ_ID_DMA1_Stream3 = 14,
    IRQ_ID_DMA1_Stream4 = 15,
    IRQ_ID_DMA1_Stream5 = 16,
    IRQ_ID_DMA1_Stream6 = 17,
    IRQ_ID_ADC = 18,
    IRQ_ID_CAN1_TX = 19,
    IRQ_ID_CAN1_RX0 = 20,
    IRQ_ID_CAN1_RX1 = 21,
    IRQ_ID_CAN1_SCE = 22,
    IRQ_ID_EXTI9_5 = 23,
    IRQ_ID_TIM1_BRK_TIM9 = 24,
    IRQ_ID_TIM1_UP_TIM10 = 25,
    IRQ_ID_TIM1_TRG_COM_TIM11 =26,
    IRQ_ID_TIM1_CC = 27,
    IRQ_ID_TIM2 = 28,
    IRQ_ID_TIM3 = 29,
    IRQ_ID_TIM4 = 30,
    IRQ_ID_I2C1_EV = 31,
    IRQ_ID_I2C1_ER = 32,
    IRQ_ID_I2C2_EV = 33,
    IRQ_ID_I2C2_ER = 34,
    IRQ_ID_SPI1 = 35,
    IRQ_ID_SPI2 = 36,
    IRQ_ID_USART1 = 37,
    IRQ_ID_USART2 = 38,
    IRQ_ID_USART3 = 39,
    IRQ_ID_EXTI15_10 = 40,
    IRQ_ID_RTC_Alarm = 41,
    IRQ_ID_OTG_FS_WKUP = 42,
    IRQ_ID_TIM8_BRK_TIM12 = 43,
    IRQ_ID_TIM8_UP_TIM13 = 44,
    IRQ_ID_TIM8_TRG_COM_TIM14 =45,
    IRQ_ID_TIM8_CC = 46,
    IRQ_ID_DMA1_Stream7 = 47,
    IRQ_ID_FSMC = 48,
    IRQ_ID_SDIO = 49,
    IRQ_ID_TIM5 = 50,
    IRQ_ID_SPI3 = 51,
    IRQ_ID_UART4 = 52,
    IRQ_ID_UART5 = 53,
    IRQ_ID_TIM6_DAC = 54,
    IRQ_ID_TIM7 = 55,
    IRQ_ID_DMA2_Stream0 = 56,
    IRQ_ID_DMA2_Stream1 = 57,
    IRQ_ID_DMA2_Stream2 = 58,
    IRQ_ID_DMA2_Stream3 = 59,
    IRQ_ID_DMA2_Stream4 = 60,
    IRQ_ID_ETH = 61,
    IRQ_ID_ETH_WKUP = 62,
    IRQ_ID_CAN2_TX = 63,
    IRQ_ID_CAN2_RX0 = 64,
    IRQ_ID_CAN2_RX1 = 65,
    IRQ_ID_CAN2_SCE = 66,
    IRQ_ID_OTG_FS = 67,
    IRQ_ID_DMA2_Stream5 = 68,
    IRQ_ID_DMA2_Stream6 = 69,
    IRQ_ID_DMA2_Stream7 = 70,
    IRQ_ID_USART6 = 71,
    IRQ_ID_I2C3_EV = 72,
    IRQ_ID_I2C3_ER = 73,
    IRQ_ID_OTG_HS_EP1_OUT = 74,
    IRQ_ID_OTG_HS_EP1_IN = 75,
    IRQ_ID_OTG_HS_WKUP = 76,
    IRQ_ID_OTG_HS = 77,
    IRQ_ID_DCMI = 78,
    IRQ_ID_CRYP = 79,
    IRQ_ID_HASH_RNG = 80,
    IRQ_ID_FPU = 81
} irq_id_t;

typedef enum nvic_offset_tag
{
    NVIC_ISER0_OFFSET = 0x000,
    NVIC_ISER1_OFFSET = 0x004,
    NVIC_ISER2_OFFSET = 0x008,
    NVIC_ICER0_OFFSET = 0x080,
    NVIC_ICER1_OFFSET = 0x084,
    NVIC_ICER2_OFFSET = 0x088,
    NVIC_ISPR0_OFFSET = 0x100,
    NVIC_ISPR1_OFFSET = 0x104,
    NVIC_ISPR2_OFFSET = 0x108,
    NVIC_ICPR0_OFFSET = 0x180,
    NVIC_ICPR1_OFFSET = 0x184,
    NVIC_ICPR2_OFFSET = 0x188,
    NVIC_IABR0_OFFSET = 0x200,
    NVIC_IABR1_OFFSET = 0x204,
    NVIC_IABR2_OFFSET = 0x208,
    NVIC_IPR0_OFFSET = 0x300,
    NVIC_IPR1_OFFSET = 0x304,
    NVIC_IPR2_OFFSET = 0x308,
    NVIC_IPR3_OFFSET = 0x30C,
    NVIC_IPR4_OFFSET = 0x310,
    NVIC_IPR5_OFFSET = 0x314,
    NVIC_IPR6_OFFSET = 0x318,
    NVIC_IPR7_OFFSET = 0x31C,
    NVIC_IPR8_OFFSET = 0x320,
    NVIC_IPR9_OFFSET = 0x324,
    NVIC_IPR10_OFFSET = 0x328,
    NVIC_IPR11_OFFSET = 0x32C,
    NVIC_IPR12_OFFSET = 0x330,
    NVIC_IPR13_OFFSET = 0x334,
    NVIC_IPR14_OFFSET = 0x338,
    NVIC_IPR15_OFFSET = 0x33C,
    NVIC_IPR16_OFFSET = 0x340,
    NVIC_IPR17_OFFSET = 0x344,
    NVIC_IPR18_OFFSET = 0x348,
    NVIC_IPR19_OFFSET = 0x34C,
    NVIC_IPR20_OFFSET = 0x350,
    NVIC_STIR_OFFSET = 0xE00,
} nvic_offset_t;

/* NVIC_ISER */

#define NVIC_ISER_FIELD_LENGTH 1
#define NVIC_ISER_TYPE volatile uint32_t

typedef enum nvic_iser_tag
{
    NVIC_ISER_DISABLE = 0,
    NVIC_ISER_ENABLE = 1
} nvic_iser_tag;

#define set_nvic_iser0(irq_id) \
    SET_REG((NVIC + NVIC_ISER0_OFFSET), NVIC_ISER_TYPE, irq_id, NVIC_ISER_FIELD_LENGTH, 1)
#define get_nvic_iser0(irq_id) \
    GET_REG((NVIC + NVIC_ISER0_OFFSET), NVIC_ISER_TYPE, irq_id, NVIC_ISER_FIELD_LENGTH)

#define set_nvic_iser1(irq_id) \
    SET_REG((NVIC + NVIC_ISER1_OFFSET), NVIC_ISER_TYPE, (irq_id - 32), NVIC_ISER_FIELD_LENGTH, 1)
#define get_nvic_iser1(irq_id) \
    GET_REG((NVIC + NVIC_ISER1_OFFSET), NVIC_ISER_TYPE, (irq_id - 32), NVIC_ISER_FIELD_LENGTH)

#define set_nvic_iser2(irq_id) \
    SET_REG((NVIC + NVIC_ISER2_OFFSET), NVIC_ISER_TYPE, (irq_id - 64), NVIC_ISER_FIELD_LENGTH, 1)

#define get_nvic_iser2(irq_id) \
    GET_REG((NVIC + NVIC_ISER2_OFFSET), NVIC_ISER_TYPE, (irq_id - 64), NVIC_ISER_FIELD_LENGTH)

#define set_nvic_iser(irq_id) \
    ((irq_id) < 32) ? (set_nvic_iser0(irq_id)) : \
    ((irq_id) < 64) ? (set_nvic_iser1(irq_id)) : \
    ((irq_id) < 81) ? (set_nvic_iser2(irq_id)) : ASSERT(FALSE)

#define get_nvic_iser(irq_id) \
    ((irq_id) < 32) ? (get_nvic_iser0(irq_id)) : \
    ((irq_id) < 64) ? (get_nvic_iser1(irq_id)) : (get_nvic_iser2(irq_id))

/* NVIC_ICER */

#define NVIC_ICER_FIELD_LENGTH 1
#define NVIC_ICER_TYPE volatile uint32_t

typedef enum nvic_icer_tag
{
    NVIC_ICER_DISABLE = 0,
    NVIC_ICER_ENABLE = 1
} nvic_icer_tag;

#define set_nvic_icer0(irq_id) \
    SET_REG((NVIC + NVIC_ICER0_OFFSET), NVIC_ICER_TYPE, irq_id, NVIC_ICER_FIELD_LENGTH, 1)
#define get_nvic_icer0(irq_id) \
    GET_REG((NVIC + NVIC_ICER0_OFFSET), NVIC_ICER_TYPE, irq_id, NVIC_ICER_FIELD_LENGTH)

#define set_nvic_icer1(irq_id) \
    SET_REG((NVIC + NVIC_ICER1_OFFSET), NVIC_ICER_TYPE, (irq_id - 32), NVIC_ICER_FIELD_LENGTH, 1)
#define get_nvic_icer1(irq_id) \
    GET_REG((NVIC + NVIC_ICER1_OFFSET), NVIC_ICER_TYPE, (irq_id - 32), NVIC_ICER_FIELD_LENGTH)

#define set_nvic_icer2(irq_id) \
    SET_REG((NVIC + NVIC_ICER2_OFFSET), NVIC_ICER_TYPE, (irq_id - 64), NVIC_ICER_FIELD_LENGTH, 1)
#define get_nvic_icer2(irq_id) \
    GET_REG((NVIC + NVIC_ICER2_OFFSET), NVIC_ICER_TYPE, (irq_id - 64), NVIC_ICER_FIELD_LENGTH)

#define set_nvic_icer(irq_id) \
    ((irq_id) < 32) ? (set_nvic_icer0(irq_id)) : \
    ((irq_id) < 64) ? (set_nvic_icer1(irq_id)) : \
    ((irq_id) < 81) ? (set_nvic_icer2(irq_id)) : ASSERT(FALSE)

#define get_nvic_icer(irq_id) \
    ((irq_id) < 32) ? (get_nvic_icer0(irq_id)) : \
    ((irq_id) < 64) ? (get_nvic_icer1(irq_id)) : (get_nvic_icer2(irq_id))

/* NVIC_ISPR */

#define NVIC_ISPR_FIELD_LENGTH 1
#define NVIC_ISPR_TYPE volatile uint32_t

typedef enum nvic_ispr_tag
{
    NVIC_ISPR_NOT_PENDING = 0,
    NVIC_ISPR_PENDING = 1
} nvic_ispr_tag;

#define set_nvic_ispr0(irq_id) \
    SET_REG((NVIC + NVIC_ISPR0_OFFSET), NVIC_ISPR_TYPE, irq_id, NVIC_ISPR_FIELD_LENGTH, 1)
#define get_nvic_ispr0(irq_id) \
    GET_REG((NVIC + NVIC_ISPR0_OFFSET), NVIC_ISPR_TYPE, irq_id, NVIC_ISPR_FIELD_LENGTH)

#define set_nvic_ispr1(irq_id) \
    SET_REG((NVIC + NVIC_ISPR1_OFFSET), NVIC_ISPR_TYPE, (irq_id - 32), NVIC_ISPR_FIELD_LENGTH, 1)
#define get_nvic_ispr1(irq_id) \
    GET_REG((NVIC + NVIC_ISPR1_OFFSET), NVIC_ISPR_TYPE, (irq_id - 32), NVIC_ISPR_FIELD_LENGTH)

#define set_nvic_ispr2(irq_id) \
    SET_REG((NVIC + NVIC_ISPR2_OFFSET), NVIC_ISPR_TYPE, (irq_id - 64), NVIC_ISPR_FIELD_LENGTH, 1)
#define get_nvic_ispr2(irq_id) \
    GET_REG((NVIC + NVIC_ISPR2_OFFSET), NVIC_ISPR_TYPE, (irq_id - 64), NVIC_ISPR_FIELD_LENGTH)

#define set_nvic_ispr(irq_id) \
    ((irq_id) < 32) ? (set_nvic_ispr0(irq_id)) : \
    ((irq_id) < 64) ? (set_nvic_ispr1(irq_id)) : \
    ((irq_id) < 81) ? (set_nvic_ispr2(irq_id)) : ASSERT(FALSE)

#define get_nvic_ispr(irq_id) \
    ((irq_id) < 32) ? (get_nvic_ispr0(irq_id)) : \
    ((irq_id) < 64) ? (get_nvic_ispr1(irq_id)) : (get_nvic_ispr2(irq_id))

/* NVIC_ICPR */

#define NVIC_ICPR_FIELD_LENGTH 1
#define NVIC_ICPR_TYPE volatile uint32_t

typedef enum nvic_icpr_tag
{
    NVIC_ICPR_NOT_PENDING = 0,
    NVIC_ICPR_PENDING = 1
} nvic_icpr_tag;

#define set_nvic_icpr0(irq_id) \
    SET_REG((NVIC + NVIC_ICPR0_OFFSET), NVIC_ICPR_TYPE, irq_id, NVIC_ICPR_FIELD_LENGTH, 1)
#define get_nvic_icpr0(irq_id) \
    GET_REG((NVIC + NVIC_ICPR0_OFFSET), NVIC_ICPR_TYPE, irq_id, NVIC_ICPR_FIELD_LENGTH)

#define set_nvic_icpr1(irq_id) \
    SET_REG((NVIC + NVIC_ICPR1_OFFSET), NVIC_ICPR_TYPE, (irq_id - 32), NVIC_ICPR_FIELD_LENGTH, 1)
#define get_nvic_icpr1(irq_id) \
    GET_REG((NVIC + NVIC_ICPR1_OFFSET), NVIC_ICPR_TYPE, (irq_id - 32), NVIC_ICPR_FIELD_LENGTH)

#define set_nvic_icpr2(irq_id) \
    SET_REG((NVIC + NVIC_ICPR2_OFFSET), NVIC_ICPR_TYPE, (irq_id - 64), NVIC_ICPR_FIELD_LENGTH, 1)
#define get_nvic_icpr2(irq_id) \
    GET_REG((NVIC + NVIC_ICPR2_OFFSET), NVIC_ICPR_TYPE, (irq_id - 64), NVIC_ICPR_FIELD_LENGTH)

#define set_nvic_icpr(irq_id) \
    ((irq_id) < 32) ? (set_nvic_icpr0(irq_id)) : \
    ((irq_id) < 64) ? (set_nvic_icpr1(irq_id)) : \
    ((irq_id) < 81) ? (set_nvic_icpr2(irq_id)) : ASSERT(FALSE)

#define get_nvic_icpr(irq_id) \
    ((irq_id) < 32) ? (get_nvic_icpr0(irq_id)) : \
    ((irq_id) < 64) ? (get_nvic_icpr1(irq_id)) : (get_nvic_icpr2(irq_id))


/* SYSCFG */

#define SYSCFG 0x40013800

typedef enum syscfg_offset_tag
{
    SYSCFG_MEMRMP_OFFSET = 0x00,
    SYSCFG_PMC_OFFSET = 0x04,
    SYSCFG_EXTICR1_OFFSET = 0x08,
    SYSCFG_EXTICR2_OFFSET = 0x0C,
    SYSCFG_EXTICR3_OFFSET = 0x10,
    SYSCFG_EXTICR4_OFFSET = 0x14,
    SYSCFG_CMPCR_OFFSET = 0x20
} syscfg_offset_t;

/* SYSCFG_EXTICR */

#define SYSCFG_EXTICR_FIELD_LENGTH 4
#define SYSCFG_EXTICR_TYPE volatile uint32_t

#define SYSCFG_EXTICR_GPIO_TO_PORT_BIT(port) \
   ((port) == GPIOA) ? 0 : \
   ((port) == GPIOB) ? 1 : \
   ((port) == GPIOC) ? 2 : \
   ((port) == GPIOD) ? 3 : \
   ((port) == GPIOE) ? 4 : \
   ((port) == GPIOF) ? 5 : \
   ((port) == GPIOG) ? 6 : \
   ((port) == GPIOH) ? 7 : 8

#define SYSCFG_EXTICR_PORT_BIT_TO_GPIO(port) \
   ((port) == 0) ? GPIOA : \
   ((port) == 1) ? GPIOB : \
   ((port) == 2) ? GPIOC : \
   ((port) == 3) ? GPIOD : \
   ((port) == 4) ? GPIOE : \
   ((port) == 5) ? GPIOF : \
   ((port) == 6) ? GPIOG : \
   ((port) == 7) ? GPIOH : GPIOI

#define set_syscfg_exticr_id(exticr_id_offset, port, line) \
    SET_REG((SYSCFG + exticr_id_offset), SYSCFG_EXTICR_TYPE, \
            (line * SYSCFG_EXTICR_FIELD_LENGTH), SYSCFG_EXTICR_FIELD_LENGTH, SYSCFG_EXTICR_GPIO_TO_PORT_BIT(port))

#define set_syscfg_exticr(port, line) \
    (line <= 3)                    ? (set_syscfg_exticr_id(SYSCFG_EXTICR1_OFFSET, port, line)) : \
    ((line >= 4) && (line <= 7))   ? (set_syscfg_exticr_id(SYSCFG_EXTICR2_OFFSET, port, (line - 4))) : \
    ((line >= 8) && (line <= 11))  ? (set_syscfg_exticr_id(SYSCFG_EXTICR3_OFFSET, port, (line - 8))) : \
    ((line >= 12) && (line <= 15)) ? (set_syscfg_exticr_id(SYSCFG_EXTICR4_OFFSET, port, (line - 11))) : ASSERT(FALSE)

#define get_syscfg_exticr_id(exticr_id_offset, line) \
    SYSCFG_EXTICR_PORT_BIT_TO_GPIO(GET_REG((SYSCFG + exticr_id_offset), SYSCFG_EXTICR_TYPE, \
                                           (line * SYSCFG_EXTICR_FIELD_LENGTH), \
                                           SYSCFG_EXTICR_FIELD_LENGTH))

#define get_syscfg_exticr(line) \
    (line <= 3)                   ? (get_syscfg_exticr_id(SYSCFG_EXTICR1_OFFSET, line)) : \
    ((line >= 4) && (line <= 7))  ? (get_syscfg_exticr_id(SYSCFG_EXTICR2_OFFSET, (line - 4))) : \
    ((line >= 8) && (line <= 11)) ? (get_syscfg_exticr_id(SYSCFG_EXTICR3_OFFSET, (line - 8))) : \
                                    (get_syscfg_exticr_id(SYSCFG_EXTICR4_OFFSET, (line - 11)))


/* EXTI */

#define EXTI 0x40013C00
#define EXTI_TYPE volatile uint32_t
#define EXTI_FIELD_LENGTH 1

/* EXTIx OFFSETs */
typedef enum exti_offset_tag
{
    EXTI_IMR_OFFSET = 0x00,
    EXTI_EMR_OFFSET = 0x04,
    EXTI_RTSR_OFFSET = 0x08,
    EXTI_FTSR_OFFSET = 0x0C,
    EXTI_SWIER_OFFSET = 0x10,
    EXTI_PR_OFFSET = 0x14
} exti_offset_t;

#define set_exti_reg(reg_offset, line, val) \
    SET_REG((EXTI + reg_offset), EXTI_TYPE, line, EXTI_FIELD_LENGTH, val)

#define get_exti_reg(reg_offset, line) \
    GET_REG((EXTI + reg_offset), EXTI_TYPE, line, EXTI_FIELD_LENGTH)

/* EXTI_IMR */

typedef enum exti_imr_tag
{
    EXTI_IMR_MASKED = 0,
    EXTI_IMR_NOT_MASKED = 1
} exti_imr_t;

#define set_exti_imr(line, val) set_exti_reg(EXTI_IMR_OFFSET, line, val)
#define get_exti_imr(line) get_exti_reg(EXTI_IMR_OFFSET, line)

/* EXTI_EMR */

typedef enum exti_emr_tag
{
    EXTI_EMR_MASKED = 0,
    EXTI_EMR_NOT_MASKED = 1
} exti_emr_t;

#define set_exti_emr(line, val) set_exti_reg(EXTI_EMR_OFFSET, line, val)
#define get_exti_emr(line) get_exti_reg(EXTI_EMR_OFFSET, line)

/* EXTI_RTSR */

typedef enum exti_rtsr_tag
{
    EXTI_RTSR_RISING_TRIGGER_DIS = 0,
    EXTI_RTSR_RISING_TRIGGER_EN = 1
} exti_rtsr_t;

#define set_exti_rtsr(line, val) set_exti_reg(EXTI_RTSR_OFFSET, line, val)
#define get_exti_rtsr(line) get_exti_reg(EXTI_RTSR_OFFSET, line)

/* EXTI_FTSR */

typedef enum exti_ftsr_tag
{
    EXTI_FTSR_FALLING_TRIGGER_DIS = 0,
    EXTI_FTSR_FALLING_TRIGGER_EN = 1
} exti_ftsr_t;

#define set_exti_ftsr(line, val) set_exti_reg(EXTI_FTSR_OFFSET, line, val)
#define get_exti_ftsr(line) get_exti_reg(EXTI_FTSR_OFFSET, line)

/* EXTI_PR */

typedef enum exti_pr_tag
{
    EXTI_PR_NONE = 0,
    EXTI_PR_TRIGGERED = 1
} exti_pr_t;

#define set_exti_pr(line, val) set_exti_reg(EXTI_PR_OFFSET, line, val)
#define get_exti_pr(line) get_exti_reg(EXTI_PR_OFFSET, line)


/* TIM */

typedef enum timer_tag
{
    TIM1 = 0x40010000,
    TIM2 = 0x40000000,
    TIM3 = 0x40000400,
    TIM4 = 0x40000800,
    TIM5 = 0x40000C00,
    TIM6 = 0x40001000,
    TIM7 = 0x40001400,
    TIM8 = 0x40010400,
    TIM9 = 0x40014000,
    TIM10 = 0x40014400,
    TIM11 = 0x40014800,
    TIM12 = 0x40001800,
    TIM13 = 0x40001C00,
    TIM14 = 0x40002000
} timer_t;

/* TIM1 & TIM8 (advanced-control timers) */

/* TIM2 & TIM5 (general-purpose timers) */

/* TIM9 & TIM14 (general-purpose timers) */

/* TIM6 & TIM7 (basic timers) */

/* TIM6 / TIM7_OFFSETs */
typedef enum tim_offset_tag
{
    TIM_CR1_OFFSET = 0x0,
    TIM_CR2_OFFSET = 0x4,
    TIM_DIER_OFFSET = 0xC,
    TIM_SR_OFFSET = 0x10,
    TIM_EGR_OFFSET = 0x14,
    TIM_CNT_OFFSET = 0x24,
    TIM_PSC_OFFSET = 0x28,
    TIM_ARR_OFFSET = 0x2C
} tim_offset_t;

/* TIM_CR1 */

#define TIM_CR1_TYPE volatile uint16_t
#define TIM_CR1_LENGTH 1

typedef enum tim_cr1_offset_tag
{
    TIM_CR1_ARPE_OFFSET = 7,
    TIM_CR1_OPM_OFFSET = 3,
    TIM_CR1_URS_OFFSET = 2,
    TIM_CR1_UDIS_OFFSET = 1,
    TIM_CR1_CEN_OFFSET = 0
} tim_cr1_offset_t;

/* 7 */
typedef enum tim_cr1_arpe_tag
{
    TIM_CR1_ARPE_NOT_BUFFERED = 0,
    TIM_CR1_ARPE_BUFFERED = 1
} tim_cr1_arpe_t;

#define set_tim_cr1_arpe(timer_id, value) \
    SET_REG(((timer_id) + TIM_CR1_OFFSET), TIM_CR1_TYPE, TIM_CR1_ARPE_OFFSET, TIM_CR1_LENGTH, value)
#define get_tim_cr1_arpe(timer_id) \
    GET_REG(((timer_id) + TIM_CR1_OFFSET), TIM_CR1_TYPE, TIM_CR1_ARPE_OFFSET, TIM_CR1_LENGTH)

/* 3 */
typedef enum tim_cr1_opm_tag
{
    TIM_CR1_OPM_NOT_STOPPED = 0,
    TIM_CR1_OPM_STOPPED = 1
} tim_cr1_opm_t;

#define set_tim_cr1_opm(timer_id, value) \
    SET_REG(((timer_id) + TIM_CR1_OFFSET), TIM_CR1_TYPE, TIM_CR1_OPM_OFFSET, TIM_CR1_LENGTH, value)
#define get_tim_cr1_opm(timer_id) \
    GET_REG(((timer_id) + TIM_CR1_OFFSET), TIM_CR1_TYPE, TIM_CR1_OPM_OFFSET, TIM_CR1_LENGTH)

/* 2 */
typedef enum tim_cr1_urs_tag
{
    TIM_CR1_URS_ANY_REQUEST = 0,
    TIM_CR1_URS_COUNTER_REQUEST = 1
} tim_cr1_urs_t;

#define set_tim_cr1_urs(timer_id, value) \
    SET_REG(((timer_id) + TIM_CR1_OFFSET), TIM_CR1_TYPE, TIM_CR1_URS_OFFSET, TIM_CR1_LENGTH, value)
#define get_tim_cr1_urs(timer_id) \
    GET_REG(((timer_id) + TIM_CR1_OFFSET), TIM_CR1_TYPE, TIM_CR1_URS_OFFSET, TIM_CR1_LENGTH)

/* 1 */
typedef enum tim_cr1_udis_tag
{
    TIM_CR1_UDIS_UEV_ENABLE = 0,
    TIM_CR1_UDIS_UEV_DISABLE = 1
} tim_cr1_udis_t;

#define set_tim_cr1_udis(timer_id, value) \
    SET_REG(((timer_id) + TIM_CR1_OFFSET), TIM_CR1_TYPE, TIM_CR1_UDIS_OFFSET, TIM_CR1_LENGTH, value)
#define get_tim_cr1_udis(timer_id) \
    GET_REG(((timer_id) + TIM_CR1_OFFSET), TIM_CR1_TYPE, TIM_CR1_UDIS_OFFSET, TIM_CR1_LENGTH)

/* 0 */
typedef enum tim_cr1_cen_tag
{
    TIM_CR1_CEN_DISABLE = 0,
    TIM_CR1_CEN_ENABLE = 1
} tim_cr1_cen_t;

#define set_tim_cr1_cen(timer_id, value) \
    SET_REG(((timer_id) + TIM_CR1_OFFSET), TIM_CR1_TYPE, TIM_CR1_CEN_OFFSET, TIM_CR1_LENGTH, value)
#define get_tim_cr1_cen(timer_id) \
    GET_REG(((timer_id) + TIM_CR1_OFFSET), TIM_CR1_TYPE, TIM_CR1_CEN_OFFSET, TIM_CR1_LENGTH)

/* TIM_DIER */

#define TIM_DIER_TYPE volatile uint16_t
#define TIM_DIER_LENGTH 1

typedef enum tim_dier_offset_tag
{
    TIM_DIER_UDE_OFFSET = 8,
    TIM_DIER_UIE_OFFSET = 0
} tim_dier_offset_t;

/* 8 */
typedef enum tim_dier_ude_tag
{
    TIM_DIER_UDE_DISABLE = 0,
    TIM_DIER_UDE_ENABLE = 1
} tim_dier_ude_t;

#define set_tim_dier_ude(timer_id, value) \
    SET_REG(((timer_id) + TIM_DIER_OFFSET), TIM_DIER_TYPE, TIM_DIER_UDE_OFFSET, TIM_DIER_LENGTH, value)
#define get_tim_dier_ude(timer_id) \
    GET_REG(((timer_id) + TIM_DIER_OFFSET), TIM_DIER_TYPE, TIM_DIER_UDE_OFFSET, TIM_DIER_LENGTH)

/* 0 */
typedef enum tim_dier_uie_tag
{
    TIM_DIER_UIE_DISABLE = 0,
    TIM_DIER_UIE_ENABLE = 1
} tim_dier_uie_t;

#define set_tim_dier_uie(timer_id, value) \
    SET_REG(((timer_id) + TIM_DIER_OFFSET), TIM_DIER_TYPE, TIM_DIER_UIE_OFFSET, TIM_DIER_LENGTH, value)
#define get_tim_dier_uie(timer_id) \
    GET_REG(((timer_id) + TIM_DIER_OFFSET), TIM_DIER_TYPE, TIM_DIER_UIE_OFFSET, TIM_DIER_LENGTH)

/* TIM_SR */

#define TIM_SR_TYPE volatile uint16_t
#define TIM_SR_LENGTH 1

typedef enum tim_sr_offset_tag
{
    TIM_SR_UIF_OFFSET = 0
} tim_sr_offset_t;

/* 0 */
typedef enum tim_sr_uif_tag
{
    TIM_SR_UIF_NO_UPDATE = 0,
    TIM_SR_UIF_PENDING_UPDATE = 1
} tim_sr_uif_t;

#define set_tim_sr_uif(timer_id, value) \
    SET_REG(((timer_id) + TIM_SR_OFFSET), TIM_SR_TYPE, TIM_SR_UIF_OFFSET, TIM_SR_LENGTH, value)
#define get_tim_sr_uif(timer_id) \
    GET_REG(((timer_id) + TIM_SR_OFFSET), TIM_SR_TYPE, TIM_SR_UIF_OFFSET, TIM_SR_LENGTH)

/* TIM_EGR */

#define TIM_EGR_TYPE volatile uint16_t
#define TIM_EGR_LENGTH 1

typedef enum tim_egr_offset_tag
{
    TIM_EGR_UG_OFFSET = 0
} tim_egr_offset_t;

/* 0 */
typedef enum tim_egr_ug_tag
{
    TIM_EGR_UG_NONE = 0,
    TIM_EGR_UG_UPDATE = 1
} tim_egr_ug_t;

#define set_tim_egr_ug(timer_id, value) \
    SET_REG(((timer_id) + TIM_EGR_OFFSET), TIM_EGR_TYPE, TIM_EGR_UG_OFFSET, TIM_EGR_LENGTH, value)

/* TIM_CNT */

#define TIM_CNT_TYPE volatile uint16_t
#define TIM_CNT_LENGTH 16

#define set_tim_cnt(timer_id, value) \
    SET_REG(((timer_id) + TIM_CNT_OFFSET), TIM_CNT_TYPE, 0, TIM_CNT_LENGTH, value)
#define get_tim_cnt(timer_id) \
    GET_REG(((timer_id) + TIM_CNT_OFFSET), TIM_CNT_TYPE, 0, TIM_CNT_LENGTH)

/* TIM_PSC */

#define TIM_PSC_TYPE volatile uint16_t
#define TIM_PSC_LENGTH 16

#define set_tim_psc(timer_id, value) \
    SET_REG(((timer_id) + TIM_PSC_OFFSET), TIM_PSC_TYPE, 0, TIM_PSC_LENGTH, value)
#define get_tim_psc(timer_id) \
    GET_REG(((timer_id) + TIM_PSC_OFFSET), TIM_PSC_TYPE, 0, TIM_PSC_LENGTH)

/* TIM_ARR */

#define TIM_ARR_TYPE volatile uint16_t
#define TIM_ARR_LENGTH 16

#define set_tim_arr(timer_id, value) \
    SET_REG(((timer_id) + TIM_ARR_OFFSET), TIM_ARR_TYPE, 0, TIM_ARR_LENGTH, value)
#define get_tim_arr(timer_id) \
    GET_REG(((timer_id) + TIM_ARR_OFFSET), TIM_ARR_TYPE, 0, TIM_ARR_LENGTH)


/* CONTROL */

typedef enum control_offset_tag
{
    CONTROL_FPCA = 2,
    CONTROL_SPSEL = 1,
    CONTROL_PRIV = 0
} control_offset_t;

/* 0 - PRIV */
typedef enum control_priv_tag
{
    CONTROL_PRIV_PRIVILEGED = 0,
    CONTROL_PRIV_UNPRIVILEGED = 1
} control_priv_t;

#endif /* _STM32f407_H_ */
