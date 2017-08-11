#ifndef _HAL_BME280_H_
#define _HAL_BME280_H_

#include "stm32f407.h"


#define BME280_SPI_ID SPI2

/* to be used with hal_bme280_spi_transaction_flag */
#define BME280_SPI_TRANSACTION_IN_PROGRESS 0
#define BME280_SPI_TRANSACTION_DONE 1

#define BME280_REG_WRITE_BIT 0
#define BME280_REG_READ_BIT 1

#define BME280_REG_WRITE_MASK 0x7F
#define BME280_REG_READ_MASK 0x7F

#define hum_lsb 0xFE
#define hum_msb 0xFD
#define temp_xlsb 0xFC
#define temp_lsb 0xFB
#define temp_msb 0xFA
#define press_xlsb 0xF9
#define press_lsb 0xF8
#define press_msb 0xF7
#define config 0xF5
#define ctrl_meas 0xF4
#define status 0xF3
#define ctrl_hum 0xF2
#define calib41 0xF0
#define calib40 0xEF
#define calib39 0xEE
#define calib38 0xED
#define calib37 0xEC
#define calib36 0xEB
#define calib35 0xEA
#define calib34 0xE9
#define calib33 0xE8
#define calib32 0xE7
#define calib31 0xE6
#define calib30 0xE5
#define calib29 0xE4
#define calib28 0xE3
#define calib27 0xE2
#define calib26 0xE1
#define reset 0xE0
#define id 0xD0
#define calib25 0xA1
#define calib24 0xA0
#define calib23 0x9F
#define calib22 0x9E
#define calib21 0x9D
#define calib20 0x9C
#define calib19 0x9B
#define calib18 0x9A
#define calib17 0x99
#define calib16 0x98
#define calib15 0x97
#define calib14 0x96
#define calib13 0x95
#define calib12 0x94
#define calib11 0x93
#define calib10 0x92
#define calib09 0x91
#define calib08 0x90
#define calib07 0x8F
#define calib06 0x8E
#define calib05 0x8D
#define calib04 0x8C
#define calib03 0x8B
#define calib02 0x8A
#define calib01 0x89
#define calib00 0x88

#define BME280_MEMORY_BEGIN calib00
#define BME280_MEMORY_END (hum_lsb + 1)
#define BME280_MEMORY_SIZE_CALIB_00_25 ((calib25 + 1) - calib00)
#define BME280_MEMORY_SIZE_CALIB_26_41 ((calib41 + 1) - calib26)
#define BME280_MEMORY_SIZE (BME280_MEMORY_END - BME280_MEMORY_BEGIN)


typedef enum bme280_mode_tag
{
    BME280_MODE_SLEEP = 0,
    BME280_MODE_FORCED = 1,
    BME280_MODE_NORMAL = 3
} bme280_mode_t;

typedef enum bme280_oversampling_tag
{
    BME280_OSRS_SKIP = 0,
    BME280_OSRS_1 = 1,
    BME280_OSRS_2 = 2,
    BME280_OSRS_4 = 3,
    BME280_OSRS_8 = 4,
    BME280_OSRS_16 = 5
} bme280_oversampling_t;

typedef enum bme280_status_tag
{
    bme280_status_in_progress = 0,
    bme280_status_done = 1
} bme280_status_t;


void hal_bme280_init(void);
void hal_bme280_reset(void);
uint8_t hal_bme280_get_id(void);
bme280_status_t hal_bme280_get_status(void);
void hal_bme280_set_ctrl_hum(bme280_oversampling_t hum);
uint8_t hal_bme280_get_ctrl_hum(void);
void hal_bme280_set_ctrl_meas(bme280_oversampling_t temp, bme280_oversampling_t press, bme280_mode_t mode);
uint8_t hal_bme280_get_ctrl_meas(void);
void hal_bme280_get_calib(uint8_t *data_calib_00_25, uint8_t *data_calib_26_41);
void hal_bme280_get_press_temp_hum(int32_t *press, int32_t *temp, int16_t *hum);
void hal_bme280_write_reg(size_t reg_addr, uint8_t data);
void hal_bme280_read_reg(size_t reg_addr, size_t size, uint8_t *data_tx, uint8_t *data_rx);
void hal_bme280_spi_callback(uint8_t *data);

#endif /* _HAL_BME280_H_ */
