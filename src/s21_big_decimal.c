#include "s21_decimal.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FOR s21_big_decimal
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Инициализируем s21_big_decimal нулями
void s21_init_big_decimal(s21_big_decimal *obj) {
  for (int i = 0; i < 7; i++) {
    obj->bits[i] = 0;
  }
}

// Конвертация из двух s21_decimal в два s21_big_decimal
void s21_from_decimal_to_big(s21_decimal d1, s21_big_decimal *b1,
                             s21_decimal d2, s21_big_decimal *b2) {
  for (int i = 0; i < 7; i++) {
    if (i < 3) {
      b1->bits[i] = d1.bits[i];
      b2->bits[i] = d2.bits[i];
    } else {
      b1->bits[i] = 0;
      b2->bits[i] = 0;
    }
  }
  b1->bits[6] = d1.bits[SCALE];
  b2->bits[6] = d2.bits[SCALE];
}

// Принимаем 2 s21_decimal, делаем для них арифметическое действие
void operate(s21_decimal d1, s21_decimal d2, int action,
             s21_big_decimal *result) {
  if (is_dec_zero(d1)) {
    d1.bits[SCALE] = 0;
  }
  if (is_dec_zero(d2)) {
    d2.bits[SCALE] = 0;
  }
  s21_big_decimal b1, b2;
  s21_init_big_decimal(result);
  s21_from_decimal_to_big(d1, &b1, d2, &b2);
  if (action == IS_LESS) {
    equalize_scales(&b1, &b2, s21_get_scale(d1), s21_get_scale(d2));
    s21_set_big_sign(&b1, s21_get_sign(d1));
    s21_set_big_sign(&b2, s21_get_sign(d2));
    s21_is_less_big(b1, b2, result);
  } else if (action == IS_EQUAL) {
    equalize_scales(&b1, &b2, s21_get_scale(d1), s21_get_scale(d2));
    s21_set_big_sign(&b1, s21_get_sign(d1));
    s21_set_big_sign(&b2, s21_get_sign(d2));
    s21_is_equal_big(b1, b2, result);
  }
}

// Установка бита в s21_big_decimal
void s21_set_big_bit(s21_big_decimal *num, int index, int bit) {
  if (bit == 1) {
    num->bits[index / 32] = num->bits[index / 32] | (1 << index % 32);
  } else {
    num->bits[index / 32] = num->bits[index / 32] & ~(1 << index % 32);
  }
}

// Установка знака в s21_big_decimal
void s21_set_big_sign(s21_big_decimal *num, int sign) {
  return s21_set_big_bit(num, 223, sign);
}

// Установить степень в s21_big_decimal
void s21_set_big_scale(s21_big_decimal *num, int scale) {
  int sign = s21_get_big_sign(*num);
  num->bits[6] = (scale << 16);
  s21_set_big_sign(num, sign);
}

// Узнать степень s21_big_decimal
int s21_get_big_scale(s21_big_decimal num) {
  s21_set_big_sign(&num, PLUS_SIGN);
  return num.bits[6] >> 16;
}

// Делим число в двоичном виде на 10, перебрасываем последний знак в более
// младший бит в s21_big_decimal
void s21_div_big_by_10(s21_big_decimal *num) {
  unsigned long long rem = 0, tmp;
  for (int i = 5; i >= 0; i--) {
    tmp = 0;
    tmp = (unsigned long long)num->bits[i] + rem;
    num->bits[i] = (unsigned int)(tmp / 10);
    rem = (tmp % 10) << 32;
  }
}

// Поднимаем scale децималов до максимального из двух
void equalize_scales(s21_big_decimal *b1, s21_big_decimal *b2, int scale1,
                     int scale2) {
  if (scale1 < scale2) {
    higher_scale(b1, scale2 - scale1);
    s21_set_big_scale(b2, scale2);
  } else if (scale1 > scale2) {
    higher_scale(b2, scale1 - scale2);
    s21_set_big_scale(b1, scale1);
  }
}

