#include "opcodes.hpp"


bool is_opcode(const char c) {
  char op_arr[] = {
    MOVE_RIGHT,
    MOVE_LEFT,
    INCREMENT,
    DECREMENT,
    OUTPUT,
    INPUT,
    BRACKET_OPEN,
    BRACKET_CLOSE
  };
  
  for (int i = 0; i <= 8; i++) {
    if (op_arr[i] == c)
      return true;
  }

  return false;
}

