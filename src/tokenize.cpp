#include "tokenize.h"


int get_precedence(char c) {
  switch (c) {
    case '^':
      return 3;

    case '*':
    case '/':
    case '%':
      return 2;

    case '+':
    case '-':
      return 1;
    
    case '(':
    case ')':
      return 0;

    default:
      return -1;
  }
}

void tokenize(char* operation, vector<token_t> &tokens_infix) {
  // It should be noted that negative numbers are handled in the next step of the program
  // '-3 + 2' --> [-] [3] [+] [2]
  const int input_len = strlen(operation);
  int parenthesis_check = 0;
  int tokens_total = 0;
  bool is_float = false;

  // Input is NOT null terminated
  for (int i = 0; i < input_len; i++) {
    // If we find a digit
    if (IS_DIGIT(operation[i])) {
      // We start getting the bit before the decimal dot (the '1' in '1.5')
      double integral_portion = CHAR_TO_DIGIT(operation[i]);
      // And keep track of the possible fractional portion of the number
      double fractional_portion = 0;
      int fractional_length = 0;
      i++; // next token

      // Start consuming tokens until
      while (i <= input_len) {
        // We find a number:
        if (IS_DIGIT(operation[i])) {
          // We add to the number like usual
          if (!is_float) {
            integral_portion = integral_portion * 10 + CHAR_TO_DIGIT(operation[i]);
          }
          // We add to the fractional part and keep track of how long it is
          else {
            fractional_portion = fractional_portion * 10 + CHAR_TO_DIGIT(operation[i]);
            fractional_length++;
          }
          i++; // next token
        }
        // We find the dot that separates the fractional from the integer
        else if (IS_DECIMAL_POINT(operation[i])) {
          // If there was already another . in the number to parse this will kill the program
          if (is_float) {
            cout << "At char. " << i << ": " << integral_portion << ". -> ..." << endl;
            EXIT_ERROR("Numbers cannot have two decimal signs in them. Check your input.");
          }
          // We are dealing with a float so we set the is_float flag to true and move to the next thing
          is_float = true;
          i++;
        }
        // We find something else
        else {
          i--; // put back
          // Create new token with the info we have so far and continue
          tokens_infix.push_back(
            token_t{
              .value = integral_portion + GET_FIXED_FRACTIONAL(fractional_portion, fractional_length),
              .is_literal = true,
              .precedence = 0,
              .argument_num = 0
            }
          );
          tokens_total++;
          break;
        }
      }
    }

    else if (IS_OPERATOR(operation[i])) {
      // Default arguments is 2
      int arguments = 2;

      // Parenthesis checks...
      if (operation[i] == '(') {
        if (parenthesis_check < 0) {
          EXIT_ERROR("Out of order parenthesis.");
        }
        parenthesis_check++;
        arguments = 0;
      }
      else if (operation[i] == ')') {
        parenthesis_check--;
        arguments = 0;
      }
      else if (get_precedence(operation[i]) == -1) {
        // Oops. This character shouldn't be counted. Next one!
        continue;
      }

      // We take the operator and shove it in. Functions have not been implemented
      tokens_infix.push_back(
            token_t{
              .op = operation[i],
              .is_literal = false,
              .precedence = get_precedence(operation[i]),
              .argument_num = arguments
            }
          );
      tokens_total++;
    }
  }
  if (tokens_total == 0) {
    EXIT_ERROR("Syntax error. No tokens detected.");
  }
  if (parenthesis_check != 0) {
    EXIT_ERROR("Unmatched parenthesis.");
  }
}
