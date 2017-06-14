#ifndef BME280_H_
#define BME280_H_

#include "hal_bme280.h"


void bme280_init(bme280_mode_t mode, bme280_oversampling_t temp,
                 bme280_oversampling_t press, bme280_oversampling_t hum);
void bme280_reset(void);
uint8_t bme280_get_chipid(void);
void bme280_set_mode(bme280_mode_t mode);
bme280_mode_t bme280_get_mode(void);
void bme280_get_compensation_values(void);
void bme280_set_oversampling(bme280_oversampling_t temp, bme280_oversampling_t press, bme280_oversampling_t hum);
uint8_t bme280_get_ctrl_meas();
uint8_t bme280_get_ctrl_hum();
int32_t bme280_compensate_temp(int32_t temp_raw);
uint32_t bme280_compensate_press(int32_t press_raw);
uint32_t bme280_compensate_hum(int32_t hum_raw);
void bme280_poll(int32_t *press, int32_t *temp, int32_t *hum);

#endif /* BME280_H_ */
