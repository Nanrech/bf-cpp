#include <iostream>
#include <fstream>
#include <vector>
#include "interpreter.h"

using namespace std;


int main(int argc, char* argv[]) {
  // Don't look here, it's ugly

  if (argc != 2) {
    cout << "Usage: '.\\" << argv[0] << " <program.bf>'. Missing bf file." << endl;
    return 1;
  }

  ifstream in_file(argv[1]);
  if (in_file.fail()) {
    cout << "Error reading " << argv[1] << endl;
    return 1;
  }

  BfInterpreter Interpreter;
  vector<BfToken> token_list;
  vector<unsigned int> token_stack;
  char c;


  while (in_file.get(c)) {
    // Implementation sorta inspired by tsoding's https://github.com/tsoding/bfjit
    switch (c) {
      case BFT_MOVR:
      case BFT_MOVL:
      case BFT_INC:
      case BFT_DEC:
      case BFT_OUT:
      case BFT_INP: {
        unsigned int count = 1;
        char next_c = '\0';
        in_file.get(next_c);

        while (c == next_c || !Interpreter.is_opcode(next_c)) {
          if (!Interpreter.is_opcode(next_c)) {
              if (!in_file.get(next_c)) {
                break;
              }
              continue;
          }
          count++;
          in_file.get(next_c);
        }

        in_file.putback(next_c);

        BfToken token = {
          .amount = count,
          .type = c
        };

        token_list.push_back(token);
        c = next_c;
        break;
      }
      
      case BFT_BRO: {
        BfToken token = {
          .amount = token_list.size(),
          .type = BFT_BRO
        };
        token_stack.push_back(token.amount);
        token_list.push_back(token);
        break;
      }
      
      case BFT_BRC: {
        if (token_stack.empty()) {
          // uuuuuuuunnnnnnnnnnnnnngggggggggggghhhhhhhhhhhhhhhhhhhhhhhhhhhh
          // https://youtu.be/W-ZuKp8P7gA?t=2934 
          throw runtime_error("\n");
        }
        unsigned int previous = token_stack.back();
        token_stack.pop_back();
        
        BfToken token = {
          .amount = previous,
          .type = c
        };

        token_list[previous].amount = token_list.size();
        token_list.push_back(token);
        break;
      }

      default:
        break;
    }
  }

  in_file.close();
  Interpreter.run(token_list);
  
  return 0;
}
