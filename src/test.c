#include <check.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_decimal.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// COMPARISON
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Меньше
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_TEST(is_less_0) {
  s21_decimal value_one = {0}, value_two = {0};
  ck_assert_int_eq(0, s21_is_less(value_one, value_two));
}

END_TEST

START_TEST(is_less_1) {
  s21_decimal value_one = {{134, 0, 0, 0}}, value_two = {{0, 556, 0, 0}};
  ck_assert_int_eq(1, s21_is_less(value_one, value_two));
}

END_TEST

START_TEST(is_less_2) {
  s21_decimal value_one = {{777, 0, 0, 0}}, value_two = {{777, 0, 0, 0}};
  ck_assert_int_eq(0, s21_is_less(value_one, value_two));
}

END_TEST

START_TEST(is_less_3) {
  s21_decimal value_one = {{5566, 0, 0, 0}}, value_two = {{4674, 0, 0, 0}};
  ck_assert_int_eq(0, s21_is_less(value_one, value_two));
}

END_TEST

START_TEST(is_less_4) {
  s21_decimal value_one = {{12, 0, 0, 0}}, value_two = {{12, 0, 0, 0}};
  s21_set_bit(&value_two, 127, 1);
  ck_assert_int_eq(0, s21_is_less(value_one, value_two));
}

END_TEST

START_TEST(is_less_5) {
  s21_decimal value_one = {0}, value_two = {0};
  s21_set_bit(&value_one, 127, 1);
  ck_assert_int_eq(0, s21_is_less(value_one, value_two));
}

END_TEST

START_TEST(is_less_6) {
  s21_decimal value_one = {0}, value_two = {0};
  s21_set_bit(&value_one, 127, 1);
  s21_set_bit(&value_two, 127, 0);
  ck_assert_int_eq(0, s21_is_less(value_one, value_two));
}

END_TEST

START_TEST(is_less_7) {
  s21_decimal value_one = {0}, value_two = {0};
  s21_set_bit(&value_one, 127, 1);
  s21_set_bit(&value_two, 127, 0);
  s21_set_bit(&value_one, 77, 1);
  ck_assert_int_eq(1, s21_is_less(value_one, value_two));
}

END_TEST

START_TEST(is_less_8) {
  s21_decimal value_one = {0}, value_two = {0};
  s21_set_bit(&value_one, 127, 1);
  s21_set_bit(&value_two, 127, 1);
  s21_set_bit(&value_one, 77, 1);
  s21_set_scale(&value_one, 5);
  s21_set_scale(&value_two, 5);
  ck_assert_int_eq(1, s21_is_less(value_one, value_two));
}

END_TEST

START_TEST(is_less_9) {
  s21_decimal value_one = {{12, UINT_MAX, 111, 0}},
              value_two = {{0, UINT_MAX, 112, 0}};
  s21_set_scale(&value_one, 12);
  s21_set_scale(&value_two, 11);
  ck_assert_int_eq(1, s21_is_less(value_one, value_two));
}

END_TEST

START_TEST(is_less_10) {
  s21_decimal value_one = {{567, 443, 0, 0}}, value_two = {{567, 444, 0, 0}};
  s21_set_scale(&value_one, 13);
  s21_set_scale(&value_two, 14);
  ck_assert_int_eq(0, s21_is_less(value_one, value_two));
}

END_TEST

START_TEST(is_less_11) {
  s21_decimal value_one = {{0, 44567, 0, 0}}, value_two = {{0, 0, 0, 0}};
  s21_set_bit(&value_one, 127, 1);
  s21_set_bit(&value_two, 127, 1);
  ck_assert_int_eq(1, s21_is_less(value_one, value_two));
}

END_TEST

START_TEST(is_less_12) {
  s21_decimal value_one = {0}, value_two = {0};
  s21_set_bit(&value_one, 127, 1);
  s21_set_bit(&value_two, 127, 1);
  s21_set_bit(&value_one, 45, 1);
  s21_set_scale(&value_one, 16);
  s21_set_scale(&value_two, 15);
  ck_assert_int_eq(1, s21_is_less(value_one, value_two));
}

END_TEST

START_TEST(is_less_13) {
  s21_decimal value_one = {0}, value_two = {0};
  s21_set_bit(&value_one, 127, 1);
  s21_set_bit(&value_two, 127, 1);
  s21_set_bit(&value_one, 77, 1);
  s21_set_bit(&value_two, 76, 1);
  s21_set_scale(&value_one, 15);
  s21_set_scale(&value_two, 16);
  ck_assert_int_eq(1, s21_is_less(value_one, value_two));
}

END_TEST

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Больше
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

START_TEST(is_greater_0) {
  s21_decimal value_one = {0}, value_two = {0};
  ck_assert_int_eq(0, s21_is_greater(value_one, value_two));
}

END_TEST

START_TEST(is_greater_1) {
  s21_decimal value_one = {{134, 0, 0, 0}}, value_two = {{0, 556, 0, 0}};
  ck_assert_int_eq(0, s21_is_greater(value_one, value_two));
}

END_TEST

START_TEST(is_greater_2) {
  s21_decimal value_one = {{777, 0, 0, 0}}, value_two = {{777, 0, 0, 0}};
  ck_assert_int_eq(0, s21_is_greater(value_one, value_two));
}

END_TEST

START_TEST(is_greater_3) {
  s21_decimal value_one = {{5566, 0, 0, 0}}, value_two = {{4674, 0, 0, 0}};
  ck_assert_int_eq(1, s21_is_greater(value_one, value_two));
}

END_TEST

START_TEST(is_greater_4) {
  s21_decimal value_one = {{12, 0, 0, 0}}, value_two = {{12, 0, 0, 0}};
  s21_set_bit(&value_two, 127, 1);
  ck_assert_int_eq(1, s21_is_greater(value_one, value_two));
}

END_TEST

START_TEST(is_greater_5) {
  s21_decimal value_one = {0}, value_two = {0};
  s21_set_bit(&value_two, 127, 1);
  ck_assert_int_eq(0, s21_is_greater(value_one, value_two));
}

END_TEST

START_TEST(is_greater_6) {
  s21_decimal value_one = {0}, value_two = {0};
  s21_set_bit(&value_one, 127, 1);
  s21_set_bit(&value_two, 127, 0);
  ck_assert_int_eq(0, s21_is_greater(value_one, value_two));
}

END_TEST

START_TEST(is_greater_7) {
  s21_decimal value_one = {0}, value_two = {0};
  s21_set_bit(&value_one, 127, 1);
  s21_set_bit(&value_two, 127, 0);
  s21_set_bit(&value_one, 77, 1);
  ck_assert_int_eq(0, s21_is_greater(value_one, value_two));
}

END_TEST

START_TEST(is_greater_8) {
  s21_decimal value_one = {0}, value_two = {0};
  s21_set_bit(&value_one, 127, 1);
  s21_set_bit(&value_two, 127, 1);
  s21_set_bit(&value_one, 77, 1);
  s21_set_scale(&value_one, 5);
  s21_set_scale(&value_two, 5);
  ck_assert_int_eq(0, s21_is_greater(value_one, value_two));
}

END_TEST

START_TEST(is_greater_9) {
  s21_decimal value_one = {{UINT_MAX, 345, 111, 0}},
              value_two = {{UINT_MAX, 345, 112, 0}};
  s21_set_scale(&value_one, 12);
  s21_set_scale(&value_two, 11);
  ck_assert_int_eq(0, s21_is_greater(value_one, value_two));
}

END_TEST

START_TEST(is_greater_10) {
  s21_decimal value_one = {{567, 443, 0, 0}}, value_two = {{567, 444, 0, 0}};
  s21_set_scale(&value_one, 13);
  s21_set_scale(&value_two, 14);
  ck_assert_int_eq(1, s21_is_greater(value_one, value_two));
}

END_TEST

START_TEST(is_greater_11) {
  s21_decimal value_one = {{0, 44567, 0, 0}}, value_two = {{0, 0, 0, 0}};
  s21_set_bit(&value_one, 127, 1);
  s21_set_bit(&value_two, 127, 1);
  ck_assert_int_eq(0, s21_is_greater(value_one, value_two));
}

END_TEST

START_TEST(is_greater_12) {
  s21_decimal value_one = {0}, value_two = {0};
  s21_set_bit(&value_one, 127, 1);
  s21_set_bit(&value_two, 127, 1);
  s21_set_bit(&value_one, 45, 1);
  s21_set_scale(&value_one, 16);
  s21_set_scale(&value_two, 15);
  ck_assert_int_eq(0, s21_is_greater(value_one, value_two));
}

END_TEST

START_TEST(is_greater_13) {
  s21_decimal value_one = {0}, value_two = {0};
  s21_set_bit(&value_one, 127, 1);
  s21_set_bit(&value_two, 127, 1);
  s21_set_bit(&value_one, 77, 1);
  s21_set_bit(&value_two, 76, 1);
  s21_set_scale(&value_one, 15);
  s21_set_scale(&value_two, 16);
  ck_assert_int_eq(0, s21_is_greater(value_one, value_two));
}

END_TEST

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// меньше или равно
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

START_TEST(is_greater_or_equal_0) {
  s21_decimal value_one = {{0, 0, 0, 0}}, value_two = {{0, 0, 0, 0}};
  ck_assert_int_eq(1, s21_is_greater_or_equal(value_one, value_two));
}

END_TEST

START_TEST(is_greater_or_equal_1) {
  s21_decimal value_one = {{655678, 0, 0, 0}}, value_two = {{655678, 0, 0, 0}};
  ck_assert_int_eq(1, s21_is_greater_or_equal(value_one, value_two));
}

END_TEST

START_TEST(is_greater_or_equal_2) {
  s21_decimal value_one = {{UINT_MAX, 0, 0, 0}},
              value_two = {{UINT_MAX, 0, 0, 0}};
  ck_assert_int_eq(1, s21_is_greater_or_equal(value_one, value_two));
}

END_TEST

START_TEST(is_greater_or_equal_3) {
  s21_decimal value_one = {{455678, 246678, 0, 0}},
              value_two = {{455678, 346678, 0, 0}};
  ck_assert_int_eq(0, s21_is_greater_or_equal(value_one, value_two));
}

END_TEST

START_TEST(is_greater_or_equal_4) {
  s21_decimal value_one = {{455678, 346678, 0, 0}},
              value_two = {{455678, 346678, 0, 0}};
  ck_assert_int_eq(1, s21_is_greater_or_equal(value_one, value_two));
}

END_TEST

START_TEST(is_greater_or_equal_5) {
  s21_decimal value_one = {{777, 346678, 455678, 0}},
              value_two = {{777, 346678, 455678, 0}};
  ck_assert_int_eq(1, s21_is_greater_or_equal(value_one, value_two));
}

END_TEST

START_TEST(is_greater_or_equal_6) {
  s21_decimal value_one = {0}, value_two = {0};
  s21_set_bit(&value_one, 127, 1);
  ck_assert_int_eq(1, s21_is_greater_or_equal(value_one, value_two));
}

END_TEST

