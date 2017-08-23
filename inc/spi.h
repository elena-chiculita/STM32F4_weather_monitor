#ifndef _SPI_H_
#define _SPI_H_

#include <stddef.h>
#include "hal_spi.h"


typedef enum spi_device_id_tag
{
    SPI_DEVICE_LCD = 0,
    SPI_DEVICE_BME280 = 1
} spi_device_id_t;

typedef void (*spi_transaction_callback_t)(uint8_t *);


void spi_init(spi_id_t spi_id);
void spi_device_init(spi_device_id_t spi_device_id);
void spi_tx(uint8_t *data, size_t size, spi_device_id_t spi_device_id, spi_transaction_callback_t fn);
void spi_rx(uint8_t *data, size_t size, spi_device_id_t spi_device_id, spi_transaction_callback_t fn);
void spi_txrx(uint8_t *data_tx, uint8_t *data_rx, size_t size,
              spi_device_id_t spi_device_id, spi_transaction_callback_t fn);
void _spi_handler(spi_id_t spi_id);
void _spi1_handler(uint32_t *stack);
void _spi2_handler(uint32_t *stack);
void _spi3_handler(uint32_t *stack);

#endif /* _SPI_H_ */
