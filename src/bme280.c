#include "bme280.h"
#include "int_64.h"
#include "util.h"


static uint8_t bme280_calib_00_25[BME280_MEMORY_SIZE_CALIB_00_25];
static uint8_t bme280_calib_26_41[BME280_MEMORY_SIZE_CALIB_26_41];
static int32_t t_fine;
uint16_t dig_T1, dig_P1;
int16_t dig_T2, dig_T3, dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9, dig_H2, dig_H4, dig_H5;
unsigned char dig_H1, dig_H3, dig_H6;


void bme280_init(bme280_mode_t mode, bme280_oversampling_t temp,
                 bme280_oversampling_t press, bme280_oversampling_t hum)
{
    hal_bme280_init();
    bme280_get_compensation_values();
    bme280_set_oversampling(temp, press, hum);
    bme280_set_mode(mode);
}

void bme280_reset(void)
{
    hal_bme280_reset();
}

uint8_t bme280_get_chipid(void)
{
    return hal_bme280_get_id();
}

void bme280_set_mode(bme280_mode_t mode)
{
    uint8_t data = bme280_get_ctrl_meas();

    return hal_bme280_set_ctrl_meas(((data & 0xE0) >> 5), ((data & 0x1C) >> 2), mode);
}

bme280_mode_t bme280_get_mode(void)
{
    return (hal_bme280_get_ctrl_meas() & 0x3);
}

void bme280_get_compensation_values(void)
{
    hal_bme280_get_calib(bme280_calib_00_25, bme280_calib_26_41);
    dig_T1 = (bme280_calib_00_25[1] << 8) | bme280_calib_00_25[0];
    dig_T2 = (bme280_calib_00_25[3] << 8) | bme280_calib_00_25[2];
    dig_T3 = (bme280_calib_00_25[5] << 8) | bme280_calib_00_25[4];
    dig_P1 = (bme280_calib_00_25[7] << 8) | bme280_calib_00_25[6];
    dig_P2 = (bme280_calib_00_25[9] << 8) | bme280_calib_00_25[8];
    dig_P3 = (bme280_calib_00_25[11] << 8) | bme280_calib_00_25[10];
    dig_P4 = (bme280_calib_00_25[13] << 8) | bme280_calib_00_25[12];
    dig_P5 = (bme280_calib_00_25[15] << 8) | bme280_calib_00_25[14];
    dig_P6 = (bme280_calib_00_25[17] << 8) | bme280_calib_00_25[16];
    dig_P7 = (bme280_calib_00_25[19] << 8) | bme280_calib_00_25[18];
    dig_P8 = (bme280_calib_00_25[21] << 8) | bme280_calib_00_25[20];
    dig_P9 = (bme280_calib_00_25[23] << 8) | bme280_calib_00_25[22];
    dig_H1 = bme280_calib_00_25[25];
    dig_H2 = (bme280_calib_26_41[1] << 8) | bme280_calib_26_41[0];
    dig_H3 = bme280_calib_26_41[2];
    dig_H4 = (bme280_calib_26_41[3] << 4) | (bme280_calib_26_41[4] & 0x0F);
    dig_H5 = (bme280_calib_26_41[6] << 4) | ((bme280_calib_26_41[5] & 0xF0) >> 4);
    dig_H6 = bme280_calib_26_41[7];
}

void bme280_set_oversampling(bme280_oversampling_t temp, bme280_oversampling_t press, bme280_oversampling_t hum)
{
    hal_bme280_set_ctrl_hum(hum);
    hal_bme280_set_ctrl_meas(temp, press, bme280_get_mode());
}

uint8_t bme280_get_ctrl_meas()
{
    return hal_bme280_get_ctrl_meas();
}

uint8_t bme280_get_ctrl_hum()
{
    return hal_bme280_get_ctrl_hum();
}

