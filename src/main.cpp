#include <iostream>
#include <fstream>
#include <stack>
#include "interpreter.h"

using namespace std;


int main(int argc, char* argv[]) {
  // Don't look here, it's ugly
  if (argc != 2) {
    cout << "Usage: " << argv[0] << " <program.bf>\nMissing bf file." << endl;
    return 1;
  }
  // Standard error checking
  ifstream in_file(argv[1]);
  if (in_file.fail()) {
    cout << "Error reading " << argv[1] << endl;
    return 1;
  }

  // ---- Parser happens below this point ----

  BfInterpreter interpreter;
  stack<unsigned int> bracket_stack;  // Keeps track of previous brackets
  char c;                             // char of holding
  unsigned int total_tokens = 0;

  while (!in_file.get(c).eof()) {
    char buffer_character = c;
    unsigned int single_token_amount = 1;

    if (IS_IO_CHAR(c)) {
      interpreter.tokens.push_back(BfToken {.amount = single_token_amount, .type = buffer_character});
      total_tokens++;
    }
    else if (IS_MULTI_OPERATOR_CHAR(c)) {
      while (!in_file.get(c).eof()) {
        if (!IS_VALID_CHAR(c)) {
          // Text, whitespace, whatever. Don't need it. Skip.
          continue;
        }
        else {
          if (c == buffer_character) {
            // Minor optimization. The parser merges consecutive equal tokens into one
            // So ++++++++ would be one {'+', 8} token instead of 8 '+' tokens
            single_token_amount++;
            continue;
          }
          else {
            // Put it back where it came from
            in_file.putback(c);
            // And insert what we must
            interpreter.tokens.push_back(BfToken {.amount = single_token_amount, .type = buffer_character});
            total_tokens++;
            break;
          }
        }
      }
      if (in_file.eof()) {
        interpreter.tokens.push_back(BfToken {.amount = single_token_amount, .type = buffer_character});
        total_tokens++;
      }
    }
    else if (IS_BRACKET_CHAR(c)) {
      if (c == '[') {
        BfToken new_token = {
          .amount = single_token_amount,
          .type = buffer_character
        };
        interpreter.tokens.push_back(new_token);
        bracket_stack.push(total_tokens);
        total_tokens++;
      }
      else {
        if (bracket_stack.empty()) {
          cout << "Invalid syntax (bracket mismatch)" << endl;
          exit(-1);
        }
        BfToken new_token = {
          .amount = bracket_stack.top(),
          .type = c
        };
        interpreter.tokens[bracket_stack.top()].amount = total_tokens;
        interpreter.tokens.push_back(new_token);
        bracket_stack.pop();
        total_tokens++;
      }
    }
  }
  in_file.close();

  // Done!
  interpreter.run();

  return 0;
}
