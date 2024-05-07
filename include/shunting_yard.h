#include <deque>
#include <vector>

#include "macros.h"
#include "token.h"


void shunting_yard(vector<token_t> &tokens_infix, deque<token_t> &tokens_output);
