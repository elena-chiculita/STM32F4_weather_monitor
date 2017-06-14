#include "hal_bme280.h"
#include "spi.h"
#include "alloc.h"


static volatile uint8_t hal_bme280_spi_transaction_flag = BME280_SPI_TRANSACTION_DONE;


void hal_bme280_init(void)
{
    spi_device_init(SPI_DEVICE_BME280);
    hal_bme280_reset();
    while (hal_bme280_get_status() != bme280_status_done);
}

void hal_bme280_reset(void)
{
    hal_bme280_write_reg(reset, 0xB6);
}

uint8_t hal_bme280_get_id(void)
{
    uint8_t data_tx[2], data_rx[2];

    hal_bme280_read_reg(id, 2, data_tx, data_rx);

    return data_rx[1];
}

bme280_status_t hal_bme280_get_status(void)
{
    uint8_t data_tx[2], data_rx[2];

    hal_bme280_read_reg(status, 2, data_tx, data_rx);
    if (((data_rx[1] & 0x1) == 0) && ((data_rx[1] & 0x8) == 0))
    {
        return bme280_status_done;
    }

    return bme280_status_in_progress;
}

void hal_bme280_set_ctrl_hum(bme280_oversampling_t hum)
{
    hal_bme280_write_reg(ctrl_hum, hum);
}

uint8_t hal_bme280_get_ctrl_hum(void)
{
    uint8_t data_tx[2], data_rx[2];

    hal_bme280_read_reg(ctrl_hum, 2, data_tx, data_rx);

    return data_rx[1];
}

void hal_bme280_set_ctrl_meas(bme280_oversampling_t temp, bme280_oversampling_t press, bme280_mode_t mode)
{
    hal_bme280_write_reg(ctrl_meas, ((temp << 5) | (press << 2) | mode));
}

uint8_t hal_bme280_get_ctrl_meas(void)
{
    uint8_t data_tx[2], data_rx[2];

    hal_bme280_read_reg(ctrl_meas, 2, data_tx, data_rx);

    return data_rx[1];
}

void hal_bme280_get_calib(uint8_t *data_calib_00_25, uint8_t *data_calib_26_41)
{
    uint8_t data_tx[BME280_MEMORY_SIZE_CALIB_00_25], data_rx[BME280_MEMORY_SIZE_CALIB_00_25];

    ASSERT((data_calib_00_25 != NULL) && (data_calib_26_41 != NULL));
    hal_bme280_read_reg(calib00, BME280_MEMORY_SIZE_CALIB_00_25, data_tx, data_rx);
    memcpy(data_calib_00_25, data_rx + 1, BME280_MEMORY_SIZE_CALIB_00_25);
    hal_bme280_read_reg(calib26, BME280_MEMORY_SIZE_CALIB_26_41, data_tx, data_rx);
    memcpy(data_calib_26_41, data_rx + 1, BME280_MEMORY_SIZE_CALIB_26_41);
}

void hal_bme280_get_press_temp_hum(int32_t *press, int32_t *temp, int16_t *hum)
{
    uint8_t data_tx[9], data_rx[9];

    ASSERT((temp != NULL) && (press != NULL) && (hum != NULL));

    hal_bme280_read_reg(press_msb, 9, data_tx, data_rx);
    *press = ((data_rx[1] << 16) | (data_rx[2] << 8) | data_rx[3]) >> 4;
    *temp = ((data_rx[4] << 16) | (data_rx[5] << 8) | data_rx[6]) >> 4;
    *hum = (data_rx[7] << 8) | data_rx[8];
}

void hal_bme280_write_reg(size_t reg_addr, uint8_t data)
{
    uint8_t data_tx[] = {
        ((BME280_REG_WRITE_BIT << 7) | (reg_addr & BME280_REG_WRITE_MASK)),
        0x0
    };

    ASSERT(hal_bme280_spi_transaction_flag == BME280_SPI_TRANSACTION_DONE);
    hal_bme280_spi_transaction_flag = BME280_SPI_TRANSACTION_IN_PROGRESS;

    data_tx[1] = data;

    spi_txrx(data_tx, NULL, sizeof(data_tx), SPI_DEVICE_BME280, hal_bme280_spi_callback);

    while (hal_bme280_spi_transaction_flag != BME280_SPI_TRANSACTION_DONE);
}

void hal_bme280_read_reg(size_t reg_addr, size_t size, uint8_t *data_tx, uint8_t *data_rx)
{
    ASSERT((data_tx != NULL) && (data_rx != NULL));
    ASSERT(hal_bme280_spi_transaction_flag == BME280_SPI_TRANSACTION_DONE);
    hal_bme280_spi_transaction_flag = BME280_SPI_TRANSACTION_IN_PROGRESS;

    *data_tx = (BME280_REG_READ_BIT << 7) | (reg_addr & BME280_REG_READ_MASK);

    spi_txrx(data_tx, data_rx, size, SPI_DEVICE_BME280, hal_bme280_spi_callback);

    while (hal_bme280_spi_transaction_flag != BME280_SPI_TRANSACTION_DONE);
}

void hal_bme280_spi_callback(uint8_t *data)
{
    UNUSED(data);
    ASSERT(hal_bme280_spi_transaction_flag == BME280_SPI_TRANSACTION_IN_PROGRESS);
    hal_bme280_spi_transaction_flag = BME280_SPI_TRANSACTION_DONE;
}
