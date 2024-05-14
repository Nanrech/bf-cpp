#include "interpreter.h"
#include <fstream>

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

  //ofstream out("out.txt"); // Messing with stdout. Ignore.
  //streambuf *sout = cout.rdbuf();

  for (program_pointer = 0; program_pointer <= tokens.size() - 1;) {
  // The program pointer moves inside each of these bc brackets mess with the flow
    
    // DEBUG:
    //cout.rdbuf(out.rdbuf());
    //view_tape();
    //cout.rdbuf(sout);

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
