#include "spi.h"
#include "gpio.h"
#include "util.h"
#include "hal_nvic.h"
#include "hal_lcd.h"
#include "hal_bme280.h"
#include "alloc.h"
#include "list.h"


typedef struct spi_device_tag
{
   spi_device_id_t spi_device_id;
   spi_id_t spi_id;
   gpio_port_t nss_port;
   uint8_t nss_pin;
   bool is_init;
} spi_device_t;

spi_device_t spi_devices[] =
{
    {SPI_DEVICE_LCD, LCD_SPI_ID, SPI2_NSS_PORT_LCD, SPI2_NSS_PIN_LCD, FALSE},
    {SPI_DEVICE_BME280, BME280_SPI_ID, SPI2_NSS_PORT_BME280, SPI2_NSS_PIN_BME280, FALSE}
};

typedef enum spi_store_id_tag
{
    SPI_ID_1 = 0,
    SPI_ID_2 = 1,
    SPI_ID_3 = 2,
    SPI_ID_MAX = 3
} spi_store_id_t;

typedef struct spi_transaction_tag
{
    list_elem_t elem;
    size_t size;
    uint8_t *data_tx;
    uint8_t *data_rx;
    spi_transaction_callback_t fn;
    gpio_port_t nss_port;
    uint8_t nss_pin;
} spi_transaction_t;

typedef struct spi_store_tag
{
    spi_id_t spi_id;
    spi_transaction_t *spi_transaction;
    list_t list;
    bool is_init;
} spi_store_t;

volatile spi_store_t spi_store[SPI_ID_MAX];

static volatile spi_store_t* spi_get_store(spi_id_t spi_id);
static spi_device_t* spi_device_get(spi_device_id_t spi_device_id);


void spi_init(spi_id_t spi_id)
{
    spi_store_id_t spi_store_id;
    gpio_port_t mosi_port, miso_port, clk_port;
    uint8_t mosi_pin, miso_pin, clk_pin;
    gpio_af_t gpio_af;
    irq_id_t irq_id;

    switch (spi_id)
    {
        case SPI1:
            gpio_af = GPIO_AF_SPI1;
            irq_id = IRQ_ID_SPI1;
            spi_store_id = SPI_ID_1;
            mosi_port = SPI1_MOSI_PORT;
            mosi_pin = SPI1_MOSI_PIN;
            miso_port = SPI1_MISO_PORT;
            miso_pin = SPI1_MISO_PIN;
            clk_port = SPI1_CLK_PORT;
            clk_pin = SPI1_CLK_PIN;
            break;
        case SPI2:
            gpio_af = GPIO_AF_SPI2;
            irq_id = IRQ_ID_SPI2;
            spi_store_id = SPI_ID_2;
            mosi_port = SPI2_MOSI_PORT;
            mosi_pin = SPI2_MOSI_PIN;
            miso_port = SPI2_MISO_PORT;
            miso_pin = SPI2_MISO_PIN;
            clk_port = SPI2_CLK_PORT;
            clk_pin = SPI2_CLK_PIN;
            break;
        case SPI3:
            gpio_af = GPIO_AF_SPI3;
            irq_id = IRQ_ID_SPI3;
            spi_store_id = SPI_ID_3;
            mosi_port = SPI3_MOSI_PORT;
            mosi_pin = SPI3_MOSI_PIN;
            miso_port = SPI3_MISO_PORT;
            miso_pin = SPI3_MISO_PIN;
            clk_port = SPI3_CLK_PORT;
            clk_pin = SPI3_CLK_PIN;
            break;
        default:
            ASSERT(FALSE);
            return;
    }

    /* disable interrupts */
    _disable_irq();

    spi_store[spi_store_id].spi_id = spi_id;
    list_init((list_t *)&spi_store[spi_store_id].list);

    gpio_init(mosi_port, mosi_pin, GPIO_MODER_ALTERNATE, GPIO_OTYPER_PUSH_PULL, GPIO_OSPEEDR_VERY_HIGH, GPIO_PUPDR_NO_PULL);
    gpio_init(miso_port, miso_pin, GPIO_MODER_ALTERNATE, GPIO_OTYPER_PUSH_PULL, GPIO_OSPEEDR_VERY_HIGH, GPIO_PUPDR_NO_PULL);
    gpio_init(clk_port, clk_pin, GPIO_MODER_ALTERNATE, GPIO_OTYPER_PUSH_PULL, GPIO_OSPEEDR_VERY_HIGH, GPIO_PUPDR_NO_PULL);
    set_gpio_afr(mosi_port, mosi_pin, gpio_af);
    set_gpio_afr(miso_port, miso_pin, gpio_af);
    set_gpio_afr(clk_port, clk_pin, gpio_af);

    hal_spi_init(spi_id,
                 SPI_CR1_BR_PCLK_BY_4,
                 SPI_CR1_CPOL_IDLE_LOW,
                 SPI_CR1_CPHA_CAPTURE_FIRST_EDGE,
                 SPI_CR1_DFF_8_BIT,
                 SPI_CR1_LSBFIRST_MSB,
                 SPI_CR1_SSM_ENABLE,
                 SPI_CR1_SSI_ENABLE,
                 SPI_CR1_MSTR_MASTER,
                 SPI_CR2_TXEIE_MASKED,
                 SPI_CR2_RXNEIE_NOT_MASKED,
                 SPI_CR2_ERRIE_NOT_MASKED,
                 SPI_CR1_SPE_ENABLE);

    hal_spi_rx(spi_id);
    hal_nvic_enable(irq_id);
    spi_store[spi_store_id].is_init = TRUE;

    /* enable interrupts */
    _enable_irq();
}

