#include <cmath>    // pow
#include <string.h> // strlen
#include <vector>

#include "macros.h"
#include "token.h"

using namespace std;


int get_precedence(char c);
void tokenize(char* operation, vector<token_t> &tokens_infix);
