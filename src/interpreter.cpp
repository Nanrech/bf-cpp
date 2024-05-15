#include "interpreter.h"

using namespace std;


void BfInterpreter::view_tape() {
  cout << "byte: " << tokens[program_pointer].type << tokens[program_pointer].amount << " ";
  cout << "size: " << tape.size() << " | ";
  cout << "pointer: " << tape_pointer << endl;

  for (auto cell : tape) {
    cout << (int)cell << " ";
  }
  cout << endl;
}

void BfInterpreter::run() {
  // Loops through all registered tokens and executes them. Pretty self-explanatory
  for (program_pointer = 0; program_pointer <= tokens.size() - 1; program_pointer++) {
    switch (tokens[program_pointer].type) {
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
        bracket_open();
        break;

      case ']':
        bracket_close();
        break;
      
      default:
        cout << "Whar();";
        break;
    }
  }
}

inline void BfInterpreter::move_right() {
  // Move .amount to the right. If the tape is too small, expand it
  unsigned int token_amount = tokens[program_pointer].amount;

  if ((tape_pointer + token_amount) >= tape.size()) {
    for (unsigned int _ = 0; _ < token_amount; _++) {
      tape_pointer++;
      tape.push_back(0);
    }
  }
  else {
    for (unsigned int _ = 0; _ < token_amount; _++) {
      tape_pointer++;
    }
  }
}

inline void BfInterpreter::move_left() {
  // Move .amount to the left. No negative index allowed
  unsigned int token_amount = tokens[program_pointer].amount;
  // "error: cOmPaRiSoN oF uNsIgNeD eXpReSsIoN iN '>= 0' iS aLwAyS tRuE" 🤓☝
  // error here bc tape_pointer and token.amount are both unsigned so they'd wrap around
  int diff = tape_pointer - token_amount;

  if (diff >= 0) {
    tape_pointer -= token_amount;
  }
  else {
    tape_pointer = 0;
  }
}

inline void BfInterpreter::increment() {
  tape[tape_pointer] += tokens[program_pointer].amount;
}

inline void BfInterpreter::decrement() {
  tape[tape_pointer] -= tokens[program_pointer].amount;
}

inline void BfInterpreter::output() {
  for (unsigned int _ = 0; _ < tokens[program_pointer].amount; _++) {
    cout << tape[tape_pointer];
  }
}

inline void BfInterpreter::input() {
  // No idea why this (more than one consecutive ,) would ever be used but it is supported
  for (unsigned int _ = 0; _ < tokens[program_pointer].amount; _++) {
    char c;
    cin >> c;
    tape[tape_pointer] = c;
  }
}

inline void BfInterpreter::bracket_open() {
  if (tape[tape_pointer] == 0) {
    program_pointer = tokens[program_pointer].amount;
  }
  else {
    return;
  }
}

inline void BfInterpreter::bracket_close() {
  if (tape[tape_pointer] != 0) {
    program_pointer = tokens[program_pointer].amount;
  }
  else {
    return;
  }
}