void spi_device_init(spi_device_id_t spi_device_id)
{
    spi_device_t *spi_device;

    /* disable interrupts */
    _disable_irq();

    spi_device = spi_device_get(spi_device_id);
    ASSERT(spi_device != NULL);
    ASSERT(
        (spi_device->spi_id == SPI1) ||
        (spi_device->spi_id == SPI2) ||
        (spi_device->spi_id == SPI3) ||
        (spi_device->spi_id == SPI4) ||
        (spi_device->spi_id == SPI5) ||
        (spi_device->spi_id == SPI6)
    );

    if (spi_device->is_init == FALSE)
    {
        gpio_init(spi_device->nss_port,
                  spi_device->nss_pin,
                  GPIO_MODER_OUTPUT,
                  GPIO_OTYPER_PUSH_PULL,
                  GPIO_OSPEEDR_VERY_HIGH,
                  GPIO_PUPDR_NO_PULL);
        gpio_set(spi_device->nss_port, spi_device->nss_pin);
        spi_device->is_init = TRUE;
    }

    /* enable interrupts */
    _enable_irq();
}

void spi_tx(uint8_t *data, size_t size, spi_device_id_t spi_device_id, spi_transaction_callback_t fn)
{
    spi_txrx(data, NULL, size, spi_device_id, fn);
}

void spi_rx(uint8_t *data, size_t size, spi_device_id_t spi_device_id, spi_transaction_callback_t fn)
{
    spi_txrx(NULL, data, size, spi_device_id, fn);
}

void spi_txrx(uint8_t *data_tx, uint8_t *data_rx, size_t size,
              spi_device_id_t spi_device_id, spi_transaction_callback_t fn)
{
    volatile spi_store_t *spi_store;
    spi_device_t *spi_device;
    spi_transaction_t *spi_transaction;

    /* disable interrupts */
    _disable_irq();

    spi_device = spi_device_get(spi_device_id);
    ASSERT(spi_device != NULL);
    ASSERT(
        (spi_device->spi_id == SPI1) ||
        (spi_device->spi_id == SPI2) ||
        (spi_device->spi_id == SPI3) ||
        (spi_device->spi_id == SPI4) ||
        (spi_device->spi_id == SPI5) ||
        (spi_device->spi_id == SPI6)
    );
    ASSERT(spi_device->is_init == TRUE);

    spi_store = spi_get_store(spi_device->spi_id);
    ASSERT(spi_store != NULL);
    ASSERT(spi_store->is_init == TRUE);

    spi_transaction = calloc(1, sizeof(spi_transaction_t));
    ASSERT(spi_transaction != NULL);
    spi_transaction->data_rx = data_rx;
    spi_transaction->data_tx = data_tx;
    spi_transaction->size = size;
    spi_transaction->fn = fn;
    spi_transaction->nss_port = spi_device->nss_port;
    spi_transaction->nss_pin = spi_device->nss_pin;

    list_add_last((list_t *)&spi_store->list, (list_elem_t *)&spi_transaction->elem);

    /* enable interrupts */
    _enable_irq();

    set_spi_cr2_txeie(spi_device->spi_id, SPI_CR2_TXEIE_NOT_MASKED);
}