START_TEST(is_greater_or_equal_7) {
  s21_decimal value_one = {{455678, 346678, 0, 0}},
              value_two = {{455678, 346678, 0, 0}};
  s21_set_scale(&value_one, 14);
  s21_set_scale(&value_two, 13);
  ck_assert_int_eq(0, s21_is_greater_or_equal(value_one, value_two));
}

END_TEST

START_TEST(is_greater_or_equal_8) {
  s21_decimal value_one = {{777, 0, 1234567, 0}},
              value_two = {{777, 202, 1234567, 0}};
  ck_assert_int_eq(0, s21_is_greater_or_equal(value_one, value_two));
}

END_TEST

START_TEST(is_greater_or_equal_9) {
  s21_decimal value_one = {{777, 346678, 455678, 0}},
              value_two = {{777, 346678, 555678, 0}};
  s21_set_scale(&value_one, 12);
  s21_set_scale(&value_two, 13);
  ck_assert_int_eq(1, s21_is_greater_or_equal(value_one, value_two));
}

END_TEST

START_TEST(is_greater_or_equal_10) {
  s21_decimal value_one = {{333, 0, 1234567, 0}},
              value_two = {{333, 202, 1234567, 0}};
  s21_set_bit(&value_one, 127, 1);
  ck_assert_int_eq(0, s21_is_greater_or_equal(value_one, value_two));
}

END_TEST

START_TEST(is_greater_or_equal_11) {
  s21_decimal value_one = {{0, 346678, 0, 0}}, value_two = {{0, 0, 455678, 0}};
  s21_set_bit(&value_one, 127, 1);
  s21_set_bit(&value_two, 127, 1);
  ck_assert_int_eq(1, s21_is_greater_or_equal(value_one, value_two));
}

END_TEST

START_TEST(is_greater_or_equal_12) {
  s21_decimal value_one = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}},
              value_two = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_set_bit(&value_one, 127, 1);
  s21_set_scale(&value_one, 10);
  s21_set_scale(&value_two, 12);
  ck_assert_int_eq(0, s21_is_greater_or_equal(value_one, value_two));
}

END_TEST

START_TEST(is_greater_or_equal_13) {
  s21_decimal value_one = {{67295, 7777666, 1234567, 0}},
              value_two = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_set_bit(&value_one, 127, 1);
  s21_set_scale(&value_one, 10);
  s21_set_scale(&value_two, 10);
  ck_assert_int_eq(0, s21_is_greater_or_equal(value_one, value_two));
}

END_TEST

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// больше или равно
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

START_TEST(is_less_or_equal_0) {
  s21_decimal value_one = {{655678, 0, 0, 0}}, value_two = {{655678, 0, 0, 0}};
  ck_assert_int_eq(1, s21_is_less_or_equal(value_one, value_two));
}

END_TEST

START_TEST(is_less_or_equal_1) {
  s21_decimal value_one = {0}, value_two = {0};
  value_one.bits[0] = 655678;
  value_two.bits[0] = 455678;
  ck_assert_int_eq(0, s21_is_less_or_equal(value_one, value_two));
}

END_TEST

START_TEST(is_less_or_equal_2) {
  s21_decimal value_one = {{UINT_MAX, 0, 0, 0}},
              value_two = {{UINT_MAX, 0, 0, 0}};
  ck_assert_int_eq(1, s21_is_less_or_equal(value_one, value_two));
}

END_TEST

START_TEST(is_less_or_equal_3) {
  s21_decimal value_one = {{455678, 246678, 0, 0}},
              value_two = {{455678, 346678, 0, 0}};
  ck_assert_int_eq(1, s21_is_less_or_equal(value_one, value_two));
}

END_TEST

START_TEST(is_less_or_equal_4) {
  s21_decimal value_one = {{455678, 346678, 0, 0}},
              value_two = {{455678, 346678, 0, 0}};
  ck_assert_int_eq(1, s21_is_less_or_equal(value_one, value_two));
}

END_TEST

START_TEST(is_less_or_equal_5) {
  s21_decimal value_one = {{777, 346678, 455678, 0}},
              value_two = {{777, 346678, 455678, 0}};
  ck_assert_int_eq(1, s21_is_less_or_equal(value_one, value_two));
}

END_TEST

START_TEST(is_less_or_equal_6) {
  s21_decimal value_one = {0}, value_two = {0};
  s21_set_bit(&value_one, 127, 1);
  ck_assert_int_eq(1, s21_is_less_or_equal(value_one, value_two));
}

END_TEST

START_TEST(is_less_or_equal_7) {
  s21_decimal value_one = {{455678, 346678, 0, 0}},
              value_two = {{455678, 346678, 0, 0}};
  s21_set_scale(&value_one, 14);
  s21_set_scale(&value_two, 13);
  ck_assert_int_eq(1, s21_is_less_or_equal(value_one, value_two));
}

END_TEST

START_TEST(is_less_or_equal_8) {
  s21_decimal value_one = {{777, 0, 1234567, 0}},
              value_two = {{777, 202, 1234567, 0}};
  ck_assert_int_eq(1, s21_is_less_or_equal(value_one, value_two));
}

END_TEST

START_TEST(is_less_or_equal_9) {
  s21_decimal value_one = {{777, 346678, 455678, 0}},
              value_two = {{777, 346678, 555678, 0}};
  s21_set_scale(&value_one, 12);
  s21_set_scale(&value_two, 13);
  ck_assert_int_eq(0, s21_is_less_or_equal(value_one, value_two));
}

END_TEST

START_TEST(is_less_or_equal_10) {
  s21_decimal value_one = {{333, 0, 1234567, 0}},
              value_two = {{333, 202, 1234567, 0}};
  s21_set_bit(&value_one, 127, 1);
  ck_assert_int_eq(1, s21_is_less_or_equal(value_one, value_two));
}

END_TEST

START_TEST(is_less_or_equal_11) {
  s21_decimal value_one = {{0, 346678, 0, 0}}, value_two = {{0, 0, 455678, 0}};
  s21_set_bit(&value_one, 127, 1);
  s21_set_bit(&value_two, 127, 1);
  ck_assert_int_eq(0, s21_is_less_or_equal(value_one, value_two));
}

END_TEST

START_TEST(is_less_or_equal_12) {
  s21_decimal value_one = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}},
              value_two = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_set_bit(&value_one, 127, 1);
  s21_set_scale(&value_one, 10);
  s21_set_scale(&value_two, 12);
  ck_assert_int_eq(1, s21_is_less_or_equal(value_one, value_two));
}

END_TEST

START_TEST(is_less_or_equal_13) {
  s21_decimal value_one = {{67295, 7777666, 1234567, ~(UINT_MAX / 2)}},
              value_two = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_set_bit(&value_one, 127, 1);
  s21_set_scale(&value_one, 10);
  s21_set_scale(&value_two, 10);
  ck_assert_int_eq(1, s21_is_less_or_equal(value_one, value_two));
}

END_TEST

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// равно
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

START_TEST(is_equal_0) {
  s21_decimal value_one = {0}, value_two = {0};
  s21_set_sign(&value_two, 1);
  ck_assert_int_eq(1, s21_is_equal(value_one, value_two));
}

START_TEST(is_equal_1) {
  s21_decimal value_one = {0}, value_two = {0};
  s21_set_bit(&value_two, 127, 1);
  ck_assert_int_eq(1, s21_is_equal(value_one, value_two));
}

END_TEST

START_TEST(is_equal_2) {
  s21_decimal value_one = {0}, value_two = {0};
  s21_set_bit(&value_two, 56, 1);
  ck_assert_int_eq(0, s21_is_equal(value_one, value_two));
}

END_TEST

START_TEST(is_equal_3) {
  s21_decimal value_one = {{0, 0, UINT_MAX, 0}},
              value_two = {{0, 0, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_set_bit(&value_two, 127, 1);
  ck_assert_int_eq(0, s21_is_equal(value_one, value_two));
}

END_TEST

START_TEST(is_equal_4) {
  s21_decimal value_one = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}},
              value_two = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  ck_assert_int_eq(1, s21_is_equal(value_one, value_two));
}

END_TEST

START_TEST(is_equal_5) {
  s21_decimal value_one = {0}, value_two = {0};
  s21_set_bit(&value_one, 23, 1);
  s21_set_bit(&value_two, 34, 1);
  ck_assert_int_eq(0, s21_is_equal(value_one, value_two));
}

END_TEST

START_TEST(is_equal_6) {
  s21_decimal value_one = {{777, 0, 1234567, 0}},
              value_two = {{777, 202, 1234567, 0}};
  ck_assert_int_eq(0, s21_is_equal(value_one, value_two));
}

END_TEST

START_TEST(is_equal_7) {
  s21_decimal value_one = {{777, 346678, 455678, 0}},
              value_two = {{777, 346678, 555678, 0}};
  s21_set_bit(&value_one, 127, 1);
  s21_set_scale(&value_one, 3);
  s21_set_scale(&value_two, 3);
  ck_assert_int_eq(0, s21_is_equal(value_one, value_two));
}

END_TEST

START_TEST(is_equal_8) {
  s21_decimal value_one = {0}, value_two = {0};
  s21_set_bit(&value_one, 45, 1);
  s21_set_bit(&value_two, 56, 1);
  s21_set_scale(&value_one, 13);
  s21_set_scale(&value_two, 13);
  ck_assert_int_eq(0, s21_is_equal(value_one, value_two));
}

END_TEST

START_TEST(is_equal_9) {
  s21_decimal value_one = {0}, value_two = {0};
  s21_set_scale(&value_one, 20);
  s21_set_scale(&value_two, 5);
  ck_assert_int_eq(1, s21_is_equal(value_one, value_two));
}

END_TEST

START_TEST(is_equal_10) {
  s21_decimal value_one = {{0, 346678, 0, 0}}, value_two = {{0, 455678, 0, 0}};
  s21_set_bit(&value_one, 127, 1);
  s21_set_bit(&value_two, 127, 1);
  ck_assert_int_eq(0, s21_is_equal(value_one, value_two));
}

END_TEST

START_TEST(is_equal_11) {
  s21_decimal value_one = {{UINT_MAX, UINT_MAX, 0, 0}},
              value_two = {{UINT_MAX, UINT_MAX, 0, 0}};
  s21_set_scale(&value_one, 13);
  s21_set_scale(&value_two, 13);
  ck_assert_int_eq(1, s21_is_equal(value_one, value_two));
}

END_TEST

START_TEST(is_equal_12) {
  s21_decimal value_one = {0}, value_two = {0};
  s21_set_bit(&value_one, 53, 1);
  s21_set_bit(&value_two, 53, 1);
  s21_set_bit(&value_one, 127, 1);
  ck_assert_int_eq(0, s21_is_equal(value_one, value_two));
}

END_TEST

START_TEST(is_equal_13) {
  s21_decimal value_one = {{UINT_MAX, UINT_MAX, 0, 0}},
              value_two = {{UINT_MAX, UINT_MAX, 0, 0}};
  s21_set_scale(&value_one, 13);
  s21_set_scale(&value_two, 12);
  ck_assert_int_eq(0, s21_is_equal(value_one, value_two));
}

END_TEST

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// не равно
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

START_TEST(is_not_equal_0) {
  s21_decimal value_one = {0}, value_two = {0};
  s21_set_sign(&value_two, 1);
  ck_assert_int_eq(0, s21_is_not_equal(value_one, value_two));
}

