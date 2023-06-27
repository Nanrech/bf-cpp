#include "interpreter.hpp"


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
  i = 0 > stack.top() - 1 ? 0 : stack.top() - 1;
  stack.pop();
}

void BfInterpreter::run(const std::vector<char> &tokens) {
  size_t i = 0;

  while (i <= tokens.size()) {
    switch(tokens[i]) {
      case MOVE_RIGHT:
        move_right();
        break;

      case MOVE_LEFT:
        move_left();
        break;

      case INCREMENT:
        increment();
        break;

      case DECREMENT:
        decrement();
        break;

      case OUTPUT:
        output();
        break;

      case INPUT:
        input();
        break;

      case BRACKET_OPEN:
        bracket_open(i);
        break;

      case BRACKET_CLOSE:
        bracket_close(i);
        break;

      default:
        break;
    }
    i++;
  }
}