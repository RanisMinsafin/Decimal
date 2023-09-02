#include "s21_decimal.h"

// Принтим биты
void output(s21_decimal num) {
  printf("BIT[0]:");
  for (int i = 31; i >= 0; i--) {
    int tmp = s21_get_bit(num, i);
    printf("%d", tmp);
  }
  printf("\nBIT[1]:");
  for (int i = 63; i >= 32; i--) {
    int tmp = s21_get_bit(num, i);
    printf("%d", tmp);
  }
  printf("\nBIT[2]:");
  for (int i = 95; i >= 64; i--) {
    int tmp = s21_get_bit(num, i);
    printf("%d", tmp);
  }
  printf("\nBIT[3]:");
  for (int i = 127; i >= 96; i--) {
    int tmp = s21_get_bit(num, i);
    printf("%d", tmp);
  }
  printf("\n%u %u %u\n", num.bits[0], num.bits[1], num.bits[2]);
}

// Принтим биты (наоборот)
void output_reverse(s21_decimal num) {
  printf("BIT[0]:");
  for (int i = 0; i < 32; i++) {
    int tmp = s21_get_bit(num, i);
    printf("%d", tmp);
  }
  printf("\nBIT[1]:");
  for (int i = 32; i < 64; i++) {
    int tmp = s21_get_bit(num, i);
    printf("%d", tmp);
  }
  printf("\nBIT[2]:");
  for (int i = 64; i < 96; i++) {
    int tmp = s21_get_bit(num, i);
    printf("%d", tmp);
  }
  printf("\nBIT[3]:");
  for (int i = 96; i < 128; i++) {
    int tmp = s21_get_bit(num, i);
    printf("%d", tmp);
  }
  printf("\n%u %u %u\n", num.bits[0], num.bits[1], num.bits[2]);
}

// Принтим биты
void output_big(s21_big_decimal num) {
  printf("BIT[0]:");
  for (int i = 31; i >= 0; i--) {
    int tmp = s21_get_big_bit(num, i);
    printf("%d", tmp);
  }
  printf("\nBIT[1]:");
  for (int i = 63; i >= 32; i--) {
    int tmp = s21_get_big_bit(num, i);
    printf("%d", tmp);
  }
  printf("\nBIT[2]:");
  for (int i = 95; i >= 64; i--) {
    int tmp = s21_get_big_bit(num, i);
    printf("%d", tmp);
  }
  printf("\nBIT[3]:");
  for (int i = 127; i >= 96; i--) {
    int tmp = s21_get_big_bit(num, i);
    printf("%d", tmp);
  }
  printf("\nBIT[4]:");
  for (int i = 159; i >= 128; i--) {
    int tmp = s21_get_big_bit(num, i);
    printf("%d", tmp);
  }
  printf("\nBIT[5]:");
  for (int i = 191; i >= 160; i--) {
    int tmp = s21_get_big_bit(num, i);
    printf("%d", tmp);
  }
  printf("\nBIT[6]:");
  for (int i = 223; i >= 192; i--) {
    int tmp = s21_get_big_bit(num, i);
    printf("%d", tmp);
  }
  printf("\n%u %u %u\n", num.bits[0], num.bits[1], num.bits[2]);
}

// Принтим степень s21_decimal
void output_scale(s21_decimal num) {
  printf("BIT[3] [16:24]:");
  for (int i = 119; i >= 112; i--) {
    int tmp = s21_get_bit(num, i);
    printf("%d", tmp);
  }
  printf("\nscale = %d", s21_get_scale(num));
}

