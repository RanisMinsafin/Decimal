#include "s21_decimal.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CONVERSION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Из int в s21_decimal
int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int status = CONVERTATION_ERROR;
  if (src != INFINITY && src != -INFINITY && dst != NULL) {
    status = CONVERTATION_OK;
    s21_init_decimal(dst);
    if (src < 0) {
      src = -src;
      s21_set_sign(dst, MINUS_SIGN);
    } else {
      s21_set_sign(dst, PLUS_SIGN);
    }
    dst->bits[LOW] = src;
  }
  return status;
}

// Из s21_decimal в int
int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int status = CONVERTATION_ERROR;
  if (dst != NULL) {
    s21_decimal trunc_dec;
    s21_init_decimal(&trunc_dec);
    s21_truncate(src, &trunc_dec);
    if (trunc_dec.bits[MID] == 0 && trunc_dec.bits[HIGH] == 0) {
      status = CONVERTATION_OK;
      *dst = trunc_dec.bits[LOW];
      if (s21_get_sign(src)) {
        *dst = -*dst;
      }
    }
  }
  return status;
}

// Из s21_decimal во float
int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int status = CONVERTATION_ERROR;
  if (dst != NULL) {
    long double accum = 0;
    status = CONVERTATION_OK;
    int scale = s21_get_scale(src);
    for (int i = 0; i < 96; i++) {
      accum += pow(2, i) * s21_get_bit(src, i);
    }
    accum = accum / pow(10, scale);
    if (s21_get_sign(src) == MINUS_SIGN) {
      accum = -accum;
    }
    *dst = (float)accum;
  }
  return status;
}

// Из float в s21_decimal
int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int status = CONVERTATION_ERROR;
  if (dst != NULL) {
    s21_init_decimal(dst);
    if ((src < 1e-28 && src > 0) || (src < 0 && src > -1e-28)) {
      status = CONVERTATION_ERROR;
      s21_init_decimal(dst);
    } else if (src > 79228162514264337593543950335.0 ||
               src < -79228162514264337593543950335.0 || src == INFINITY ||
               src == -INFINITY) {
      status = CONVERTATION_ERROR;
    } else {
      status = CONVERTATION_OK;
      s21_float_to_decimal(src, dst);
    }
  }
  return status;
}