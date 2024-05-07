#include <iostream>

#pragma once
using namespace std;


typedef struct token_t {
  union {
    double value;
    char op;
  };
  bool is_literal;
  int precedence;
  int argument_num; // Either 1 or 2. 0 for literals
} token_t;

void print_token(token_t& token);
