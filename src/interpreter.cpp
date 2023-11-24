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
  
  if ((unsigned)pointer == tape.size()) {
    tape.push_back(0);
  }
}

void BfInterpreter::move_left() {
  // We don't allow negative index
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

void BfInterpreter::bracket_open(const size_t i) {
  stack.push(i);
}

void BfInterpreter::bracket_close(size_t &i) {
  if (stack.empty()) {
    throw std::runtime_error("Unmatched closing bracket");
  }

  if (tape[pointer] == 0) {
    stack.pop();
    return;
  }

  if (stack.top() == 0) {
    i = 0;
  }
  else {
    i = stack.top() - 1;
  }

  stack.pop();
}

bool BfInterpreter::is_opcode(const char c) {
  for (char i : {'>', '<', '+', '-', '.', '[', ']'}) {
    if (i == c) {
      return true;
    }
  }
  return false;
}

void BfInterpreter::run(const std::vector<char> &tokens) {
  size_t i = 0;

  while (i <= tokens.size()) {
    switch(tokens[i]) {
      case '>':
        move_right();
        break;

      case '<':
        move_left();
        break;

      case '+':
        increment();
        break;

      case '-':
        decrement();
        break;

      case '.':
        output();
        break;

      case ',':
        input();
        break;

      case '[':
        bracket_open(i);
        break;

      case ']':
        bracket_close(i);
        break;

      default:
        break;
    }
    i++;
  }
}
