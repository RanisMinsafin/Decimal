# Custom Decimal Library (decimal.h)

This project involves the development of a custom `decimal.h` library, implementing various functions for decimal arithmetic. The library is written in C language, adheres to the C11 standard, and follows best practices in coding style and documentation.

## Overview of Implemented `decimal.h` Functions

The `decimal.h` library provides functions for decimal arithmetic, supporting high-precision calculations. The following functions are implemented:

### Arithmetic Operations

1. `s21_add` - Addition of two decimal numbers.
2. `s21_sub` - Subtraction of one decimal number from another.
3. `s21_mul` - Multiplication of two decimal numbers.
4. `s21_div` - Division of one decimal number by another.
5. `s21_mod` - Modulus operation of two decimal numbers.

### Comparison Functions

6. `s21_is_less` - Check if one decimal number is less than another.
7. `s21_is_less_or_equal` - Check if one decimal number is less than or equal to another.
8. `s21_is_greater` - Check if one decimal number is greater than another.
9. `s21_is_greater_or_equal` - Check if one decimal number is greater than or equal to another.
10. `s21_is_equal` - Check if two decimal numbers are equal.
11. `s21_is_not_equal` - Check if two decimal numbers are not equal.

### Conversion Functions

12. `s21_from_int_to_decimal` - Convert an integer to a decimal number.
13. `s21_from_decimal_to_int` - Convert a decimal number to an integer (truncating the fractional part).
14. `s21_from_decimal_to_float` - Convert a decimal number to a floating-point number (float).
15. `s21_from_float_to_decimal` - Convert a floating-point number (float) to a decimal number.

### Other Utility Functions

16. `s21_floor` - Round a decimal number towards negative infinity.
17. `s21_round` - Perform mathematical rounding of a decimal number.
18. `s21_truncate` - Truncate the decimal part of a decimal number.
19. `s21_negate` - Change the sign of a decimal number to its opposite.
20. `s21_bank_round` - Perform banking rounding of a decimal number.

## Implementation Details

- The library adheres to the C11 standard and does not use outdated or legacy language constructions or library functions.
- Coding style follows the Google style guidelines to ensure code consistency and readability.
- Functions are prefixed with `s21_` for clarity and to avoid naming conflicts.
- Unit tests, using the Check library, ensure the correctness of each implemented function.
- A comprehensive Makefile is provided for building the library and running tests, including targets like `all`, `clean`, `test`, and `gcov_report`.
- Decimal numbers are represented internally using a binary format with the `bits` array, as specified in the provided example.
- The library supports a wide range of decimal numbers, from -79,228,162,514,264,337,593,543,950,335 to +79,228,162,514,264,337,593,543,950,335.

## Getting Started

To build the library and run tests, use the following commands:

```bash
make all  # Build the library and tests
make test  # Run unit tests
make gcov_report  # Generate a coverage report
```

This will compile the library, execute unit tests, and create a coverage report for analysis.

## Usage

Include the `s21_decimal.h` header file in your C code to access the custom decimal functions:

```c
#include "s21_decimal.h"

int main() {
    // Initialize decimal numbers
    s21_decimal num1, num2, result;
    s21_init_decimal(&num1);
    s21_init_decimal(&num2);

    // Set values for num1 and num2 (example)
    s21_from_int_to_decimal(10, &num1);
    s21_from_int_to_decimal(5, &num2);

    // Perform arithmetic operations
    s21_add(num1, num2, &result);
    s21_sub(num1, num2, &result);
    s21_mul(num1, num2, &result);
    s21_div(num1, num2, &result);

    // Convert to string and print (example)
    char result_str[50];
    s21_decimal_to_string(result, result_str, sizeof(result_str));
    printf("Result: %s\n", result_str);

    return 0;
}
```

## Conclusion

The `decimal.h` library provides a reliable solution for high-precision decimal arithmetic in C projects. It ensures accurate calculations and follows best practices for code quality and maintainability.

For detailed information on each function and its usage, consult the project's source code.