// Повышение степени s21_big_decimal на значение scale
void higher_scale(s21_big_decimal *d, int scale) {
  s21_big_decimal tmp1 = *d, tmp2 = *d, tmp, total;
  s21_init_big_decimal(&total);
  for (int i = 0; i < scale; i++) {
    for (int j = 0; j < 5; j++) {
      // s21_add_big_decimals(tmp1, tmp2, &tmp);
      // s21_add_big_decimals(total, tmp, &total);
      s21_add_big_dec(tmp1, tmp2, &tmp);
      s21_add_big_dec(total, tmp, &total);
    }
    tmp1 = total;
    tmp2 = total;
    *d = total;
    s21_init_big_decimal(&total);
  }
}

// Узнать бит по порядковому номеру в s21_big_decimal
int s21_get_big_bit(s21_big_decimal num, int index) {
  int mask = 1 << (index % 32);
  return !!(num.bits[index / 32] & mask);
}

// Узнать знак (+ или -)
int s21_get_big_sign(s21_big_decimal num) {
  int mask = 1 << 31;
  return !!(num.bits[6] & mask);
}

// Переводим из s21_big_decimal в s21_decimal
int s21_from_big_to_decimal(s21_big_decimal big, s21_decimal *norm) {
  int status = OK, flag = 0;
  int scale = s21_get_big_scale(big);
  if (big.bits[3] != 0 || big.bits[4] != 0 || big.bits[5] != 0) {
    flag = 1;
    for (;
         scale > 0 && big.bits[3] != 0 && big.bits[4] != 0 && big.bits[5] != 0;
         scale--) {
      s21_div_big_by_10(&big);
    }
  }
  if (scale == 0 &&
      (big.bits[3] != 0 || big.bits[4] != 0 || big.bits[5] != 0)) {
    if (s21_get_big_sign(big)) {
      status = NUM_TOO_SMALL;
    } else {
      status = NUM_TOO_BIG;
    }
  }
  if (status == OK) {
    if (flag) {
      s21_decimal tmp;
      s21_init_decimal(&tmp);
      tmp.bits[LOW] = big.bits[LOW];
      tmp.bits[MID] = big.bits[MID];
      tmp.bits[HIGH] = big.bits[HIGH];
      tmp.bits[SCALE] = big.bits[6];
      s21_bank_round(tmp, norm);
    } else {
      norm->bits[LOW] = big.bits[LOW];
      norm->bits[MID] = big.bits[MID];
      norm->bits[HIGH] = big.bits[HIGH];
      norm->bits[SCALE] = big.bits[6];
    }
  }
  return status;
}

// Инвертирование битов s21_big_decimal (без учета bits[6])
void invert_big_dec(s21_big_decimal *obj) {
  for (int i = 0; i < 6; i++) {
    obj->bits[i] = ~obj->bits[i];
  }
}

// Равен ли s21_big_decimal нулю
int is_big_dec_zero(s21_big_decimal obj) {
  return (obj.bits[0] == 0 && obj.bits[1] == 0 && obj.bits[2] == 0 &&
          obj.bits[3] == 0 && obj.bits[4] == 0 && obj.bits[5] == 0);
}

// Проверяем, меньше ли b1 чем b2, записываем результат в res(как int = 1 либо
// 0)
void s21_is_less_big(s21_big_decimal b1, s21_big_decimal b2,
                     s21_big_decimal *res) {
  int ret = true, left, right, flag = true;
  int sign1 = s21_get_big_sign(b1), sign2 = s21_get_big_sign(b2);
  if (sign1 == PLUS_SIGN && sign2 == MINUS_SIGN) {
    ret = false;
  } else if (sign1 == sign2) {
    for (int i = 191; i >= 0 && flag; i--) {
      left = s21_get_big_bit(b1, i);
      right = s21_get_big_bit(b2, i);
      if (left > right) {
        if (sign1 == MINUS_SIGN) {
          flag = false;
        } else {
          ret = false;
          flag = false;
        }
      } else if (right > left) {
        if (sign1 == MINUS_SIGN) {
          ret = false;
          flag = false;
        } else {
          flag = false;
        }
      }
    }
    if (flag == true) {
      ret = false;
    }
  }
  res->bits[LOW] = ret;
}