START_TEST(is_not_equal_1) {
  s21_decimal value_one = {0}, value_two = {0};
  s21_set_bit(&value_two, 127, 1);
  ck_assert_int_eq(0, s21_is_not_equal(value_one, value_two));
}

END_TEST

START_TEST(is_not_equal_2) {
  s21_decimal value_one = {0}, value_two = {0};
  s21_set_bit(&value_two, 56, 1);
  ck_assert_int_eq(1, s21_is_not_equal(value_one, value_two));
}

END_TEST

START_TEST(is_not_equal_3) {
  s21_decimal value_one = {{0, 0, UINT_MAX, 0}},
              value_two = {{0, 0, UINT_MAX, 0}};
  s21_set_bit(&value_two, 127, 1);
  ck_assert_int_eq(1, s21_is_not_equal(value_one, value_two));
}

END_TEST

START_TEST(is_not_equal_4) {
  s21_decimal value_one = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}},
              value_two = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  ck_assert_int_eq(0, s21_is_not_equal(value_one, value_two));
}

END_TEST

START_TEST(is_not_equal_5) {
  s21_decimal value_one = {0}, value_two = {0};
  s21_set_bit(&value_one, 23, 1);
  s21_set_bit(&value_two, 34, 1);
  ck_assert_int_eq(1, s21_is_not_equal(value_one, value_two));
}

END_TEST

START_TEST(is_not_equal_6) {
  s21_decimal value_one = {{777, 0, 1234567, 0}},
              value_two = {{777, 202, 1234567, 0}};
  ck_assert_int_eq(1, s21_is_not_equal(value_one, value_two));
}

END_TEST

START_TEST(is_not_equal_7) {
  s21_decimal value_one = {{777, 346678, 455678, 0}},
              value_two = {{777, 346678, 555678, 0}};
  s21_set_bit(&value_one, 127, 1);
  s21_set_scale(&value_one, 3);
  s21_set_scale(&value_two, 3);
  ck_assert_int_eq(1, s21_is_not_equal(value_one, value_two));
}

END_TEST

START_TEST(is_not_equal_8) {
  s21_decimal value_one = {0}, value_two = {0};
  s21_set_bit(&value_one, 45, 1);
  s21_set_bit(&value_two, 56, 1);
  s21_set_scale(&value_one, 13);
  s21_set_scale(&value_two, 13);
  ck_assert_int_eq(1, s21_is_not_equal(value_one, value_two));
}

END_TEST

START_TEST(is_not_equal_9) {
  s21_decimal value_one = {0}, value_two = {0};
  s21_set_scale(&value_one, 20);
  s21_set_scale(&value_two, 5);
  ck_assert_int_eq(0, s21_is_not_equal(value_one, value_two));
}

END_TEST

START_TEST(is_not_equal_10) {
  s21_decimal value_one = {{0, 346678, 0, 0}}, value_two = {{0, 455678, 0, 0}};
  s21_set_bit(&value_one, 127, 1);
  s21_set_bit(&value_two, 127, 1);
  ck_assert_int_eq(1, s21_is_not_equal(value_one, value_two));
}

END_TEST

START_TEST(is_not_equal_11) {
  s21_decimal value_one = {{UINT_MAX, UINT_MAX, 0, 0}},
              value_two = {{UINT_MAX, UINT_MAX, 0, 0}};
  s21_set_scale(&value_one, 13);
  s21_set_scale(&value_two, 13);
  ck_assert_int_eq(0, s21_is_not_equal(value_one, value_two));
}

END_TEST

START_TEST(is_not_equal_12) {
  s21_decimal value_one = {0}, value_two = {0};
  s21_set_bit(&value_one, 53, 1);
  s21_set_bit(&value_two, 53, 1);
  s21_set_bit(&value_one, 127, 1);
  ck_assert_int_eq(1, s21_is_not_equal(value_one, value_two));
}

END_TEST

START_TEST(is_not_equal_13) {
  s21_decimal value_one = {{UINT_MAX, UINT_MAX, 0, 0}},
              value_two = {{UINT_MAX, UINT_MAX, 0, 0}};
  s21_set_scale(&value_one, 13);
  s21_set_scale(&value_two, 12);
  ck_assert_int_eq(1, s21_is_not_equal(value_one, value_two));
}

END_TEST

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ARITHMETICS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// вычетание
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

START_TEST(sub_0) {
  s21_decimal value_one = {{345668, 3455, 234355, ~(UINT_MAX / 2)}},
              value_two = {{678567, 435, 345554, 566788}}, result;
  ck_assert_int_eq(0, s21_sub(value_one, value_two, &result));
}

END_TEST

START_TEST(sub_1) {
  s21_decimal value_one = {{345668, 3455, 234355, 0}},
              value_two = {{678567, 435, 345554, ~(UINT_MAX / 2)}}, result;
  ck_assert_int_eq(0, s21_sub(value_one, value_two, &result));
}

END_TEST

START_TEST(sub_2) {
  s21_decimal value_one = {{345668, 3455, 234355, ~(UINT_MAX / 2)}},
              value_two = {{678567, 435, 345554, ~(UINT_MAX / 2)}}, result;
  ck_assert_int_eq(0, s21_sub(value_one, value_two, &result));
}

END_TEST

START_TEST(sub_3) {
  s21_decimal value_one = {{23, 456456, 5655665, 34545545}},
              value_two = {{23, 456456, 5655665, 34545545}}, result;
  ck_assert_int_eq(0, s21_sub(value_one, value_two, &result));
}

END_TEST

START_TEST(sub_4) {
  s21_decimal value_one = {{123, 456, 789, 0}},
              value_two = {{987, 654, 321, 0}}, result;
  s21_set_scale(&value_one, 13);
  ck_assert_int_eq(0, s21_sub(value_one, value_two, &result));
}

END_TEST

START_TEST(sub_5) {
  s21_decimal value_one = {{123, 456, 789, 0}},
              value_two = {{987, 654, 321, 0}}, result;
  s21_set_bit(&value_two, 127, 1);
  ck_assert_int_eq(0, s21_sub(value_one, value_two, &result));
}

END_TEST

START_TEST(sub_6) {
  s21_decimal value_one = {{123, 456, 789, ~(UINT_MAX / 2)}},
              value_two = {{987, 654, 321, 0}}, result;
  s21_set_bit(&value_two, 127, 1);
  s21_set_bit(&value_one, 127, 1);
  ck_assert_int_eq(0, s21_sub(value_one, value_two, &result));
}

END_TEST

START_TEST(sub_7) {
  s21_decimal value_one = {{123, 456, 789, ~(UINT_MAX / 2)}},
              value_two = {{987, 654, 321, 0}}, result;
  s21_set_scale(&value_one, 13);
  s21_set_scale(&value_two, 13);
  ck_assert_int_eq(0, s21_sub(value_one, value_two, &result));
}

END_TEST

START_TEST(sub_8) {
  s21_decimal value_one = {{123, 456, 789, 0}},
              value_two = {{987, 654, 321, ~(UINT_MAX / 2)}}, result;
  s21_set_bit(&value_one, 127, 1);
  s21_set_scale(&value_two, 13);
  ck_assert_int_eq(0, s21_sub(value_one, value_two, &result));
}

END_TEST

START_TEST(sub_9) {
  s21_decimal value_one = {0}, value_two = {0}, result;
  s21_set_bit(&value_one, 127, 1);
  s21_set_bit(&value_two, 127, 1);
  ck_assert_int_eq(0, s21_sub(value_one, value_two, &result));
}

END_TEST

START_TEST(sub_10) {
  s21_decimal value_one = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}},
              value_two = {{987, 654, 321, 0}}, result;
  ck_assert_int_eq(2, s21_sub(value_one, value_two, &result));
}

END_TEST

START_TEST(sub_11) {
  s21_decimal value_one = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}},
              value_two = {{987, 654, 321, 0}}, result;
  s21_set_bit(&value_one, 127, 1);
  s21_set_scale(&value_two, 13);
  ck_assert_int_eq(0, s21_sub(value_one, value_two, &result));
}

END_TEST

START_TEST(sub_12) {
  s21_decimal value_one = {{5677, 0, 0, ~(UINT_MAX / 2)}},
              value_two = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}}, result;
  ck_assert_int_eq(2, s21_sub(value_one, value_two, &result));
}

END_TEST

START_TEST(sub_13) {
  s21_decimal value_one = {{5677, 0, 0, 0}},
              value_two = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}}, result;
  ck_assert_int_eq(0, s21_sub(value_one, value_two, &result));
}

END_TEST

START_TEST(sub_14) {
  s21_decimal value_one = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}},
              value_two = {{667, 545, 43, ~(UINT_MAX / 2)}}, result;
  ck_assert_int_eq(1, s21_sub(value_one, value_two, &result));
}

END_TEST

START_TEST(sub_15) {
  s21_decimal value_one = {{667, 545, 43, 0}},
              value_two = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}},
              result;
  ck_assert_int_eq(1, s21_sub(value_one, value_two, &result));
}

END_TEST

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// сложение
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

START_TEST(add_0) {
  s21_decimal value_one = {{123, 456, 789, 0}},
              value_two = {{987, 654, 321, 0}}, result;
  ck_assert_int_eq(0, s21_add(value_one, value_two, &result));
}

END_TEST

START_TEST(add_1) {
  s21_decimal value_one = {{15, 0, 0, 0}},
              value_two = {{15, 0, 0, ~(UINT_MAX / 2)}}, result;
  ck_assert_int_eq(0, s21_add(value_one, value_two, &result));
}

END_TEST

START_TEST(add_2) {
  s21_decimal value_one = {{UINT_MAX, 65656, 9876, 0}},
              value_two = {{677, 0, 777, 0}}, result;
  s21_set_bit(&value_one, 127, 1);
  s21_set_bit(&value_two, 127, 1);
  ck_assert_int_eq(0, s21_add(value_one, value_two, &result));
}

END_TEST

START_TEST(add_3) {
  s21_decimal value_one = {{123, 0, UINT_MAX, 0}},
              value_two = {{0, 777, UINT_MAX, 0}}, result;
  s21_set_scale(&value_one, 12);
  s21_set_scale(&value_two, 12);
  ck_assert_int_eq(0, s21_add(value_one, value_two, &result));
}

END_TEST

START_TEST(add_4) {
  s21_decimal value_one = {{5677, 0, 12333, 0}}, value_two = {{0, 0, 0, 0}},
              result;
  s21_set_scale(&value_one, 19);
  s21_set_bit(&value_two, 86, 1);
  ck_assert_int_eq(0, s21_add(value_one, value_two, &result));
}

END_TEST

START_TEST(add_5) {
  s21_decimal value_one = {{UINT_MAX, 456, 789, 0}},
              value_two = {{987, UINT_MAX, 321, 0}}, result;
  s21_set_scale(&value_one, 6);
  s21_set_scale(&value_two, 4);
  ck_assert_int_eq(0, s21_add(value_one, value_two, &result));
}

END_TEST

START_TEST(add_6) {
  s21_decimal value_one = {{2, 0, 0, ~(UINT_MAX / 2)}},
              value_two = {{8, 0, 0, 0}}, result;
  ck_assert_int_eq(0, s21_add(value_one, value_two, &result));
}

