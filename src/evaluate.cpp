#include "evaluate.h"


double execute_operation(double a, double b, char op) {
  switch (op) {
    case '^':
      return pow(a, b);

    case '*':
      return b * a;

    case '/':
      if (b == 0) {
        EXIT_ERROR("DIVISION BY ZERO");
      }
      return a / b;

    case '+':
      return a + b;

    case '-':
      return a - b;

    default:
      return 0;
  }
}

double evaluate(deque<token_t> &tokens_RPN) {
  stack<double> eval_st;

  for (token_t current_token : tokens_RPN) {
    // Literals get pushed into the evaluation stack
    if (current_token.is_literal) {
      eval_st.push(current_token.value);
    }
    else {
      // We will have min. 1 & max. 2 arguments per operator
      double args[2] = {0.0};

      for (int i = 0; i < current_token.argument_num; i++) {
        if (eval_st.empty()) {
          // If we run out of potential arguments the program will explode and die on the spot
          // If this error message is good enough for CASIO, it's good enough for me
          EXIT_ERROR("Syntax error. Weird operator order.");
        }
        else {
          // args[0] is the second argument, args[1] is the first one
          args[i] = eval_st.top();
          eval_st.pop();
        }
      }
      // Now that we have the arguments and the operator
      // (a^b^c = (a^b)^c; not a^(b^c), because that's what my calculator says)
      double result = 0.0;

      if (current_token.argument_num == 1) {
        // 0 + args[0], 0 - args[0], simple solution
        result = execute_operation(0, args[0], current_token.op);
      }
      else {
        // The other function does the rest of the work
        result = execute_operation(args[1], args[0], current_token.op);
      }
      // Push the result of the latest operation into the evaluation stack
      // so it can be used as an argument in the next iteration
      eval_st.push(result);
    }
  }

  // There should be only one element left at the top of the stack: the result of the operation
  return eval_st.top();
}
