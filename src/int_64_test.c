#include "int_64_test.h"
#include "int_64.h"


uint32_t int_64_conversions_test(void)
{
    int32_t msb[] = {0xFF00FF00, 0xFF00FF0}, word_msb, test_val_32;
    uint32_t lsb = 0x12345678, word_lsb;
    int_64_t var1, var2;
    uint8_t i;

    for (i = 0; i < (sizeof(msb) / sizeof(msb[0])); i++)
    {
        var1 = int_64_create(msb[i], lsb);
        int_64_get_words(var1, &word_msb, &word_lsb);
        TEST((word_msb == msb[i]) && (word_lsb == lsb));
        TEST(convert_int64_to_int32(var1) == (int32_t)lsb);
        
        test_val_32 = msb[i];
        var2 = convert_int32_to_int64(test_val_32);
        int_64_get_words(var2, &word_msb, &word_lsb);
        TEST(word_msb == (int32_t)((test_val_32 < 0) ? 0xFFFFFFFF : 0x0));
        TEST((uint32_t)word_lsb == (uint32_t)test_val_32);
        TEST(convert_int64_to_int32(var2) == (int32_t)test_val_32);
    }

    return PASS;
}

uint32_t int_64_math_test(void)
{
    int32_t  msb1[] = {0x80000000, 0x80000000, 0xFFFFFFFF, 0x0       , 0x7FFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x12345678, 0x0       , 0x12345678, 0x65465470};
    uint32_t lsb1[] = {0x0       , 0x0       , 0x0       , 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0       , 0x1       , 0x0       , 0xDEADBEEF, 0xdbac5f62};
    int32_t  msb2[] = {0x7FFFFFFF, 0x80000000, 0x1       , 0x0       , 0x0       , 0x0       , 0x1       , 0x1       , 0x1       , 0xFFFFFFFF, 0xfffffdcb};
    uint32_t lsb2[] = {0x0       , 0x0       , 0x0       , 0x1       , 0x1       , 0x1       , 0xFFFFFFFF, 0x12345678, 0x1       , 0xFFFFFFFF, 0xae808031};
    int8_t    cmp[] = {-1        , 0         , -1        , 1         , 1         , -1        , -1        ,  1        , -1        , 1         , 1         };
    int32_t  msba[] = {0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000001, 0x80000000, 0x00000000, 0x00000000, 0x12345679, 0x1       , 0x12345678, 0x6546523C};
    uint32_t lsba[] = {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF, 0x12345679, 0x1       , 0xDEADBEEE, 0x8A2CDF93};
    int32_t  msbs[] = {0x00000001, 0x00000000, 0xFFFFFFFE, 0x00000000, 0x7FFFFFFF, 0xFFFFFFFF, 0xFFFFFFFD, 0x12345676, 0xFFFFFFFE, 0x12345678, 0x654656A5};
    uint32_t lsbs[] = {0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFE, 0xFFFFFFFE, 0xFFFFFFFE, 0x00000001, 0xedcba989, 0xFFFFFFFF, 0xDEADBEF0, 0x2D2BDF31};
    int32_t  msbm[] = {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x7FFFFFFF, 0xFFFFFFFF, 0x00000001, 0x1DF4D841, 0x00000000, 0xEDCBA987, 0xA6FD132A};
    uint32_t lsbm[] = {0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x12345678, 0x00000000, 0x21524111, 0x88AF41C2};
    int32_t  msbd[] = {0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0x7FFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000, 0xEDCBA987, 0xFFFFFFFF};
    uint32_t lsbd[] = {0xFFFFFFFF, 0x00000001, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x10FEF010, 0x00000000, 0x21524111, 0xFFD20EA9};
    int_64_t op1, op2, res;
    int32_t word_msb;
    uint32_t word_lsb;
    uint8_t i;

    for (i = 0; i < (sizeof(msb1) / sizeof(msb1[0])); i++)
    {
        op1 = int_64_create(msb1[i], lsb1[i]);
        op2 = int_64_create(msb2[i], lsb2[i]);
        TEST(int_64_cmp(op1, op2) == cmp[i]);
        res = int_64_add(op1, op2);
        int_64_get_words(res, &word_msb, &word_lsb);
        TEST((word_msb == msba[i]) && (word_lsb == lsba[i]));
        res = int_64_sub(op1, op2);
        int_64_get_words(res, &word_msb, &word_lsb);
        TEST((word_msb == msbs[i]) && (word_lsb == lsbs[i]));
        res = int_64_mul(op1, op2);
        int_64_get_words(res, &word_msb, &word_lsb);
        TEST((word_msb == msbm[i]) && (word_lsb == lsbm[i]));
        res = int_64_div(op1, op2);
        int_64_get_words(res, &word_msb, &word_lsb);
        TEST((word_msb == msbd[i]) && (word_lsb == lsbd[i]));
    }

    return PASS;
}