END_TEST

START_TEST(add_7) {
  s21_decimal value_one = {0}, value_two = {0}, result;
  s21_set_bit(&value_two, 127, 1);
  s21_set_bit(&value_two, 33, 1);
  s21_set_bit(&value_one, 86, 1);
  ck_assert_int_eq(0, s21_add(value_one, value_two, &result));
}

END_TEST

START_TEST(add_8) {
  s21_decimal value_one = {{123, 456, 789, 0}},
              value_two = {{987, 654, 321, ~(UINT_MAX / 2)}}, result;
  s21_set_bit(&value_one, 127, 1);
  ck_assert_int_eq(0, s21_add(value_one, value_two, &result));
}

END_TEST

START_TEST(add_9) {
  s21_decimal value_one = {{456, 321, 7777, ~(UINT_MAX / 2)}}, value_two = {0},
              result;
  s21_set_bit(&value_two, 127, 1);
  s21_set_bit(&value_two, 77, 1);
  ck_assert_int_eq(0, s21_add(value_one, value_two, &result));
}

END_TEST

START_TEST(add_10) {
  s21_decimal value_one = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}},
              value_two = {{987, UINT_MAX, 321, 0}}, result;
  s21_set_scale(&value_two, 12);
  ck_assert_int_eq(0, s21_add(value_one, value_two, &result));
}

END_TEST

START_TEST(add_11) {
  s21_decimal value_one = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}},
              value_two = {{4, 0, 0, ~(UINT_MAX / 2)}}, result;
  ck_assert_int_eq(0, s21_add(value_one, value_two, &result));
}

END_TEST

START_TEST(add_12) {
  s21_decimal value_one = {{UINT_MAX, 0, 24444444, 0}},
              value_two = {{UINT_MAX, 45666656, 234444, 0}}, result;
  s21_set_bit(&value_two, 127, 1);
  ck_assert_int_eq(0, s21_add(value_one, value_two, &result));
}

END_TEST

START_TEST(add_13) {
  s21_decimal value_one = {{123, 0, 0, ~(UINT_MAX / 2)}},
              value_two = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}}, result;
  ck_assert_int_eq(0, s21_add(value_one, value_two, &result));
}

END_TEST

START_TEST(add_14) {
  s21_decimal value_one = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}},
              value_two = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}}, result;
  s21_set_scale(&value_one, 5);
  s21_set_scale(&value_two, 3);
  ck_assert_int_eq(0, s21_add(value_one, value_two, &result));
}

END_TEST

START_TEST(add_15) {
  s21_decimal value_one = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}},
              value_two = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}},
              result;
  s21_set_scale(&value_one, 5);
  s21_set_scale(&value_two, 3);
  ck_assert_int_eq(0, s21_add(value_one, value_two, &result));
}

END_TEST

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// умножение
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

START_TEST(mul_0) {
  s21_decimal value_one = {{123, 456, 789, ~(UINT_MAX / 2)}},
              value_two = {{987, 654, 321, 0}}, result = {{0}};
  s21_set_scale(&value_one, 3);
  ck_assert_int_eq(0, s21_mul(value_one, value_two, &result));
}

END_TEST

START_TEST(mul_1) {
  s21_decimal value_one = {{123, 456, 789, 0}},
              value_two = {{987, 654, 321, ~(UINT_MAX / 2)}}, result = {{0}};
  s21_set_bit(&value_two, 127, 1);
  ck_assert_int_eq(2, s21_mul(value_one, value_two, &result));
}

END_TEST

START_TEST(mul_2) {
  s21_decimal value_one = {{123, 456, 789, ~(UINT_MAX / 2)}},
              value_two = {{987, 654, 321, ~(UINT_MAX / 2)}}, result = {{0}};
  ck_assert_int_eq(1, s21_mul(value_one, value_two, &result));
}

END_TEST

START_TEST(mul_3) {
  s21_decimal value_one = {{123, 456, 789, 0}},
              value_two = {{987, 654, 321, 0}}, result = {{0}};
  s21_set_scale(&value_one, 8);
  s21_set_scale(&value_two, 8);
  ck_assert_int_eq(0, s21_mul(value_one, value_two, &result));
}

END_TEST

START_TEST(mul_4) {
  s21_decimal value_one = {{123, 456, UINT_MAX, 0}},
              value_two = {{987, UINT_MAX, 321, 0}}, result = {{0}};
  s21_set_bit(&value_one, 127, 1);
  s21_set_bit(&value_two, 127, 1);
  ck_assert_int_eq(1, s21_mul(value_one, value_two, &result));
}

END_TEST

START_TEST(mul_5) {
  s21_decimal value_one = {{123, 456, 789, 0}},
              value_two = {{987, 654, 321, 0}}, result = {{0}};
  s21_set_bit(&value_one, 127, 1);
  s21_set_bit(&value_two, 127, 1);
  s21_set_scale(&value_one, 12);
  s21_set_scale(&value_two, 14);
  ck_assert_int_eq(0, s21_mul(value_one, value_two, &result));
}

END_TEST

START_TEST(mul_6) {
  s21_decimal value_one = {{123, 456, 0, ~(UINT_MAX / 2)}},
              value_two = {{987, 654, 321, 0}}, result = {{0}};
  s21_set_bit(&value_one, 23, 1);
  ck_assert_int_eq(2, s21_mul(value_one, value_two, &result));
}

END_TEST

START_TEST(mul_7) {
  s21_decimal value_one = {{123, 456, 0, ~(UINT_MAX / 2)}},
              value_two = {{987, 654, 0, 0}}, result = {{0}};
  s21_set_bit(&value_one, 33, 1);
  s21_set_bit(&value_two, 22, 1);
  s21_set_scale(&value_one, 2);
  s21_set_scale(&value_two, 2);
  ck_assert_int_eq(0, s21_mul(value_one, value_two, &result));
}

END_TEST

START_TEST(mul_8) {
  s21_decimal value_one = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}},
              value_two = {{777, 0, 0, ~(UINT_MAX / 2)}}, result = {{0}};
  ck_assert_int_eq(1, s21_mul(value_one, value_two, &result));
}

END_TEST

START_TEST(mul_9) {
  s21_decimal value_one = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}},
              value_two = {{2, 0, 0, 0}}, result = {{0}};
  ck_assert_int_eq(2, s21_mul(value_one, value_two, &result));
}

END_TEST

START_TEST(mul_10) {
  s21_decimal value_one = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}},
              value_two = {{22, 0, 0, 0}}, result = {{0}};
  ck_assert_int_eq(1, s21_mul(value_one, value_two, &result));
}

END_TEST

START_TEST(mul_11) {
  s21_decimal value_one = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}},
              value_two = {{0, 0, 0, 0}}, result = {{0}};
  s21_set_bit(&value_two, 35, 1);
  ck_assert_int_eq(2, s21_mul(value_one, value_two, &result));
}

END_TEST

START_TEST(mul_12) {
  s21_decimal value_one = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}},
              value_two = {{2, 0, 0, 0}}, result = {{0}};
  s21_set_scale(&value_one, 1);
  ck_assert_int_eq(0, s21_mul(value_one, value_two, &result));
}

END_TEST

START_TEST(mul_13) {
  s21_decimal value_one = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}},
              value_two = {{200, 4444, 0, 0}}, result = {{0}};
  s21_set_bit(&value_two, 19, 1);
  s21_set_scale(&value_one, 1);
  s21_set_scale(&value_two, 2);
  ck_assert_int_eq(0, s21_mul(value_one, value_two, &result));
}

END_TEST

START_TEST(mul_14) {
  s21_decimal value_two = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}},
              value_one = {{20, 0, 0, 0}}, result = {{0}};
  s21_set_scale(&value_one, 1);
  s21_set_scale(&value_two, 2);
  ck_assert_int_eq(0, s21_mul(value_one, value_two, &result));
}

END_TEST

START_TEST(mul_15) {
  s21_decimal value_one = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}},
              value_two = {{0, 4444, UINT_MAX, 0}}, result = {{0}};
  s21_set_bit(&value_two, 19, 1);
  s21_set_scale(&value_one, 3);
  s21_set_scale(&value_two, 4);
  s21_set_bit(&value_one, 127, 1);
  s21_set_bit(&value_two, 127, 1);
  ck_assert_int_eq(1, s21_mul(value_one, value_two, &result));
}

END_TEST

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// деление
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

START_TEST(div_0) {
  s21_decimal value_one = {{123, 456, 0, ~(UINT_MAX / 2)}},
              value_two = {{987, 654, 0, 0}}, result;
  ck_assert_int_eq(0, s21_div(value_one, value_two, &result));
}

END_TEST

START_TEST(div_1) {
  s21_decimal value_one = {{123, 456, 789, 0}}, value_two = {{987, 0, 0, 0}},
              result;
  ck_assert_int_eq(0, s21_div(value_one, value_two, &result));
}

END_TEST

START_TEST(div_2) {
  s21_decimal value_one = {{12, 0, 0, 0}}, value_two = {{3, 0, 0, 0}}, result;
  s21_set_bit(&value_two, 127, 1);
  ck_assert_int_eq(0, s21_div(value_one, value_two, &result));
}

END_TEST

START_TEST(div_3) {
  s21_decimal value_one = {{12, 0, UINT_MAX, 0}},
              value_two = {{3, 345, 345, 0}}, result;
  s21_set_bit(&value_one, 127, 1);
  s21_set_bit(&value_two, 127, 1);
  s21_set_scale(&value_two, 15);
  ck_assert_int_eq(0, s21_div(value_one, value_two, &result));
}

END_TEST

START_TEST(div_4) {
  s21_decimal value_one = {{123, 456, 789, 0}},
              value_two = {{987, 654, 321, 0}}, result;
  ck_assert_int_eq(0, s21_div(value_one, value_two, &result));
}

END_TEST

START_TEST(div_5) {
  s21_decimal value_one = {{44444, 345, 0, 0}}, value_two = {{987, 0, 0, 0}},
              result;
  s21_set_bit(&value_two, 56, 1);
  ck_assert_int_eq(0, s21_div(value_one, value_two, &result));
}

END_TEST

START_TEST(div_6) {
  s21_decimal value_one = {{123, 345, 34, 0}}, value_two = {{987, 0, 5673, 0}},
              result;
  s21_set_bit(&value_two, 56, 1);
  s21_set_scale(&value_one, 7);
  s21_set_scale(&value_two, 9);
  ck_assert_int_eq(0, s21_div(value_one, value_two, &result));
}

END_TEST

START_TEST(div_7) {
  s21_decimal value_one = {{UINT_MAX, UINT_MAX, 0, 0}},
              value_two = {{UINT_MAX, UINT_MAX, 0, 0}}, result;
  s21_set_bit(&value_one, 127, 1);
  s21_set_bit(&value_two, 127, 1);
  ck_assert_int_eq(0, s21_div(value_one, value_two, &result));
}

END_TEST

START_TEST(div_8) {
  s21_decimal value_one = {{100, 0, 0, 0}}, value_two = {{25, 0, 0, 0}}, result;
  s21_set_bit(&value_one, 77, 1);
  ck_assert_int_eq(0, s21_div(value_one, value_two, &result));
}

