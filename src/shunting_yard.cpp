#include "shunting_yard.h"


void shunting_yard(vector<token_t> &tokens_infix, deque<token_t> &tokens_output) {
  // This is my implementation of the Shunting-Yard algorithm
  // https://en.wikipedia.org/wiki/Shunting_yard_algorithm
  // It's just a silly little console project, don't take this code too seriously
  token_t dummy_token = {
    .value = 0,
    .is_literal = true,
    .precedence = 0,
    .argument_num = 0
  };
  token_t* buffer_token = &dummy_token;
  deque<token_t> operator_st; // Operator stack

  for (token_t current_token : tokens_infix) {
    // If the token is a number: put into output
    if (current_token.is_literal) {
      tokens_output.push_back(current_token);
      buffer_token = &tokens_output.back();
      continue;
    }

    // Opening parenthesis: Push into operator stack
    else if (current_token.op == '(') {
      operator_st.push_front(current_token);
      buffer_token = &operator_st.front();
      continue;
    }

    // Closing parenthesis:
    else if (current_token.op == ')') {
      // Flush operator stack until we get to the first opening bracket
      while (!operator_st.empty() && operator_st.front().op != '(') {
        tokens_output.push_back(operator_st.front());
        operator_st.pop_front();
      }
      // Now we pop the top, which should be the opening parenthesis we found
      // No error checking here bc parenthesis mismatch is already checked by the tokenizer
      operator_st.pop_front();
      buffer_token = &current_token;
    }

    // If the token is any other operator (we have already filtered everything else out):
    else {
      // Unary operators need to have their precedence and number of arguments modified
      if (IS_UNARY(current_token.op)) {
        if ((!buffer_token->is_literal && buffer_token->op != ')') || buffer_token->value == 0) {
          current_token.precedence = 5;
          current_token.argument_num = 1;
        }
      }
      // Everyone else
      while (!operator_st.empty() && operator_st.front().op != '(') {
        // While there is an operator with greater precedence on top of the stack
        if (operator_st.front().precedence >= current_token.precedence) {
          // Keep popping out of the stack and into the output until that is no longer the case
          tokens_output.push_back(operator_st.front());
          operator_st.pop_front();
          continue;
        }
        // When that is no longer the case, break out and...
        else {
          break;
        }
      }
      // ...push current operator into the operator stack
      operator_st.push_front(current_token);
      buffer_token = &operator_st.front();
    }
  }

  // When that's all done, flush all remaining tokens in the operator stack into output stack
  while (!operator_st.empty()) {
    tokens_output.push_back(operator_st.front());
    operator_st.pop_front();
  }
}