// Проверяем, равны ли b1 и b2, записываем результат в res(как int = 1 либо 0)
void s21_is_equal_big(s21_big_decimal b1, s21_big_decimal b2,
                      s21_big_decimal *res) {
  int ret = true, left, right;
  int sign1 = s21_get_big_sign(b1), sign2 = s21_get_big_sign(b2);
  if (sign1 != sign2) {
    ret = false;
  } else {
    for (int i = 191; i >= 0 && ret; i--) {
      left = s21_get_big_bit(b1, i);
      right = s21_get_big_bit(b2, i);
      if (left != right) {
        ret = false;
      }
    }
  }
  res->bits[LOW] = ret;
}

/* Проверка больше или равно */
/* функция s21_is_equal_big записывает result единицу, если d1 меньше d2 */
/* функция s21_is_greater_or_equal_big по сути инвертирует s21_is_less_big */
int s21_is_greater_or_equal_big(s21_big_decimal d1, s21_big_decimal d2) {
  s21_big_decimal result = {{0, 0, 0, 0, 0, 0, 0}};
  int ret = true;
  s21_is_less_big(d1, d2, &result);
  if (result.bits[0]) {
    ret = false;
  }
  return ret;
}

s21_big_decimal transformDecimalToBig(s21_decimal num) {
  s21_big_decimal result = {{0, 0, 0, 0, 0, 0, 0}};
  for (int i = 0; i < 3; i++) {
    result.bits[i] = num.bits[i];
  }
  result.bits[6] = num.bits[3];
  return result;
}

/* проверка 1-го, 2-го, 3-го,4 -го, 5-го, 6-го бита big_decimal */
/* для функции деления */
int checkWorkBitsBigDecimal(s21_big_decimal num) {
  int error = 0;
  for (int i = 0; i < 6; i++) {
    if (num.bits[i] != 0) {
      error = 1;
    }
  }
  return error;
}

void s21_add_big_dec(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *result) {
  int remainder = 0, currentBitVal1 = 0, currentBitVal2 = 0, sumBit = 0;
  for (int i = 0; i < 192; i++) {
    currentBitVal1 = s21_get_big_bit(value_1, i);
    currentBitVal2 = s21_get_big_bit(value_2, i);
    sumBit = currentBitVal1 ^ currentBitVal2 ^ remainder;
    s21_set_big_bit(result, i, sumBit);
    remainder = (currentBitVal1 && currentBitVal2) ||
                (currentBitVal1 && remainder) || (currentBitVal2 && remainder);
  }
}

void s21_sub_big_dec(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *result) {
  int currentBitVal1 = 0, currentBitVal2 = 0, diffBit = 0;
  for (int i = 0; i < 192; i++) {
    currentBitVal1 = s21_get_big_bit(value_1, i);
    currentBitVal2 = s21_get_big_bit(value_2, i);
    diffBit = currentBitVal1 ^ currentBitVal2;
    s21_set_big_bit(result, i, diffBit);
    /* ситуация 101 - 10 = 11 (0 - 1 во втором разряде) */
    if (!currentBitVal1 &&
        currentBitVal2) {  // ситуация 101 - 10 = 11 (0 - 1 во втором разряде)
      int nextBit = i + 1;  // следующий бит
      /* ищем разряд у которого можно занять бит
       останавливаемся, когда находим разряд с единицей */
      while (s21_get_big_bit(value_1,
                             nextBit) == 0 &&
             nextBit < 192) {  // ищем разряд у которого можно занять бит
        // останавливаемся, когда находим разряд с единицей
        s21_set_big_bit(&value_1, nextBit, 1);
        nextBit++;  // если не нашли единичку снова переходим к следующему
                    // разряду
      }
      s21_set_big_bit(&value_1, nextBit,
                      0);  // зануляем бит у которого заняли единичку
    }
  }
}

/* вернуть успешное умножение */
int s21_mul_big_dec(s21_big_decimal value_1, s21_big_decimal value_2,
                    s21_big_decimal *result) {
  int scale1 = s21_get_big_scale(value_1);
  int scale2 = s21_get_big_scale(value_2);
  int sign1 = s21_get_big_sign(value_1);
  int sign2 = s21_get_big_sign(value_2);
  s21_big_decimal copyValue1 = {{0, 0, 0, 0, 0, 0, 0}};
  int overflow = 0;
  for (int i = 0; i < 192 && !overflow; i++) {  // !!i < 192
    if (s21_get_big_bit(value_2, i)) {  // если текущий бит равен одному
      copyValue1 = value_1;
      overflow =
          shiftBitsLeftBigDec(&copyValue1, i);  // создать функцию
                                                // сдвиг влево на i элементов
      s21_add_big_dec(copyValue1, *result,
                      result);  // складываем промежуточный результат
    }
    s21_init_big_decimal(&copyValue1);
  }
  s21_set_big_scale(result, scale1 + scale2);  // это работает
  s21_set_big_sign(result, sign1 ^ sign2);
  return overflow;
}