END_TEST

START_TEST(div_9) {
  s21_decimal value_one = {{12, 0, UINT_MAX, 0}},
              value_two = {{3, 0, UINT_MAX, 0}}, result;
  s21_set_bit(&value_two, 127, 1);
  s21_set_scale(&value_one, 13);
  s21_set_scale(&value_two, 13);
  ck_assert_int_eq(0, s21_div(value_one, value_two, &result));
}

END_TEST

START_TEST(div_10) {
  s21_decimal value_one = {0}, value_two = {0}, result;
  s21_set_bit(&value_one, 88, 1);
  s21_set_bit(&value_two, 88, 1);
  s21_set_scale(&value_one, 4);
  s21_set_scale(&value_two, 4);
  ck_assert_int_eq(0, s21_div(value_one, value_two, &result));
}

END_TEST

START_TEST(div_11) {
  s21_decimal value_one = {{0, 0, 36, 0}}, value_two = {{0, 0, 6, 0}}, result;
  s21_set_bit(&value_two, 127, 1);
  s21_set_scale(&value_one, 6);
  s21_set_scale(&value_two, 6);
  ck_assert_int_eq(0, s21_div(value_one, value_two, &result));
}

END_TEST

START_TEST(div_12) {
  s21_decimal value_one = {{50, 0, 0, 0}},
              value_two = {{10, 0, 0, ~(UINT_MAX / 2)}}, result;
  ck_assert_int_eq(0, s21_div(value_one, value_two, &result));
}

END_TEST

START_TEST(div_13) {
  s21_decimal value_one = {{36, 0, 0, ~(UINT_MAX / 2)}},
              value_two = {{2, 0, 0, ~(UINT_MAX / 2)}}, result;
  s21_set_bit(&value_one, 127, 1);
  ck_assert_int_eq(0, s21_div(value_one, value_two, &result));
}

END_TEST

START_TEST(div_14) {
  s21_decimal value_one = {{12, 23, 123, ~(UINT_MAX / 2)}},
              value_two = {{0, 0, 0, 0}}, result;
  ck_assert_int_eq(3, s21_div(value_one, value_two, &result));
}

END_TEST

START_TEST(div_15) {
  s21_decimal value_one = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}},
              value_two = {{0, 0, 0, 0}}, result;
  ck_assert_int_eq(3, s21_div(value_one, value_two, &result));
}

END_TEST

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// остаток от деления
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

START_TEST(mod_0) {
  s21_decimal value_one = {{36, 0, 0, 0}}, value_two = {{7, 0, 0, 0}}, result;
  ck_assert_int_eq(0, s21_mod(value_one, value_two, &result));
}

END_TEST

START_TEST(mod_1) {
  s21_decimal value_one = {{123, 456, 789, ~(UINT_MAX / 2)}},
              value_two = {{345, 345, 0, 0}}, result;
  ck_assert_int_eq(0, s21_mod(value_one, value_two, &result));
}

END_TEST

START_TEST(mod_2) {
  s21_decimal value_one = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}},
              value_two = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}}, result;
  ck_assert_int_eq(0, s21_mod(value_one, value_two, &result));
}

END_TEST

START_TEST(mod_3) {
  s21_decimal value_one = {{123, 456, 789, 0}},
              value_two = {{987, 654, 321, 0}}, result;
  ck_assert_int_eq(0, s21_mod(value_one, value_two, &result));
}

END_TEST

START_TEST(mod_4) {
  s21_decimal value_one = {{123, 456, 789, 0}},
              value_two = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}}, result;
  ck_assert_int_eq(0, s21_mod(value_one, value_two, &result));
}

END_TEST

START_TEST(mod_5) {
  s21_decimal value_one = {{123, 456, 789, 0}},
              value_two = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}}, result;
  s21_set_scale(&value_one, 5);
  s21_set_scale(&value_two, 6);
  ck_assert_int_eq(0, s21_mod(value_one, value_two, &result));
}

END_TEST

START_TEST(mod_6) {
  s21_decimal value_one = {{123, 456, 789, 0}},
              value_two = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}}, result;
  s21_set_scale(&value_one, 2);
  s21_set_scale(&value_two, 2);
  s21_set_bit(&value_one, 127, 1);
  s21_set_bit(&value_two, 127, 1);
  ck_assert_int_eq(0, s21_mod(value_one, value_two, &result));
}

END_TEST

START_TEST(mod_7) {
  s21_decimal value_one = {{123, 456, 789, 0}},
              value_two = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}}, result;
  s21_set_scale(&value_two, 15);
  ck_assert_int_eq(0, s21_mod(value_one, value_two, &result));
}

END_TEST

START_TEST(mod_8) {
  s21_decimal value_one = {{123, 456, 789, ~(UINT_MAX / 2)}},
              value_two = {{0, 0, 0, 0}}, result;
  ck_assert_int_eq(3, s21_mod(value_one, value_two, &result));
}

END_TEST

START_TEST(mod_9) {
  s21_decimal value_one = {{123, 456, 789, 0}}, value_two = {{0, 0, 0, 0}},
              result;
  ck_assert_int_eq(3, s21_mod(value_one, value_two, &result));
}

END_TEST

START_TEST(mod_10) {
  s21_decimal value_one = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}},
              value_two = {{0, 0, 0, 0}}, result;
  s21_set_scale(&value_one, 6);
  ck_assert_int_eq(3, s21_mod(value_one, value_two, &result));
}

END_TEST

START_TEST(mod_11) {
  s21_decimal value_one = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}},
              value_two = {{0, 0, 0, 0}}, result;
  s21_set_bit(&value_two, 127, 1);
  ck_assert_int_eq(3, s21_mod(value_one, value_two, &result));
}

END_TEST

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ANOTHER
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Отбрасываем знаки после запятой
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

START_TEST(truncate_0) {
  s21_decimal value_one = {{7, 7, 7, 0}}, result = {0};
  float result_f = 0, value_two_f = (float)129127208515966861312.0;
  ck_assert_int_eq(0, s21_truncate(value_one, &result));
  s21_from_decimal_to_float(result, &result_f);
  ck_assert_float_eq(value_two_f, result_f);
}

END_TEST

START_TEST(truncate_1) {
  s21_decimal value_one = {{2, 0, 0, ~(UINT_MAX / 2)}}, result = {0};
  float result_f = 0, value_two_f = (float)-2.0;
  ck_assert_int_eq(0, s21_truncate(value_one, &result));
  s21_from_decimal_to_float(result, &result_f);
  ck_assert_float_eq(value_two_f, result_f);
}

END_TEST

START_TEST(truncate_2) {
  s21_decimal value_one = {{2, 0, 0, ~(UINT_MAX / 2)}}, result = {0};
  float result_f = 0, value_two_f = (float)-2.0;
  ck_assert_int_eq(0, s21_truncate(value_one, &result));
  s21_from_decimal_to_float(result, &result_f);
  ck_assert_float_eq(value_two_f, result_f);
}

END_TEST

START_TEST(truncate_3) {
  s21_decimal value_one = {{2, 0, 0, ~(UINT_MAX / 2)}}, result = {0};
  float result_f = 0, value_two_f = (float)-0.0;
  s21_set_scale(&value_one, 5);
  ck_assert_int_eq(0, s21_truncate(value_one, &result));
  s21_from_decimal_to_float(result, &result_f);
  ck_assert_float_eq(value_two_f, result_f);
}

START_TEST(truncate_4) {
  s21_decimal value_one = {{128, 0, 0, 0}};
  s21_decimal result = {0};
  s21_set_scale(&value_one, 1);
  ck_assert_int_eq(0, s21_truncate(value_one, &result));
  float result_f = 0;
  s21_from_decimal_to_float(result, &result_f);
  float value_two_f = 12;
  ck_assert_float_eq(value_two_f, result_f);
}

START_TEST(truncate_5) {
  s21_decimal value_one = {{123456, 0, 0, 0}}, value_two = {{123, 0, 0, 0}},
              result;
  float result_f, value_two_f;
  s21_set_scale(&value_one, 3);
  ck_assert_int_eq(0, s21_truncate(value_one, &result));
  s21_from_decimal_to_float(result, &result_f);
  s21_from_decimal_to_float(value_two, &value_two_f);
  ck_assert_float_eq(result_f, value_two_f);
}

START_TEST(truncate_6) {
  s21_decimal value_one = {{34445667, 0, 0, 0}}, value_two = {{3, 0, 0, 0}},
              result;
  float result_f, value_two_f;
  s21_set_scale(&value_one, 7);
  ck_assert_int_eq(0, s21_truncate(value_one, &result));
  s21_from_decimal_to_float(result, &result_f);
  s21_from_decimal_to_float(value_two, &value_two_f);
  ck_assert_float_eq(result_f, value_two_f);
}

START_TEST(truncate_7) {
  s21_decimal value_one = {{UINT_MAX, 0, 0, 0}},
              value_two = {{4294967, 0, 0, 0}}, result;
  float result_f, value_two_f;
  s21_set_scale(&value_one, 3);
  ck_assert_int_eq(0, s21_truncate(value_one, &result));
  s21_from_decimal_to_float(result, &result_f);
  s21_from_decimal_to_float(value_two, &value_two_f);
  ck_assert_float_eq(result_f, value_two_f);
}

START_TEST(truncate_8) {
  s21_decimal value_one = {{UINT_MAX, 1, 0, 0}}, value_two = {{8, 0, 0, 0}},
              result;
  float result_f, value_two_f;
  s21_set_scale(&value_one, 9);
  ck_assert_int_eq(0, s21_truncate(value_one, &result));
  s21_from_decimal_to_float(result, &result_f);
  s21_from_decimal_to_float(value_two, &value_two_f);
  ck_assert_float_eq(result_f, value_two_f);
}

START_TEST(truncate_9) {
  s21_decimal value_one = {{UINT_MAX, 0, 0, 0}}, value_two = {{0, 0, 0, 0}},
              result;
  float result_f, value_two_f;
  s21_set_scale(&value_one, 10);
  ck_assert_int_eq(0, s21_truncate(value_one, &result));
  s21_from_decimal_to_float(result, &result_f);
  s21_from_decimal_to_float(value_two, &value_two_f);
  ck_assert_float_eq(result_f, value_two_f);
  s21_float_to_decimal(result_f, &result);
}

