#pragma once

#define CHAR_TO_DIGIT(c) (c - '0')
#define IS_DIGIT(c) (c >= '0' && c <= '9')
#define IS_DECIMAL_POINT(c) (c == '.')
#define IS_OPERATOR(c) (c == '+' || c == '-' || c == '*' || c == '/' || '%' || c == '^' /* || c == '!' */ || c == '(' || c == ')')
#define IS_UNARY(c) (c == '+' || c == '-' /* || c == '!' */)
#define EXIT_ERROR(s) cout << "ERROR: " << s << endl; exit(-1)
#define GET_FIXED_FRACTIONAL(p, l) (l != 0 ? p / pow(10, l) : 0) // Where p is fractional_portion and l is fractional_length
#define IS_TEXT(c) (c >= 'A' && c <= 'z')
