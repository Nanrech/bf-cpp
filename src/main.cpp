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
  vector<char> tokens;
  char aux_char;

  while (in_file.get(aux_char)) {
    if (Interpreter.is_opcode(aux_char)) {
      tokens.insert(tokens.end(), aux_char);
    }
  }
  in_file.close();

  cout << argv[1] << endl;
  Interpreter.run(tokens);

  return 0;
}
