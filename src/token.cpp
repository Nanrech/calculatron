#include "token.h"


void print_token(token_t& token) {
  if (token.is_literal) {
    cout << token.value;
  }
  else {
    cout << token.op;
  }
}