START_TEST(truncate_10) {
  s21_decimal value_one = {{UINT_MAX, 0, 0, 0}}, value_two = {{4, 0, 0, 0}},
              result;
  float result_f, value_two_f;
  s21_set_scale(&value_one, 9);
  ck_assert_int_eq(0, s21_truncate(value_one, &result));
  s21_from_decimal_to_float(result, &result_f);
  s21_from_decimal_to_float(value_two, &value_two_f);
  ck_assert_float_eq(result_f, value_two_f);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Возвращает результат умножения указанного Decimal на -1
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

START_TEST(negate_0) {
  s21_decimal value_one = {{2, 0, 0, 0}}, result = {0};
  s21_negate(value_one, &result);
  ck_assert_int_ne(s21_get_sign(value_one), s21_get_sign(result));
}

END_TEST

START_TEST(negate_1) {
  s21_decimal value_one = {{2, 0, 0, ~(UINT_MAX / 2)}}, result = {0};
  s21_negate(value_one, &result);
  ck_assert_int_ne(s21_get_sign(value_one), s21_get_sign(result));
}

END_TEST

START_TEST(negate_2) {
  s21_decimal value_one = {{0, 0, 0, ~(UINT_MAX / 2)}}, result = {0};
  s21_negate(value_one, &result);
  ck_assert_int_ne(s21_get_sign(value_one), s21_get_sign(result));
}

END_TEST

START_TEST(negate_3) {
  s21_decimal value_one = {0}, result = {0};
  s21_negate(value_one, &result);
  ck_assert_int_ne(s21_get_sign(value_one), s21_get_sign(result));
}

END_TEST

START_TEST(negate_4) {
  s21_decimal value_one = {{655678, 0, 0, 0}}, result = {0};
  s21_negate(value_one, &result);
  ck_assert_int_ne(s21_get_sign(result), s21_get_sign(value_one));
}

END_TEST

START_TEST(negate_5) {
  s21_decimal value_one = {{777, 346678, 455678, 0}}, result = {0};
  s21_negate(value_one, &result);
  ck_assert_int_ne(s21_get_sign(result), s21_get_sign(value_one));
}

END_TEST

START_TEST(negate_6) {
  s21_decimal value_one = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}}, result = {0};
  s21_negate(value_one, &result);
  ck_assert_int_ne(s21_get_sign(result), s21_get_sign(value_one));
}

END_TEST

START_TEST(negate_7) {
  s21_decimal value_one = {{67295, 7777666, 1234567, 0}}, result = {0};
  s21_set_bit(&value_one, 127, 1);
  s21_set_scale(&value_one, 10);
  s21_negate(value_one, &result);
  ck_assert_int_ne(s21_get_sign(result), s21_get_sign(value_one));
}

END_TEST

START_TEST(negate_8) {
  s21_decimal value_one = {{0, 346678, 0, 0}}, result = {0};
  s21_negate(value_one, &result);
  ck_assert_int_ne(s21_get_sign(result), s21_get_sign(value_one));
}

END_TEST

START_TEST(negate_9) {
  s21_decimal value_one = {{UINT_MAX, 346678, UINT_MAX, 0}}, result = {0};
  s21_negate(value_one, &result);
  ck_assert_int_ne(s21_get_sign(result), s21_get_sign(value_one));
}

END_TEST

