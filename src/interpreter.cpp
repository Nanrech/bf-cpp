#include "interpreter.h"


void BfInterpreter::view_tape() {
  std::cout << "Tape size: " << tape.size() << " - ";
  std::cout << "Pointer: " << pointer << std::endl;

  for (int i : tape) {
    std::cout << i << " ";
  }
  
  std::cout << std::endl;
}

void BfInterpreter::move_right() {
  pointer++;
  // Infinite tape
  if (pointer == tape.size()) {
    tape.push_back(0);
  }
}

void BfInterpreter::move_left() {
  pointer--;
}

void BfInterpreter::increment() {
  tape[pointer]++;
}

void BfInterpreter::decrement() {
  tape[pointer]--;
}

void BfInterpreter::output() {
  std::cout << tape[pointer];
}

void BfInterpreter::input() {
  char c;
  std::cin.get(c);
  tape[pointer] = (unsigned char)c;
}

void BfInterpreter::bracket_open(size_t &i, const BfToken token) {
  // "Jump past the matching ] if the cell at the pointer is 0"
  // https://esolangs.org/wiki/brainfuck
  if (tape[pointer] == 0) {
    i = token.amount;
  }
  else {
    i++;
  }
  return;
}

void BfInterpreter::bracket_close(size_t &i, const BfToken token) {
  // "Jump back to the matching [ if the cell at the pointer is nonzero"
  // https://esolangs.org/wiki/brainfuck
  if (tape[pointer] != 0) {
    i = token.amount;
  }
  else {
    i++;
  }
  return;
}

bool BfInterpreter::is_opcode(const char c) {
  for (char i : {'>', '<', '+', '-', '.', '[', ']'}) {
    if (i == c) {
      return true;
    }
  }
  return false;
}

void BfInterpreter::run(const std::vector<BfToken> &tokens) {
  // Lasciate ogne speranza, voi ch'intrate
  for (size_t i = 0; i <= tokens.size() - 1;) {
    // i is the program pointer. Every token contains either the amount of times it must be executed
    // (See the first case for an example on how that works)
    // or a "pointer" that tells the program what index to jump to when executing a '[' or a ']'
    switch (tokens[i].type) {
      // >
      case BFT_MOVR: {
        for (int count = tokens[i].amount; count >= 1; count--) {
          BfInterpreter::move_right();
        }
        i++;
        break;
      }

      // <
      case BFT_MOVL: {
        for (int count = tokens[i].amount; count >= 1; count--) {
          BfInterpreter::move_left();
        }
        i++;
        break;
      }
      
      // +
      case BFT_INC: {
        for (int count = tokens[i].amount; count >= 1; count--) {
          BfInterpreter::increment();
        }
        i++;
        break;
      }

      // -
      case BFT_DEC: {
        for (int count = tokens[i].amount; count >= 1; count--) {
          BfInterpreter::decrement();
        }
        i++;
        break;
      }

      // .
      case BFT_OUT: {
        for (int count = tokens[i].amount; count >= 1; count--) {
          BfInterpreter::output();
        }
        i++;
        break;
      }

      // ,
      case BFT_INP: {
        for (int count = tokens[i].amount; count >= 1; count--) {
          BfInterpreter::input();
        }
        i++;
        break;
      }

      // These are different since we can't assume i++ 
      // (or maybe we can, idk, I was very tired when I wrote this)
      
      // [
      case BFT_BRO:
        BfInterpreter::bracket_open(i, tokens[i]);
        break;
      
      // ]
      case BFT_BRC:
        BfInterpreter::bracket_close(i, tokens[i]);
        break;

      default:
        break;
    }
  }
  return;
}