int32_t bme280_compensate_temp(int32_t temp_raw)
{
    int32_t var1, var2;

    var1 = ((((temp_raw >> 3) - ((int32_t)dig_T1 << 1))) * ((int32_t)dig_T2)) >> 11;
    var2 = (((((temp_raw >> 4) - (int32_t)dig_T1) * ((temp_raw >> 4) - (int32_t)dig_T1)) >> 12) * (int32_t)dig_T3) >> 14;
    t_fine = var1 + var2;

    return ((t_fine * 5 + 128) >> 8);
}

uint32_t bme280_compensate_press(int32_t press_raw)
{
    int_64_t var1, var2, p;

    var1 = convert_int32_to_int64(t_fine - 128000);
    var2 = int_64_mul(var1, int_64_mul(var1, convert_int32_to_int64(dig_P6)));
    var2 = int_64_add(var2, int_64_shift_left(int_64_mul(var1, convert_int32_to_int64(dig_P5)), 17));
    var2 = int_64_add(var2, int_64_shift_left(convert_int32_to_int64(dig_P4), 35));
    var1 = int_64_add(int_64_shift_right(int_64_mul(var1, int_64_mul(var1, convert_int32_to_int64(dig_P3))), 8),
                      int_64_shift_left(int_64_mul(var1, convert_int32_to_int64(dig_P2)), 12));
    var1 = int_64_shift_right(int_64_mul(int_64_add(int_64_shift_left(convert_int32_to_int64(1), 47), var1), convert_int32_to_int64(dig_P1)), 33);
    if ((var1.msb == 0) && (var1.lsb == 0))
    {
        /* avoid division by zero */
        return 0;
    }

    p = convert_int32_to_int64(1048576 - press_raw);
    p = int_64_div(int_64_mul(int_64_sub(int_64_shift_left(p, 31), var2), convert_int32_to_int64(3125)), var1);
    var1 = int_64_shift_right(int_64_mul(convert_int32_to_int64(dig_P9), int_64_mul(int_64_shift_right(p, 13), int_64_shift_right(p, 13))), 25);
    var2 = int_64_shift_right(int_64_mul(convert_int32_to_int64(dig_P8), p), 19);
    p = int_64_add(int_64_shift_right(int_64_add(p, int_64_add(var1, var2)), 8), int_64_shift_left(convert_int32_to_int64(dig_P7), 4));

    return (uint32_t)convert_int64_to_int32(p);
}

uint32_t bme280_compensate_hum(int32_t hum_raw)
{
    int32_t v_x1_u32r;

    v_x1_u32r = (t_fine - 76800);
    v_x1_u32r = (((((hum_raw << 14) - (((int32_t)dig_H4) << 20) -
                 (((int32_t)dig_H5) * v_x1_u32r)) + 16384) >> 15) *
                 (((((((v_x1_u32r * ((int32_t)dig_H6)) >> 10) *
                  (((v_x1_u32r * ((int32_t)dig_H3)) >> 11) + 32768)) >> 10) + 2097152) * ((int32_t)dig_H2) + 8192) >> 14));
    v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) * ((int32_t)dig_H1)) >> 4));
    v_x1_u32r = (v_x1_u32r < 0 ? 0 : v_x1_u32r);
    v_x1_u32r = (v_x1_u32r > 419430400 ? 419430400 : v_x1_u32r);

    return (uint32_t)(v_x1_u32r >> 12);
}

void bme280_poll(int32_t *press, int32_t *temp, int32_t *hum)
{
    int32_t press_raw, temp_raw, hum_raw;

    ASSERT((temp != NULL) && (press != NULL) && (hum != NULL));

    bme280_set_mode(BME280_MODE_FORCED);

    while (hal_bme280_get_status() != bme280_status_done)
    {
        delay(1);
    }

    hal_bme280_get_press_temp_hum(&press_raw, &temp_raw, (int16_t *)&hum_raw);
    *temp = bme280_compensate_temp(temp_raw);
    *press = bme280_compensate_press(press_raw) >> 8;
    *hum = (bme280_compensate_hum(hum_raw) * 100) >> 10;
}
