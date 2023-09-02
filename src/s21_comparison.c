#include "s21_decimal.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// COMPARISON
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Меньше
int s21_is_less(s21_decimal d1, s21_decimal d2) {
  s21_big_decimal b;
  operate(d1, d2, IS_LESS, &b);
  return b.bits[LOW];
}

// Меньше или равно
int s21_is_less_or_equal(s21_decimal d1, s21_decimal d2) {
  return (s21_is_less(d1, d2) == true || s21_is_equal(d1, d2) == true);
}

// Больше
int s21_is_greater(s21_decimal d1, s21_decimal d2) {
  return (s21_is_equal(d1, d2) == false && s21_is_less(d1, d2) == false);
}

// Больше или равно
int s21_is_greater_or_equal(s21_decimal d1, s21_decimal d2) {
  return (s21_is_less(d1, d2) == false);
}

// Равно ли
int s21_is_equal(s21_decimal d1, s21_decimal d2) {
  s21_big_decimal b;
  operate(d1, d2, IS_EQUAL, &b);
  return b.bits[LOW];
}

// Не равны ли
int s21_is_not_equal(s21_decimal d1, s21_decimal d2) {
  return (s21_is_equal(d1, d2) == false);
}