#include "s21_decimal.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// HELP FUNCS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Вспомогательная функция для s21_from_float_to_decimal
void s21_float_to_decimal(float src, s21_decimal *dst) {
  int sign = PLUS_SIGN;
  if (src < 0) {
    sign = MINUS_SIGN;
    src = -src;
  }
  int exp = s21_get_float_scale(src), scale = 0;
  double tmp = (double)src;
  for (; scale < 28 && (int)tmp / (int)powl(2, 21) == 0; tmp *= 10, scale++)
    ;
  tmp = round(tmp);
  for (; fmod(tmp, 10) == 0 && scale > 0; tmp /= 10, scale--)
    ;
  float f = tmp;
  exp = s21_get_float_scale(f);
  if (exp < 96) {
    dst->bits[exp / 32] = 1 << exp % 32;
    for (int i = exp - 1, j = 22; j >= 0; i--, j--)
      if ((*(int *)&f & (0x1 << j)) != 0) dst->bits[i / 32] |= 1 << i % 32;
  } else {
    dst->bits[HIGH] = dst->bits[MID] = dst->bits[LOW] = 4294967295;
  }
  s21_set_sign(dst, sign);
  s21_set_scale(dst, scale);
}

// Узнать экспоненту float'a
int s21_get_float_scale(float src) {
  int t = *(int *)&src;
  return ((t >> 23) & 255) - 127;
}

// Смотрим первую цифру после запятой (для функции округления)
int s21_last_digit(s21_decimal value) {
  int res = 0;
  unsigned int tmp = 0;
  tmp = (unsigned int)value.bits[LOW];
  if (tmp % 10 >= 5) {
    res = 1;
  }
  return res;
}

// Смотрим первую цифру после запятой - равна ли 5 (для функции округления)
int s21_last_bank_digit(s21_decimal value) {
  int res = 0;
  unsigned int tmp = 0;
  tmp = (unsigned int)value.bits[LOW];
  if (tmp % 10 == 5) {
    res = 1;
  }
  return res;
}

// Стандартное округление
void standart_round(s21_decimal *obj) {
  s21_decimal res, tmp;
  s21_from_int_to_decimal(1, &tmp);
  if (s21_get_sign(*obj) == MINUS_SIGN) {
    s21_sub(*obj, tmp, &res);
  } else if (s21_get_sign(*obj) == PLUS_SIGN) {
    s21_add(*obj, tmp, &res);
  }
  *obj = res;
}

// Инициализация s21_decimal нулями
void s21_init_decimal(s21_decimal *obj) {
  for (int i = 0; i < 4; i++) {
    obj->bits[i] = 0;
  }
}

// Узнать знак (+ или -)
int s21_get_sign(s21_decimal num) {
  int mask = 1 << 31;
  return !!(num.bits[SCALE] & mask);
}

// Установить знак (+ или -)
void s21_set_sign(s21_decimal *num, int sign) {
  return s21_set_bit(num, 127, sign);
}

// Узнать бит по порядковому номеру
int s21_get_bit(s21_decimal num, int index) {
  int mask = 1 << (index % 32);
  return !!(num.bits[index / 32] & mask);
}

// Установить bit (0 или 1) в позицию index
void s21_set_bit(s21_decimal *num, int index, int bit) {
  if (bit == 1) {
    num->bits[index / 32] = num->bits[index / 32] | (1 << index % 32);
  } else {
    num->bits[index / 32] = num->bits[index / 32] & ~(1 << index % 32);
  }
}

// Узнать степень
int s21_get_scale(s21_decimal num) {
  s21_set_sign(&num, PLUS_SIGN);
  return num.bits[SCALE] >> 16;
}

// Установить степень
void s21_set_scale(s21_decimal *num, int scale) {
  int sign = s21_get_sign(*num);
  num->bits[SCALE] = (scale << 16);
  s21_set_sign(num, sign);
}

// Делим число в двоичном виде на 10, перебрасываем последний знак в более
// младший бит
void s21_div_by_10(s21_decimal *num) {
  unsigned long long rem = 0, tmp;
  for (int i = 2; i >= 0; i--) {
    tmp = 0;
    tmp = (unsigned long long)num->bits[i] + rem;
    num->bits[i] = (unsigned int)(tmp / 10);
    rem = (tmp % 10) << 32;
  }
}

// Равен ли s21_decimal нулю
int is_dec_zero(s21_decimal d) {
  return (d.bits[LOW] == 0 && d.bits[MID] == 0 && d.bits[HIGH] == 0);
}