uint32_t int_64_bitwise_test(void)
{
    int32_t   msb[] = {0x80000000, 0x0       , 0xFFFFFFFF, 0x0       , 0x7FFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x12345678};
    uint32_t  lsb[] = {0x0       , 0x80000000, 0x0       , 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0       , 0x1       };
    int32_t  msbn[] = {0x7FFFFFFF, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x80000000, 0x00000000, 0x00000000, 0xEDCBA987};
    uint32_t lsbn[] = {0xFFFFFFFF, 0x7FFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFE};
    int32_t  msb_shift_val[] = {0x12345678, 0x92345678};
    uint32_t lsb_shift_val[] = {0xDEADBEEF, 0xDEADBEEF};
    uint8_t lsl_n[] = {0, 20, 31, 32, 40, 63, 64};
    int32_t  msbl_res[] = {0x12345678, 0x678DEADB, 0x6F56DF77, 0xDEADBEEF, 0xADBEEF00, 0x80000000, 0x00000000};
    uint32_t lsbl_res[] = {0xDEADBEEF, 0xEEF00000, 0x80000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000};
    int32_t  msbr_res_pos[] = {0x12345678, 0x00000123, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000};
    uint32_t lsbr_res_pos[] = {0xDEADBEEF, 0x45678DEA, 0x2468ACF1, 0x12345678, 0x00123456, 0x00000000, 0x00000000};
    int32_t  msbr_res_neg[] = {0x92345678, 0xFFFFF923, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
    uint32_t lsbr_res_neg[] = {0xDEADBEEF, 0x45678DEA, 0x2468ACF1, 0x92345678, 0xFF923456, 0xFFFFFFFF, 0xFFFFFFFF};
    int_64_t res;
    int32_t word_msb;
    uint32_t word_lsb;
    uint8_t i;

    for (i = 0; i < (sizeof(msb) / sizeof(msb[0])); i++)
    {
        res = int_64_neg(int_64_create(msb[i], lsb[i]));
        int_64_get_words(res, &word_msb, &word_lsb);
        TEST((word_msb == msbn[i]) && (word_lsb == lsbn[i]));
    }

    for (i = 0; i < (sizeof(lsl_n) / sizeof(lsl_n[0])); i++)
    {
        res = int_64_shift_left(int_64_create(msb_shift_val[0], lsb_shift_val[0]), lsl_n[i]);
        int_64_get_words(res, &word_msb, &word_lsb);
        TEST((word_msb == msbl_res[i]) && (word_lsb == lsbl_res[i]));
        res = int_64_shift_right(int_64_create(msb_shift_val[0], lsb_shift_val[0]), lsl_n[i]);
        int_64_get_words(res, &word_msb, &word_lsb);
        TEST((word_msb == msbr_res_pos[i]) && (word_lsb == lsbr_res_pos[i]));
        res = int_64_shift_right(int_64_create(msb_shift_val[1], lsb_shift_val[1]), lsl_n[i]);
        int_64_get_words(res, &word_msb, &word_lsb);
        TEST((word_msb == msbr_res_neg[i]) && (word_lsb == lsbr_res_neg[i]));
    }

    return PASS;
}
