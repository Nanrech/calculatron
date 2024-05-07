#include "tokenize.h"      // <vector>, <string>, <cmath>
#include "shunting_yard.h" //
#include "evaluate.h"      // <cmath>, <stack>

using namespace std;


inline void print_tokenized(vector<token_t>& v) {
  cout << "Tokens: ";
  for (auto i : v) {
    print_token(i);
    cout << "";
  }
  cout << endl;
}

inline void print_RPN(deque<token_t>& d) {
  cout << "RPN:    ";
  for (auto i : d) {
    print_token(i);
    cout << "";
  }
  cout << endl;
}

int main(int argc, char** argv) {
  // uuggghhhhhhh
  if (argc <= 1) {
    cout << "Usage: " << argv[0] << " \"Your math expression here\"" << endl;
    cout << "Supported operations: + - * / % ^ ()" << endl;
    return 0;
  }
  // guuuuuhhhhhh
  if (strlen(argv[1]) == 1) {
    EXIT_ERROR("Put your operation in quotes");
  }

  // argv[1] should be a non null-terminated string containing our input
  cout << "Input:  \"" << argv[1] << "\"" << endl;

  // We get tokens from that string
  vector<token_t> tokens_infix;
  tokenize(argv[1], tokens_infix);
  print_tokenized(tokens_infix);

  // Now that we have the tokens we convert them to RPN (Reverse Polish Notation)
  deque<token_t> tokens_RPN;
  shunting_yard(tokens_infix, tokens_RPN);
  print_RPN(tokens_RPN);

  // And once that's done we evaluate them and quit
  double result = evaluate(tokens_RPN);
  cout << "Result: " << result << endl;
  return 0;
}