void _spi_handler(spi_id_t spi_id)
{
    volatile spi_store_t *spi_store;
    list_elem_t *first;
    spi_transaction_callback_t fn;
    uint8_t *data;

    /* disable interrupts */
    _disable_irq();

    spi_store = spi_get_store(spi_id);
    ASSERT(spi_store != NULL);

    if (spi_store->spi_transaction == NULL)
    {
        first = list_remove_first((list_t *)&spi_store->list);
        if (first == NULL)
        {
            set_spi_cr2_txeie(spi_id, SPI_CR2_TXEIE_MASKED);
        }

        spi_store->spi_transaction = (spi_transaction_t *)first;
    }
    else
    {
        gpio_clear(spi_store->spi_transaction->nss_port, spi_store->spi_transaction->nss_pin);

        if (get_spi_cr2_rxneie(spi_id) && get_spi_sr_rxne(spi_id))
        {
            if (spi_store->spi_transaction->data_rx != NULL)
            {
                *spi_store->spi_transaction->data_rx = hal_spi_rx(spi_id);
                spi_store->spi_transaction->data_rx++;
            }
            else
            {
                hal_spi_rx(spi_id);
            }
        }

        if (get_spi_cr2_txeie(spi_id) && get_spi_sr_txe(spi_id))
        {
            if (spi_store->spi_transaction->size == 0)
            {
                gpio_set(spi_store->spi_transaction->nss_port, spi_store->spi_transaction->nss_pin);
                fn = spi_store->spi_transaction->fn;
                data = spi_store->spi_transaction->data_tx;
                free(spi_store->spi_transaction);
                spi_store->spi_transaction = NULL;

                ASSERT(fn != NULL);
                fn(data);

                first = list_remove_first((list_t *)&spi_store->list);
                if (first == NULL)
                {
                    set_spi_cr2_txeie(spi_id, SPI_CR2_TXEIE_MASKED);
                }

                spi_store->spi_transaction = (spi_transaction_t *)first;
            }
            else
            {
                if (spi_store->spi_transaction->data_tx != NULL)
                {
                    hal_spi_tx(spi_id, *(spi_store->spi_transaction->data_tx));
                    spi_store->spi_transaction->data_tx++;
                }
                else
                {
                    hal_spi_tx(spi_id, 0x0);
                }

                spi_store->spi_transaction->size--;
            }
        }
    }

    /* enable interrupts */
    _enable_irq();
}

void _spi1_handler(uint32_t *stack)
{
    UNUSED(stack);
    _spi_handler(SPI1);
}

void _spi2_handler(uint32_t *stack)
{
    UNUSED(stack);
    _spi_handler(SPI2);
}

void _spi3_handler(uint32_t *stack)
{
    UNUSED(stack);
    _spi_handler(SPI3);
}

static volatile spi_store_t* spi_get_store(spi_id_t spi_id)
{
    switch (spi_id)
    {
        case SPI1:
            return &(spi_store[SPI_ID_1]);
        case SPI2:
            return &(spi_store[SPI_ID_2]);
        case SPI3:
            return &(spi_store[SPI_ID_3]);
        default:
            ASSERT(FALSE);
            return NULL;
    }
}

static spi_device_t* spi_device_get(spi_device_id_t spi_device_id)
{
    uint32_t i;

    for (i = 0; i < (sizeof(spi_devices) / sizeof(spi_devices[0])); i++)
    {
        if (spi_devices[i].spi_device_id == spi_device_id)
        {
            return &spi_devices[i];
        }
    }

    return NULL;
}
