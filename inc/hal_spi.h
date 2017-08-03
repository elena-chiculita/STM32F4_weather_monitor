#ifndef _HAL_SPI_H_
#define _HAL_SPI_H_

#include "stm32f407.h"


void hal_spi_init(spi_id_t spi_id,
                  spi_cr1_br_t br,
                  spi_cr1_cpol_t cpol,
                  spi_cr1_cpha_t cpha,
                  spi_cr1_dff_t dff,
                  spi_cr1_lsbfirst_t lsbfirst,
                  spi_cr1_ssm_t ssm,
                  spi_cr1_ssi_t ssi,
                  spi_cr1_mstr_t mstr,
                  spi_cr2_txeie_t txeie,
                  spi_cr2_rxneie_t rxneie,
                  spi_cr2_errie_t errie,
                  spi_cr1_spe_t spe);
void hal_spi_tx(spi_id_t spi_id, uint8_t data);
uint8_t hal_spi_rx(spi_id_t spi_id);

#endif /* _HAL_SPI_H_ */
