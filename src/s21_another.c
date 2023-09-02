#include "s21_decimal.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ANOTHER
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Округляем в сторону минус бексонечности
int s21_floor(s21_decimal value, s21_decimal *result) {
  int status = CALCULATION_ERROR;
  if (result) {
    status = CALCULATION_OK;
    int scale = s21_get_scale(value);
    if (scale > 0) {
      while (scale--) {
        s21_div_by_10(&value);
      }
      s21_set_scale(&value, 0);
      if (s21_get_sign(value) == MINUS_SIGN) {
        s21_decimal res, tmp;
        s21_from_int_to_decimal(1, &tmp);
        s21_sub(value, tmp, &res);
        value = res;
      }
    }
    if (is_dec_zero(value)) s21_set_sign(&value, PLUS_SIGN);
    *result = value;
  }
  return status;
}

// Округляем до ближайшего целого числа (математическое)
int s21_round(s21_decimal value, s21_decimal *result) {
  int status = CALCULATION_ERROR;
  if (result) {
    status = CALCULATION_OK;
    int scale = s21_get_scale(value);
    if (scale > 0) {
      while (scale-- > 1) {
        s21_div_by_10(&value);
      }
      int last_digit = s21_last_digit(value);
      s21_div_by_10(&value);
      s21_set_scale(&value, 0);
      if (last_digit) {
        standart_round(&value);
      }
    }
    if (is_dec_zero(value)) s21_set_sign(&value, PLUS_SIGN);
    *result = value;
  }
  return status;
}

// Отбрасываем знаки после запятой
int s21_truncate(s21_decimal value, s21_decimal *result) {
  int status = CALCULATION_ERROR;
  if (result) {
    status = CALCULATION_OK;
    int scale = s21_get_scale(value);
    if (scale > 0) {
      while (scale--) {
        s21_div_by_10(&value);
      }
      s21_set_scale(&value, 0);
    }
    if (is_dec_zero(value)) s21_set_sign(&value, PLUS_SIGN);
    *result = value;
  }
  return status;
}

// Результат умножения Decimal на -1
int s21_negate(s21_decimal value, s21_decimal *result) {
  int status = CALCULATION_ERROR;
  if (result != NULL) {
    status = CALCULATION_OK;
    if (s21_get_sign(value) == MINUS_SIGN) {
      s21_set_sign(&value, PLUS_SIGN);
    } else {
      s21_set_sign(&value, MINUS_SIGN);
    }
    *result = value;
  }
  return status;
}

// Округляем до ближайшего четного числа (банковское)
int s21_bank_round(s21_decimal value, s21_decimal *result) {
  int status = CALCULATION_ERROR;
  if (result) {
    status = CALCULATION_OK;
    int scale = s21_get_scale(value);
    if (scale > 0) {
      while (scale-- > 1) {
        s21_div_by_10(&value);
      }
      int last_bank_digit = s21_last_bank_digit(value);
      s21_div_by_10(&value);
      s21_set_scale(&value, 0);
      if (last_bank_digit ||
          (last_bank_digit == 0 && (value.bits[LOW] % 2 == 1))) {
        standart_round(&value);
      }
    }
    if (is_dec_zero(value)) s21_set_sign(&value, PLUS_SIGN);
    *result = value;
  }
  return status;
}