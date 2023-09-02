#ifndef S21_DECIMAL
#define S21_DECINAL

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

enum convertation_status { CONVERTATION_OK, CONVERTATION_ERROR };

enum arithmetics_status { OK, NUM_TOO_BIG, NUM_TOO_SMALL, ZERO_DIVISION };

enum operation_num { IS_LESS, IS_EQUAL };

enum calculation_status { CALCULATION_OK, CALCULATION_ERROR };

enum number_sign { PLUS_SIGN, MINUS_SIGN };

enum bits_pos { LOW, MID, HIGH, SCALE };

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned int bits[7];
} s21_big_decimal;

int last_bits(int pow, int sign);  // Для тестов...

// ARITHMETICS
int s21_add(s21_decimal d1, s21_decimal d2, s21_decimal *result);  // Сложение
int s21_sub(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result);  // Вычитание
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// COMPARISON
int s21_is_less(s21_decimal d1, s21_decimal d2);  // Меньше
int s21_is_less_or_equal(s21_decimal d1, s21_decimal d2);  // Меньше или равно
int s21_is_greater(s21_decimal d1, s21_decimal d2);  // Больше
int s21_is_greater_or_equal(s21_decimal d1,
                            s21_decimal d2);  // Больше или равно
int s21_is_equal(s21_decimal d1, s21_decimal d2);      // Равны ли
int s21_is_not_equal(s21_decimal d1, s21_decimal d2);  // Не равны ли

// CONVERSION
int s21_from_int_to_decimal(int src, s21_decimal *dst);  // из int в s21_decimal
int s21_from_decimal_to_int(s21_decimal src, int *dst);  // из s21_decimal в int
int s21_from_decimal_to_float(s21_decimal src,
                              float *dst);  // из s21_decimal во float
int s21_from_float_to_decimal(float src,
                              s21_decimal *dst);  // Из float в s21_decimal

// OTHER
int s21_floor(s21_decimal value,
              s21_decimal *result);  // Округление в сторону минус бесконечности
int s21_round(s21_decimal value,
              s21_decimal *result);  // Математическое округление
int s21_truncate(s21_decimal value,
                 s21_decimal *result);  // Отсечение дробной части s21_decimal
int s21_negate(
    s21_decimal value,
    s21_decimal *result);  // Меняет знак s21_decimal на противоположный
int s21_bank_round(s21_decimal value,
                   s21_decimal *result);  // Банковское округление

// HELP FUNCS
void s21_float_to_decimal(
    float src, s21_decimal *dst);  // Вспомогательная функция для
                                   // s21_from_float_to_decimal (конвертация)
int s21_get_float_scale(
    float src);  // Вспомогательная функция для s21_from_float_to_decimal
                 // (Вытаскиваем степень числа float)
int s21_last_digit(s21_decimal value);  // Для ф-ции round (узнаем последнюю
                                        // цифру после запятой)
int s21_last_bank_digit(s21_decimal value);  // Для ф-ции bank_round (узнаем
                                             // последнюю цифру после запятой)
void standart_round(s21_decimal *obj);  // Стандратное округление
void s21_init_decimal(s21_decimal *);  // Инициализируем Decimal нулями
int s21_get_sign(s21_decimal num);  // Узнаем знак Decimal'a
void s21_set_sign(s21_decimal *num, int sign);  // Устанавливаем знак Decimal'y
int s21_get_bit(s21_decimal num,
                int index);  // Узнаем бит num'a в позиции index
void s21_set_bit(
    s21_decimal *num, int index,
    int bit);  // Устанавливаем bit (1 or 0) в num'e в позиции index
int s21_get_scale(s21_decimal num);  // Узнаем степень в Decimal'e
void s21_set_scale(s21_decimal *num,
                   int scale);  // Устанавливаем степень в Decimal'e

void s21_div_by_10(
    s21_decimal *num);  // Уменьшаем разрядность числа Decimal (делим на 10)
int is_dec_zero(s21_decimal d);  // Равен ли s21_decimal нулю

// Для s21_big_decimal
void s21_init_big_decimal(s21_big_decimal *obj);
void s21_from_decimal_to_big(s21_decimal d1, s21_big_decimal *b1,
                             s21_decimal d2, s21_big_decimal *b2);
void operate(s21_decimal d1, s21_decimal d2, int action,
             s21_big_decimal *result);
void s21_set_big_bit(s21_big_decimal *num, int index, int bit);
void s21_set_big_sign(s21_big_decimal *num, int sign);
void s21_set_big_scale(s21_big_decimal *num, int scale);
int s21_get_big_scale(s21_big_decimal num);
void s21_div_big_by_10(s21_big_decimal *num);
void equalize_scales(s21_big_decimal *b1, s21_big_decimal *b2, int scale1,
                     int scale2);
void higher_scale(s21_big_decimal *d, int scale);
int s21_get_big_bit(s21_big_decimal num, int index);
int s21_get_big_sign(s21_big_decimal num);
int s21_from_big_to_decimal(s21_big_decimal big, s21_decimal *norm);
void invert_big_dec(s21_big_decimal *obj);
int is_big_dec_zero(s21_big_decimal obj);
void output(s21_decimal num);
void output_reverse(s21_decimal num);
void output_big(s21_big_decimal num);
void output_scale(s21_decimal num);
void s21_is_less_big(s21_big_decimal b1, s21_big_decimal b2,
                     s21_big_decimal *res);
void s21_is_equal_big(s21_big_decimal b1, s21_big_decimal b2,
                      s21_big_decimal *res);

int s21_is_greater_or_equal_big(s21_big_decimal d1, s21_big_decimal d2);
s21_big_decimal transformDecimalToBig(s21_decimal num);
s21_decimal transformBigDecimalToNormal(s21_big_decimal num);
int checkLastBitsBigDecimal(s21_big_decimal num);
int checkWorkBitsBigDecimal(s21_big_decimal num);
void s21_add_big_dec(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *result);
void s21_sub_big_dec(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *result);
int s21_mul_big_dec(s21_big_decimal value_1, s21_big_decimal value_2,
                    s21_big_decimal *result);
void s21_div_big_dec(s21_big_decimal *value_1, s21_big_decimal value_2,
                     s21_big_decimal *mod);

int sum_bits_big_dec(s21_big_decimal value);
int checkOverflowBigDecimal(s21_big_decimal value);
int shiftBitsLeftBigDec(s21_big_decimal *value, int index);
void s21_mul_by_10_big(s21_big_decimal *num);
int s21_normalize_big(s21_big_decimal *value_1, s21_big_decimal *value_2);
void output2(s21_decimal num);
void outputBigDec2(s21_big_decimal num);
void outputBigDec(s21_big_decimal num);

#endif  // S21_DECIMAL