START_TEST(negate_10) {
  s21_decimal value_one = {{UINT_MAX, UINT_MAX, 0, 0}}, result = {0};
  s21_set_bit(&value_one, 127, 1);
  s21_set_scale(&value_one, 5);
  s21_negate(value_one, &result);
  ck_assert_int_ne(s21_get_sign(result), s21_get_sign(value_one));
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// округляет указанное Decimal число до ближайшего целого числа в сторону
// отрицательной бесконечности
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

START_TEST(floor_0) {
  s21_decimal value_one = {{4, 0, 0, 0}}, result = {0};
  ck_assert_int_eq(0, s21_floor(value_one, &result));
}

END_TEST

START_TEST(floor_1) {
  s21_decimal value_one = {{2, 0, 0, ~(UINT_MAX / 2)}}, result = {0};
  float result_f = 0;
  s21_floor(value_one, &result);
  s21_from_decimal_to_float(result, &result_f);
  ck_assert_float_eq(-2, result_f);
}

END_TEST

START_TEST(floor_2) {
  s21_decimal value_one = {{2, 0, 0, ~(UINT_MAX / 2)}}, result = {0};
  float result_f = 0;
  s21_set_scale(&value_one, 5);
  s21_floor(value_one, &result);
  s21_from_decimal_to_float(result, &result_f);
  ck_assert_float_eq(-1, result_f);
}

END_TEST

START_TEST(floor_3) {
  s21_decimal value_one = {{2, 0, 0, 0}}, result = {0};
  float result_f = 0;
  s21_set_scale(&value_one, 5);
  s21_floor(value_one, &result);
  s21_from_decimal_to_float(result, &result_f);
  ck_assert_float_eq(0, result_f);
}

END_TEST

START_TEST(floor_4) {
  s21_decimal value_one = {{123456, 0, 0, 0}}, value_two = {{124, 0, 0, 0}},
              result = {0};
  float result_f, value_two_f;
  s21_set_bit(&value_one, 127, 1);
  s21_set_bit(&value_two, 127, 1);
  s21_set_scale(&value_one, 3);
  s21_floor(value_one, &result);
  s21_from_decimal_to_float(result, &result_f);
  s21_from_decimal_to_float(value_two, &value_two_f);
  ck_assert_float_eq(result_f, value_two_f);
}

END_TEST

START_TEST(floor_5) {
  s21_decimal value_one = {{87654, 0, 0, 0}}, value_two = {{9, 0, 0, 0}},
              result = {0};
  float result_f, value_two_f;
  s21_set_bit(&value_one, 127, 1);
  s21_set_bit(&value_two, 127, 1);
  s21_set_scale(&value_one, 4);
  s21_floor(value_one, &result);
  s21_from_decimal_to_float(result, &result_f);
  s21_from_decimal_to_float(value_two, &value_two_f);
  s21_get_float_scale(value_two_f);
  ck_assert_float_eq(result_f, value_two_f);
}

END_TEST

START_TEST(floor_6) {
  s21_decimal value_one = {{11, 0, 0, 0}}, value_two = {{2, 0, 0, 0}},
              result = {0};
  float result_f, value_two_f;
  s21_set_bit(&value_one, 127, 1);
  s21_set_bit(&value_two, 127, 1);
  s21_set_scale(&value_one, 1);
  s21_floor(value_one, &result);
  s21_from_decimal_to_float(result, &result_f);
  s21_from_decimal_to_float(value_two, &value_two_f);
  ck_assert_float_eq(result_f, value_two_f);
}

END_TEST

START_TEST(floor_7) {
  s21_decimal value_one = {{34, 0, 0, 0}}, value_two = {{1, 0, 0, 0}},
              result = {0};
  float result_f, value_two_f;
  s21_set_bit(&value_one, 127, 1);
  s21_set_bit(&value_two, 127, 1);
  s21_set_scale(&value_one, 3);
  s21_floor(value_one, &result);
  s21_from_decimal_to_float(result, &result_f);
  s21_from_decimal_to_float(value_two, &value_two_f);
  ck_assert_float_eq(result_f, value_two_f);
}

END_TEST

START_TEST(floor_8) {
  s21_decimal value_one = {{7777777, 0, 0, 0}}, value_two = {{78, 0, 0, 0}},
              result = {0};
  float result_f, value_two_f;
  s21_set_bit(&value_one, 127, 1);
  s21_set_bit(&value_two, 127, 1);
  s21_set_scale(&value_one, 5);
  s21_floor(value_one, &result);
  s21_from_decimal_to_float(result, &result_f);
  s21_from_decimal_to_float(value_two, &value_two_f);
  ck_assert_float_eq(result_f, value_two_f);
}

END_TEST

START_TEST(floor_9) {
  s21_decimal value_one = {{123456789, 0, 0, 0}}, value_two = {{1, 0, 0, 0}},
              result = {0};
  float result_f, value_two_f;
  s21_set_bit(&value_one, 127, 1);
  s21_set_bit(&value_two, 127, 1);
  s21_set_scale(&value_one, 9);
  s21_floor(value_one, &result);
  s21_from_decimal_to_float(result, &result_f);
  s21_from_decimal_to_float(value_two, &value_two_f);
  ck_assert_float_eq(result_f, value_two_f);
}

END_TEST

START_TEST(floor_10) {
  s21_decimal value_one = {{UINT_MAX, 0, 0, 0}}, value_two = {{43, 0, 0, 0}},
              result = {0};
  float result_f, value_two_f;
  s21_set_bit(&value_one, 127, 1);
  s21_set_bit(&value_two, 127, 1);
  s21_set_scale(&value_one, 8);
  s21_floor(value_one, &result);
  s21_from_decimal_to_float(result, &result_f);
  s21_from_decimal_to_float(value_two, &value_two_f);
  ck_assert_float_eq(result_f, value_two_f);
}

END_TEST

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Функция округляет Decimal до ближайшего целого числа
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

START_TEST(round_0) {
  s21_decimal value_one = {{7, 7, 7, 0}}, result = {0};
  float result_f = 0, value_two_f = (float)129127208515966861312.0;
  s21_round(value_one, &result);
  s21_from_decimal_to_float(result, &result_f);
  ck_assert_float_eq(value_two_f, result_f);
}

END_TEST

START_TEST(round_1) {
  s21_decimal value_one = {{3, 3, 3, ~(UINT_MAX / 2)}}, result = {0};
  ck_assert_int_eq(0, s21_round(value_one, &result));
}

END_TEST

START_TEST(round_2) {
  s21_decimal value_one = {{3, 3, 3, 0}}, result = {0};
  s21_set_scale(&value_one, 5);
  ck_assert_int_eq(0, s21_round(value_one, &result));
}

END_TEST

START_TEST(round_3) {
  s21_decimal value_one = {{7, 7, 7, ~(UINT_MAX / 2)}}, result = {0};
  s21_set_scale(&value_one, 5);
  ck_assert_int_eq(0, s21_round(value_one, &result));
}

END_TEST

START_TEST(round_4) {
  s21_decimal value_one = {{25, 0, 0, ~(UINT_MAX / 2)}}, result = {0};
  s21_set_scale(&value_one, 1);
  ck_assert_int_eq(0, s21_round(value_one, &result));
}

END_TEST

START_TEST(round_5) {
  s21_decimal value_one = {{26, 0, 0, 0}}, result = {0};
  s21_set_scale(&value_one, 1);
  ck_assert_int_eq(0, s21_round(value_one, &result));
}

END_TEST

START_TEST(round_6) {
  s21_decimal value_one = {{115, 0, 0, 0}}, result = {0};
  s21_set_scale(&value_one, 1);
  ck_assert_int_eq(0, s21_round(value_one, &result));
}

END_TEST

START_TEST(round_7) {
  s21_decimal value_one = {{118, 0, 0, 0}}, result = {0};
  s21_set_scale(&value_one, 1);
  ck_assert_int_eq(0, s21_round(value_one, &result));
}

END_TEST

START_TEST(round_8) {
  s21_decimal value_one = {{125, 0, 0, 0}}, result = {0};
  s21_set_scale(&value_one, 1);
  ck_assert_int_eq(0, s21_round(value_one, &result));
}

END_TEST

START_TEST(round_9) {
  s21_decimal value_one = {{345, 0, 0, 0}}, result = {0};
  s21_set_scale(&value_one, 1);
  ck_assert_int_eq(0, s21_round(value_one, &result));
}

END_TEST

START_TEST(round_10) {
  s21_decimal value_one = {{128, 0, 0, 0}}, result = {0};
  float result_f = 0, value_two_f = 13;
  s21_set_scale(&value_one, 1);
  s21_round(value_one, &result);
  s21_from_decimal_to_float(result, &result_f);
  ck_assert_float_eq(value_two_f, result_f);
}

END_TEST

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CONVERSION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Из s21_decimal во float
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

START_TEST(from_decimal_to_float_0) {
  s21_decimal value_one = {{456123, 0, 0, 0}};
  float result = 0.456123, value_one_f;
  s21_set_scale(&value_one, 6);
  s21_from_decimal_to_float(value_one, &value_one_f);
  ck_assert_float_eq(result, value_one_f);
}

END_TEST

START_TEST(from_decimal_to_float_1) {
  s21_decimal value_one = {{77777, 0, 0, 0}};
  float result = -777.77, value_one_f;
  s21_set_bit(&value_one, 127, 1);
  s21_set_scale(&value_one, 2);
  s21_from_decimal_to_float(value_one, &value_one_f);
  ck_assert_float_eq(result, value_one_f);
}

END_TEST

START_TEST(from_decimal_to_float_2) {
  s21_decimal value_one = {{123456789, 0, 0, 0}};
  float result = -1234.56789, value_one_f;
  s21_set_bit(&value_one, 127, 1);
  s21_set_scale(&value_one, 5);
  s21_from_decimal_to_float(value_one, &value_one_f);
  ck_assert_float_eq(result, value_one_f);
}

END_TEST

START_TEST(from_decimal_to_float_3) {
  s21_decimal value_one = {{123456789, 1, 0, 0}};
  float result = 4.418424084, value_one_f;
  s21_set_scale(&value_one, 9);
  s21_from_decimal_to_float(value_one, &value_one_f);
  ck_assert_float_eq(result, value_one_f);
}

END_TEST

START_TEST(from_decimal_to_float_4) {
  s21_decimal value_one = {{UINT_MAX, 0, 0, 0}};
  float result = 42.94967295, value_one_f;
  s21_set_scale(&value_one, 8);
  s21_from_decimal_to_float(value_one, &value_one_f);
  ck_assert_float_eq(result, value_one_f);
}

END_TEST

START_TEST(from_decimal_to_float_5) {
  s21_decimal value_one = {{UINT_MAX, 1, 0, 0}};
  float result = 85.89934590, value_one_f;
  s21_set_scale(&value_one, 8);
  s21_from_decimal_to_float(value_one, &value_one_f);
  ck_assert_float_eq(result, value_one_f);
}

END_TEST

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Из float во s21_decimal
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

START_TEST(from_float_to_decimal_0) {
  s21_decimal value_one = {{0, 0, 0, 0}};
  float result, value_one_f = -INFINITY;
  s21_from_float_to_decimal(value_one_f, &value_one);
  s21_from_decimal_to_float(value_one, &result);
  ck_assert_float_eq(result, 0);
}

END_TEST

START_TEST(from_float_to_decimal_1) {
  s21_decimal value_one = {{0, 0, 0, 0}};
  float result, value_one_f = -7777777.777;
  s21_from_float_to_decimal(value_one_f, &value_one);
  s21_from_decimal_to_float(value_one, &result);
  ck_assert_float_eq(result, value_one_f);
}

END_TEST

START_TEST(from_float_to_decimal_2) {
  s21_decimal value_one = {{0, 0, 0, 0}};
  float result, value_one_f = 8589934590;
  s21_from_float_to_decimal(value_one_f, &value_one);
  s21_from_decimal_to_float(value_one, &result);
  ck_assert_float_eq(result, value_one_f);
}

END_TEST

START_TEST(from_float_to_decimal_3) {
  s21_decimal value_one = {{0, 0, 0, 0}};
  float result, value_one_f = -1234.56789;
  s21_from_float_to_decimal(value_one_f, &value_one);
  s21_from_decimal_to_float(value_one, &result);
  ck_assert_float_eq(result, value_one_f);
}

END_TEST

START_TEST(from_float_to_decimal_4) {
  s21_decimal value_one = {{0, 0, 0, 0}};
  float result, value_one_f = 4294.967;
  s21_from_float_to_decimal(value_one_f, &value_one);
  s21_from_decimal_to_float(value_one, &result);
  ck_assert_float_eq(result, value_one_f);
}

END_TEST

START_TEST(from_float_to_decimal_5) {
  s21_decimal value_one = {{0, 0, 0, 0}};
  float result, value_one_f = -85899345.90;
  s21_from_float_to_decimal(value_one_f, &value_one);
  s21_from_decimal_to_float(value_one, &result);
  ck_assert_float_eq(result, value_one_f);
}

END_TEST

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Из s21_decimal в int
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

START_TEST(from_decimal_to_int_0) {
  s21_decimal value_one = {{456789, 0, 0, 0}};
  int result = 456789, value_one_i = 0;
  s21_from_decimal_to_int(value_one, &value_one_i);
  ck_assert_int_eq(value_one_i, result);
}

END_TEST

START_TEST(from_decimal_to_int_1) {
  s21_decimal value_one = {{123456789, 0, 0, 0}};
  int result = 123456789, value_one_i = 0;
  s21_from_decimal_to_int(value_one, &value_one_i);
  ck_assert_int_eq(value_one_i, result);
}

END_TEST

START_TEST(from_decimal_to_int_2) {
  s21_decimal value_one = {{19121993, 0, 0, 0}};
  int result = -19121993, value_one_i = 0;
  s21_set_bit(&value_one, 127, 1);
  s21_from_decimal_to_int(value_one, &value_one_i);
  ck_assert_int_eq(value_one_i, result);
}

END_TEST

START_TEST(from_decimal_to_int_3) {
  s21_decimal value_one = {{7777777, 0, 0, 0}};
  int result = 7777777, value_one_i = 0;
  s21_from_decimal_to_int(value_one, &value_one_i);
  ck_assert_int_eq(value_one_i, result);
}

END_TEST

START_TEST(from_decimal_to_int_4) {
  s21_decimal value_one = {{UINT_MAX, 0, 0, 0}};
  int result = -UINT_MAX, value_one_i = 0;
  s21_set_bit(&value_one, 127, 1);
  s21_from_decimal_to_int(value_one, &value_one_i);
  ck_assert_int_eq(value_one_i, result);
}

END_TEST

START_TEST(from_decimal_to_int_5) {
  s21_decimal value_one = {{UINT_MAX, 0, 0, 0}};
  int result = UINT_MAX, value_one_i = 0;
  s21_from_decimal_to_int(value_one, &value_one_i);
  ck_assert_int_eq(value_one_i, result);
}

END_TEST

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Из int в s21_decimal
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

START_TEST(from_int_to_decimal_0) {
  s21_decimal value_one = {{0, 0, 0, 0}};
  int result, value_one_i = 987654321;
  s21_from_int_to_decimal(value_one_i, &value_one);
  s21_from_decimal_to_int(value_one, &result);
  ck_assert_int_eq(result, value_one_i);
}

END_TEST

START_TEST(from_int_to_decimal_1) {
  s21_decimal value_one = {{0, 0, 0, 0}};
  int result, value_one_i = -123456789;
  s21_from_int_to_decimal(value_one_i, &value_one);
  s21_from_decimal_to_int(value_one, &result);
  ck_assert_int_eq(result, value_one_i);
}

END_TEST

START_TEST(from_int_to_decimal_2) {
  s21_decimal value_one = {{0, 0, 0, 0}};
  int result, value_one_i = -19121993;
  s21_from_int_to_decimal(value_one_i, &value_one);
  s21_from_decimal_to_int(value_one, &result);
  ck_assert_int_eq(result, value_one_i);
}

END_TEST

START_TEST(from_int_to_decimal_3) {
  s21_decimal value_one = {{0, 0, 0, 0}};
  int result, value_one_i = 7777777;
  s21_from_int_to_decimal(value_one_i, &value_one);
  s21_from_decimal_to_int(value_one, &result);
  ck_assert_int_eq(result, value_one_i);
}

END_TEST

START_TEST(from_int_to_decimal_4) {
  s21_decimal value_one = {{0, 0, 0, 0}};
  int result, value_one_i = UINT_MAX;
  s21_from_int_to_decimal(value_one_i, &value_one);
  s21_from_decimal_to_int(value_one, &result);
  ck_assert_int_eq(result, value_one_i);
}

END_TEST

START_TEST(from_int_to_decimal_5) {
  s21_decimal value_one = {{0, 0, 0, 0}};
  int result, value_one_i = -UINT_MAX;
  s21_from_int_to_decimal(value_one_i, &value_one);
  s21_from_decimal_to_int(value_one, &result);
  ck_assert_int_eq(result, value_one_i);
}

END_TEST

Suite *

s21_decimal_suite(void) {
  Suite *suite;

  suite = suite_create("s21_decimal");
  TCase *tcase_core = tcase_create("Core");

  // меньше
  tcase_add_test(tcase_core, is_less_0);
  tcase_add_test(tcase_core, is_less_1);
  tcase_add_test(tcase_core, is_less_2);
  tcase_add_test(tcase_core, is_less_3);
  tcase_add_test(tcase_core, is_less_4);
  tcase_add_test(tcase_core, is_less_5);
  tcase_add_test(tcase_core, is_less_6);
  tcase_add_test(tcase_core, is_less_7);
  tcase_add_test(tcase_core, is_less_8);
  tcase_add_test(tcase_core, is_less_9);
  tcase_add_test(tcase_core, is_less_10);
  tcase_add_test(tcase_core, is_less_11);
  tcase_add_test(tcase_core, is_less_12);
  tcase_add_test(tcase_core, is_less_13);

  // больше
  tcase_add_test(tcase_core, is_greater_0);
  tcase_add_test(tcase_core, is_greater_1);
  tcase_add_test(tcase_core, is_greater_2);
  tcase_add_test(tcase_core, is_greater_3);
  tcase_add_test(tcase_core, is_greater_4);
  tcase_add_test(tcase_core, is_greater_5);
  tcase_add_test(tcase_core, is_greater_6);
  tcase_add_test(tcase_core, is_greater_7);
  tcase_add_test(tcase_core, is_greater_8);
  tcase_add_test(tcase_core, is_greater_9);
  tcase_add_test(tcase_core, is_greater_10);
  tcase_add_test(tcase_core, is_greater_11);
  tcase_add_test(tcase_core, is_greater_12);
  tcase_add_test(tcase_core, is_greater_13);

  // больше или равно
  tcase_add_test(tcase_core, is_greater_or_equal_0);
  tcase_add_test(tcase_core, is_greater_or_equal_1);
  tcase_add_test(tcase_core, is_greater_or_equal_2);
  tcase_add_test(tcase_core, is_greater_or_equal_3);
  tcase_add_test(tcase_core, is_greater_or_equal_4);
  tcase_add_test(tcase_core, is_greater_or_equal_5);
  tcase_add_test(tcase_core, is_greater_or_equal_6);
  tcase_add_test(tcase_core, is_greater_or_equal_7);
  tcase_add_test(tcase_core, is_greater_or_equal_8);
  tcase_add_test(tcase_core, is_greater_or_equal_9);
  tcase_add_test(tcase_core, is_greater_or_equal_10);
  tcase_add_test(tcase_core, is_greater_or_equal_11);
  tcase_add_test(tcase_core, is_greater_or_equal_12);
  tcase_add_test(tcase_core, is_greater_or_equal_13);

  // меньше или равно
  tcase_add_test(tcase_core, is_less_or_equal_0);
  tcase_add_test(tcase_core, is_less_or_equal_1);
  tcase_add_test(tcase_core, is_less_or_equal_2);
  tcase_add_test(tcase_core, is_less_or_equal_3);
  tcase_add_test(tcase_core, is_less_or_equal_4);
  tcase_add_test(tcase_core, is_less_or_equal_5);
  tcase_add_test(tcase_core, is_less_or_equal_6);
  tcase_add_test(tcase_core, is_less_or_equal_7);
  tcase_add_test(tcase_core, is_less_or_equal_8);
  tcase_add_test(tcase_core, is_less_or_equal_9);
  tcase_add_test(tcase_core, is_less_or_equal_10);
  tcase_add_test(tcase_core, is_less_or_equal_11);
  tcase_add_test(tcase_core, is_less_or_equal_12);
  tcase_add_test(tcase_core, is_less_or_equal_13);

  // равно
  tcase_add_test(tcase_core, is_equal_0);
  tcase_add_test(tcase_core, is_equal_1);
  tcase_add_test(tcase_core, is_equal_2);
  tcase_add_test(tcase_core, is_equal_3);
  tcase_add_test(tcase_core, is_equal_4);
  tcase_add_test(tcase_core, is_equal_5);
  tcase_add_test(tcase_core, is_equal_6);
  tcase_add_test(tcase_core, is_equal_7);
  tcase_add_test(tcase_core, is_equal_8);
  tcase_add_test(tcase_core, is_equal_9);
  tcase_add_test(tcase_core, is_equal_10);
  tcase_add_test(tcase_core, is_equal_11);
  tcase_add_test(tcase_core, is_equal_12);
  tcase_add_test(tcase_core, is_equal_13);

  //  не равно
  tcase_add_test(tcase_core, is_not_equal_0);
  tcase_add_test(tcase_core, is_not_equal_1);
  tcase_add_test(tcase_core, is_not_equal_2);
  tcase_add_test(tcase_core, is_not_equal_3);
  tcase_add_test(tcase_core, is_not_equal_4);
  tcase_add_test(tcase_core, is_not_equal_5);
  tcase_add_test(tcase_core, is_not_equal_6);
  tcase_add_test(tcase_core, is_not_equal_7);
  tcase_add_test(tcase_core, is_not_equal_8);
  tcase_add_test(tcase_core, is_not_equal_9);
  tcase_add_test(tcase_core, is_not_equal_10);
  tcase_add_test(tcase_core, is_not_equal_11);
  tcase_add_test(tcase_core, is_not_equal_12);
  tcase_add_test(tcase_core, is_not_equal_13);

  // вычетание
  tcase_add_test(tcase_core, sub_0);
  tcase_add_test(tcase_core, sub_1);
  tcase_add_test(tcase_core, sub_2);
  tcase_add_test(tcase_core, sub_3);
  tcase_add_test(tcase_core, sub_4);
  tcase_add_test(tcase_core, sub_5);
  tcase_add_test(tcase_core, sub_6);
  tcase_add_test(tcase_core, sub_7);
  tcase_add_test(tcase_core, sub_8);
  tcase_add_test(tcase_core, sub_9);
  tcase_add_test(tcase_core, sub_10);
  tcase_add_test(tcase_core, sub_11);
  tcase_add_test(tcase_core, sub_12);
  tcase_add_test(tcase_core, sub_13);
  tcase_add_test(tcase_core, sub_14);
  tcase_add_test(tcase_core, sub_15);

  // сложение
  tcase_add_test(tcase_core, add_0);
  tcase_add_test(tcase_core, add_1);
  tcase_add_test(tcase_core, add_2);
  tcase_add_test(tcase_core, add_3);
  tcase_add_test(tcase_core, add_4);
  tcase_add_test(tcase_core, add_5);
  tcase_add_test(tcase_core, add_6);
  tcase_add_test(tcase_core, add_7);
  tcase_add_test(tcase_core, add_8);
  tcase_add_test(tcase_core, add_9);
  tcase_add_test(tcase_core, add_10);
  tcase_add_test(tcase_core, add_11);
  tcase_add_test(tcase_core, add_12);
  tcase_add_test(tcase_core, add_13);
  tcase_add_test(tcase_core, add_14);
  tcase_add_test(tcase_core, add_15);

  //умножение
  tcase_add_test(tcase_core, mul_0);
  tcase_add_test(tcase_core, mul_1);
  tcase_add_test(tcase_core, mul_2);
  tcase_add_test(tcase_core, mul_3);
  tcase_add_test(tcase_core, mul_4);
  tcase_add_test(tcase_core, mul_5);
  tcase_add_test(tcase_core, mul_6);
  tcase_add_test(tcase_core, mul_7);
  tcase_add_test(tcase_core, mul_8);
  tcase_add_test(tcase_core, mul_9);
  tcase_add_test(tcase_core, mul_10);
  tcase_add_test(tcase_core, mul_11);
  tcase_add_test(tcase_core, mul_12);
  tcase_add_test(tcase_core, mul_13);
  tcase_add_test(tcase_core, mul_14);
  tcase_add_test(tcase_core, mul_15);

  // деление
  tcase_add_test(tcase_core, div_0);
  tcase_add_test(tcase_core, div_1);
  tcase_add_test(tcase_core, div_2);
  tcase_add_test(tcase_core, div_3);
  tcase_add_test(tcase_core, div_4);
  tcase_add_test(tcase_core, div_5);
  tcase_add_test(tcase_core, div_6);
  tcase_add_test(tcase_core, div_7);
  tcase_add_test(tcase_core, div_8);
  tcase_add_test(tcase_core, div_9);
  tcase_add_test(tcase_core, div_10);
  tcase_add_test(tcase_core, div_11);
  tcase_add_test(tcase_core, div_12);
  tcase_add_test(tcase_core, div_13);
  tcase_add_test(tcase_core, div_14);
  tcase_add_test(tcase_core, div_15);

  // остаток от деления
  tcase_add_test(tcase_core, mod_0);
  tcase_add_test(tcase_core, mod_1);
  tcase_add_test(tcase_core, mod_2);
  tcase_add_test(tcase_core, mod_3);
  tcase_add_test(tcase_core, mod_4);
  tcase_add_test(tcase_core, mod_5);
  tcase_add_test(tcase_core, mod_6);
  tcase_add_test(tcase_core, mod_7);
  tcase_add_test(tcase_core, mod_8);
  tcase_add_test(tcase_core, mod_9);
  tcase_add_test(tcase_core, mod_10);
  tcase_add_test(tcase_core, mod_11);

  // Отбрасываем знаки после запятой
  tcase_add_test(tcase_core, truncate_0);
  tcase_add_test(tcase_core, truncate_1);
  tcase_add_test(tcase_core, truncate_2);
  tcase_add_test(tcase_core, truncate_3);
  tcase_add_test(tcase_core, truncate_4);
  tcase_add_test(tcase_core, truncate_5);
  tcase_add_test(tcase_core, truncate_6);
  tcase_add_test(tcase_core, truncate_6);
  tcase_add_test(tcase_core, truncate_7);
  tcase_add_test(tcase_core, truncate_8);
  tcase_add_test(tcase_core, truncate_9);
  tcase_add_test(tcase_core, truncate_10);

  // Возвращает результат умножения указанного Decimal на -1
  tcase_add_test(tcase_core, negate_0);
  tcase_add_test(tcase_core, negate_1);
  tcase_add_test(tcase_core, negate_2);
  tcase_add_test(tcase_core, negate_3);
  tcase_add_test(tcase_core, negate_4);
  tcase_add_test(tcase_core, negate_5);
  tcase_add_test(tcase_core, negate_6);
  tcase_add_test(tcase_core, negate_7);
  tcase_add_test(tcase_core, negate_8);
  tcase_add_test(tcase_core, negate_9);
  tcase_add_test(tcase_core, negate_10);

  // округляет указанное Decimal число до ближайшего целого числа в сторону
  // отрицательной бесконечности
  tcase_add_test(tcase_core, floor_0);
  tcase_add_test(tcase_core, floor_1);
  tcase_add_test(tcase_core, floor_2);
  tcase_add_test(tcase_core, floor_3);
  tcase_add_test(tcase_core, floor_4);
  tcase_add_test(tcase_core, floor_5);
  tcase_add_test(tcase_core, floor_6);
  tcase_add_test(tcase_core, floor_7);
  tcase_add_test(tcase_core, floor_8);
  tcase_add_test(tcase_core, floor_9);
  tcase_add_test(tcase_core, floor_10);

  // Функция округляет Decimal до ближайшего целого числа
  tcase_add_test(tcase_core, round_0);
  tcase_add_test(tcase_core, round_1);
  tcase_add_test(tcase_core, round_2);
  tcase_add_test(tcase_core, round_3);
  tcase_add_test(tcase_core, round_4);
  tcase_add_test(tcase_core, round_5);
  tcase_add_test(tcase_core, round_6);
  tcase_add_test(tcase_core, round_7);
  tcase_add_test(tcase_core, round_8);
  tcase_add_test(tcase_core, round_9);
  tcase_add_test(tcase_core, round_10);

  // Из s21_decimal во float
  tcase_add_test(tcase_core, from_decimal_to_float_0);
  tcase_add_test(tcase_core, from_decimal_to_float_1);
  tcase_add_test(tcase_core, from_decimal_to_float_2);
  tcase_add_test(tcase_core, from_decimal_to_float_3);
  tcase_add_test(tcase_core, from_decimal_to_float_4);
  tcase_add_test(tcase_core, from_decimal_to_float_5);

  // Из float во s21_decimal
  tcase_add_test(tcase_core, from_float_to_decimal_0);
  tcase_add_test(tcase_core, from_float_to_decimal_1);
  tcase_add_test(tcase_core, from_float_to_decimal_2);
  tcase_add_test(tcase_core, from_float_to_decimal_3);
  tcase_add_test(tcase_core, from_float_to_decimal_4);
  tcase_add_test(tcase_core, from_float_to_decimal_5);

  // Из s21_decimal в int
  tcase_add_test(tcase_core, from_decimal_to_int_0);
  tcase_add_test(tcase_core, from_decimal_to_int_1);
  tcase_add_test(tcase_core, from_decimal_to_int_2);
  tcase_add_test(tcase_core, from_decimal_to_int_3);
  tcase_add_test(tcase_core, from_decimal_to_int_4);
  tcase_add_test(tcase_core, from_decimal_to_int_5);

  // Из int в s21_decimal
  tcase_add_test(tcase_core, from_int_to_decimal_0);
  tcase_add_test(tcase_core, from_int_to_decimal_1);
  tcase_add_test(tcase_core, from_int_to_decimal_2);
  tcase_add_test(tcase_core, from_int_to_decimal_3);
  tcase_add_test(tcase_core, from_int_to_decimal_4);
  tcase_add_test(tcase_core, from_int_to_decimal_5);

  suite_add_tcase(suite, tcase_core);
  return suite;
}

int main(void) {
  Suite *suite = s21_decimal_suite();
  SRunner *suite_runner = srunner_create(suite);
  srunner_run_all(suite_runner, CK_VERBOSE);
  int failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);
  return (failed_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}