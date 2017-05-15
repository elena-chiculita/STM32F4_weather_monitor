#include "hal_spi.h"


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
                  spi_cr1_spe_t spe)
{
    ASSERT(
        (spi_id == SPI1) ||
        (spi_id == SPI2) ||
        (spi_id == SPI3) ||
        (spi_id == SPI4) ||
        (spi_id == SPI5) ||
        (spi_id == SPI6)
    );

    spi_clk_enable(spi_id);
    set_spi_cr1_br(spi_id, br);
    set_spi_cr1_cpol(spi_id, cpol);
    set_spi_cr1_cpha(spi_id, cpha);
    set_spi_cr1_dff(spi_id, dff);
    set_spi_cr1_lsbfirst(spi_id, lsbfirst);
    set_spi_cr1_ssm(spi_id, ssm);
    set_spi_cr1_ssi(spi_id, ssi);
    set_spi_cr1_mstr(spi_id, mstr);
    set_spi_cr2_txeie(spi_id, txeie);
    set_spi_cr2_rxneie(spi_id, rxneie);
    set_spi_cr2_errie(spi_id, errie);
    set_spi_cr1_spe(spi_id, spe);
}

void hal_spi_tx(spi_id_t spi_id, uint8_t data)
{
    ASSERT(
        (spi_id == SPI1) ||
        (spi_id == SPI2) ||
        (spi_id == SPI3) ||
        (spi_id == SPI4) ||
        (spi_id == SPI5) ||
        (spi_id == SPI6)
    );

    set_spi_dr(spi_id, data);
}

uint8_t hal_spi_rx(spi_id_t spi_id)
{
    ASSERT(
        (spi_id == SPI1) ||
        (spi_id == SPI2) ||
        (spi_id == SPI3) ||
        (spi_id == SPI4) ||
        (spi_id == SPI5) ||
        (spi_id == SPI6)
    );

    return (uint8_t) get_spi_dr(spi_id);
}
