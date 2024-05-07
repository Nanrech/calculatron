#include <cmath>
#include <stack> // also includes deque

#include "macros.h" // EXIT_ERROR
#include "token.h"


double execute_operation(double a, double b, char op);
double evaluate(deque<token_t> &tokens_RPN);