void output2(s21_decimal num) {
  // if (num.bits[3] != 0) {
  for (int i = 127; i >= 96; i--) {
    int tmp = s21_get_bit(num, i);
    printf("%d", tmp);
    if (i == 96 || i == 64 || i == 32) {
      printf("  ");
    }
  }
  // }
  if (num.bits[2] != 0) {
    for (int i = 95; i >= 64; i--) {
      int tmp = s21_get_bit(num, i);
      printf("%d", tmp);
      if (i == 96 || i == 64 || i == 32) {
        printf("  ");
      }
    }
  }
  if (num.bits[1] != 0 || num.bits[2] != 0) {
    for (int i = 63; i >= 32; i--) {
      int tmp = s21_get_bit(num, i);
      printf("%d", tmp);
      if (i == 96 || i == 64 || i == 32) {
        printf("  ");
      }
    }
  }
  if (num.bits[0] != 0 || num.bits[1] != 0 || num.bits[2] != 0) {
    for (int i = 31; i >= 0; i--) {
      int tmp = s21_get_bit(num, i);
      printf("%d", tmp);
      if (i == 96 || i == 64 || i == 32) {
        printf("  ");
      }
    }
  }
  int scale = s21_get_scale(num);
  int sign = s21_get_sign(num);
  printf("  %u %u %u %u scale:%u sign:%u\n", num.bits[0], num.bits[1],
         num.bits[2], num.bits[3], scale, sign);
}

void outputBigDec2(s21_big_decimal num) {
  for (int i = 223; i >= 0; i--) {
    int tmp = s21_get_big_bit(num, i);
    printf("%d", tmp);
    if (i == 192 || i == 160 || i == 128 || i == 96 || i == 64 || i == 32) {
      printf("  ");
    }
  }
  int scale = s21_get_big_scale(num);
  int sign = s21_get_big_sign(num);
  printf("  %u %u %u %u %u %u %u scale:%u sign:%u\n", num.bits[0], num.bits[1],
         num.bits[2], num.bits[3], num.bits[4], num.bits[5], num.bits[6], scale,
         sign);
}

void outputBigDec(s21_big_decimal num) {
  for (int i = 223; i >= 192; i--) {
    int tmp = s21_get_big_bit(num, i);
    printf("%d", tmp);
    if (i == 192 || i == 160 || i == 128 || i == 96 || i == 64 || i == 32) {
      printf("  ");
    }
  }
  if (num.bits[5] != 0) {
    for (int i = 191; i >= 160; i--) {
      int tmp = s21_get_big_bit(num, i);
      printf("%d", tmp);
      if (i == 160 || i == 128 || i == 96 || i == 64 || i == 32) {
        printf("  ");
      }
    }
  }
  if (num.bits[4] != 0 || num.bits[5] != 0) {
    for (int i = 159; i >= 128; i--) {
      int tmp = s21_get_big_bit(num, i);
      printf("%d", tmp);
      if (i == 160 || i == 128 || i == 96 || i == 64 || i == 32) {
        printf("  ");
      }
    }
  }
  if (num.bits[3] != 0 || num.bits[4] != 0 || num.bits[5] != 0) {
    for (int i = 127; i >= 96; i--) {
      int tmp = s21_get_big_bit(num, i);
      printf("%d", tmp);
      if (i == 96 || i == 64 || i == 32) {
        printf("  ");
      }
    }
  }
  if (num.bits[2] != 0 || num.bits[3] != 0 || num.bits[4] != 0 ||
      num.bits[5] != 0) {
    for (int i = 95; i >= 64; i--) {
      int tmp = s21_get_big_bit(num, i);
      printf("%d", tmp);
      if (i == 96 || i == 64 || i == 32) {
        printf("  ");
      }
    }
  }
  if (num.bits[1] != 0 || num.bits[2] != 0 || num.bits[3] != 0 ||
      num.bits[4] != 0 || num.bits[5] != 0) {
    for (int i = 63; i >= 32; i--) {
      int tmp = s21_get_big_bit(num, i);
      printf("%d", tmp);
      if (i == 96 || i == 64 || i == 32) {
        printf("  ");
      }
    }
  }
  if (num.bits[0] != 0 || num.bits[1] != 0 || num.bits[2] != 0 ||
      num.bits[3] != 0 || num.bits[4] != 0 || num.bits[5] != 0) {
    for (int i = 31; i >= 0; i--) {
      int tmp = s21_get_big_bit(num, i);
      printf("%d", tmp);
      if (i == 96 || i == 64 || i == 32) {
        printf("  ");
      }
    }
  }
  printf("  %u %u %u %u %u %u\n", num.bits[0], num.bits[1], num.bits[2],
         num.bits[3], num.bits[4], num.bits[5]);
}