void s21_div_big_dec(s21_big_decimal *value_1, s21_big_decimal value_2,
                     s21_big_decimal *mod) {
  s21_big_decimal sub = {{0, 0, 0, 0, 0, 0, 0}};  // локальное вычитаемое
  s21_big_decimal result = {{0, 0, 0, 0, 0, 0, 0}};  // локальное вычитаемое
  /* количество занятых битов у делимого */
  int sumBits = sum_bits_big_dec(*value_1);  //
  int currentBit = 0;
  while (sumBits--) {
    shiftBitsLeftBigDec(&sub, 1);
    currentBit = s21_get_big_bit(*value_1, sumBits);
    sub.bits[0] ^= currentBit;
    shiftBitsLeftBigDec(&result, 1);

    if (s21_is_greater_or_equal_big(sub, value_2)) {
      s21_sub_big_dec(sub, value_2, &sub);
      result.bits[0] ^= 1;
    }
  }
  *mod = sub;
  *value_1 = result;
}

/* проходимся по битам с конца и ищем первый бит, равный единице */
/* определение количество знаков в s21_big_decimal */
/* для функции деления */
int sum_bits_big_dec(s21_big_decimal value) {
  int sum = 0;
  for (int i = 191; i >= 0 && sum == 0; i--) {
    if (s21_get_big_bit(value, i)) {
      sum = i;
    }
  }
  return sum + 1;
}

/* проверка переполнения s21_big_decimal */
int checkOverflowBigDecimal(s21_big_decimal value) {
  int overflow = 0;
  for (int i = 192; i < 208; i++) {
    if (s21_get_big_bit(value, i) == 1) {
      overflow = 1;
    }
  }
  return overflow;
}

/* сдвиг влево всех битов в s21_big_decimal */
int shiftBitsLeftBigDec(s21_big_decimal *value, int index) {
  int overflow = 0, previousBit = 0;
  if (index) {  // если индекс равен нулю сдвига не будет
    /* для коректной работы нужно создать копию */
    s21_big_decimal copyValue = {0};
    copyValue = *value;
    /* здесь нужно было до 191 цикл делать */
    /* 192-207 первые биты бита со степенью и знаком */
    /* они временно заполняются */
    /* так я могу отслеживать переполнение */
    for (int i = 208; i >= 0; i--) {  //  && !overflow
      previousBit = s21_get_big_bit(copyValue, i - index);
      if (i < index) {
        previousBit = 0;
      }
      s21_set_big_bit(value, i, previousBit);
    }

    /* проверка переполнения */
    if (checkOverflowBigDecimal(*value)) {
      overflow = 1;
    }
  }
  return overflow;
}

void s21_mul_by_10_big(s21_big_decimal *num) {
  s21_big_decimal ten = {{0}};
  s21_big_decimal res = {{0}};
  s21_init_big_decimal(&ten);
  s21_init_big_decimal(&res);
  ten.bits[0] = 10;
  s21_mul_big_dec(*num, ten, &res);
  *num = res;
}

int s21_normalize_big(s21_big_decimal *value_1, s21_big_decimal *value_2) {
  int error = 0, diffScale = 0;
  int scale_1 = s21_get_big_scale(*value_1);
  int scale_2 = s21_get_big_scale(*value_2);
  if (scale_1 != scale_2) {
    if (scale_1 > scale_2) {
      diffScale = scale_1 - scale_2;
      s21_set_big_scale(value_2, scale_1);
      while (diffScale--) {
        s21_mul_by_10_big(value_2);
      }
    } else if (scale_1 < scale_2) {
      diffScale = scale_2 - scale_1;
      s21_set_big_scale(value_1, scale_2);
      while (diffScale--) {
        s21_mul_by_10_big(value_1);
      }
    }
    if (diffScale != 0) {
      error = 1;  // значит до конца не смогли нормализовать
    }
  }
  return error;
}
