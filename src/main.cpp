#include <cstdint>
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <array>

#define MAX_TAPE_SIZE 30000
#define IS_CHAR_VALID(c) (c == '>' || c == '<' || c == '+' || c == '-' || c == '.' || c == ',' || c == '[' || c == ']')

typedef struct Token {
  char type;
  int data; // index to matching jump instruction
} Token;


int main(int argc, char* argv[]) {
  // Input file provided?
  if (argc != 2) {
    std::cout << "Error: No input file.\nUsage: " << argv[0] << " <program.bf>" << std::endl;
    return 1;
  }

  // Input file exists?
  std::ifstream inFile(argv[1]);

  if (inFile.fail()) {
    std::cout << "Error: Couldn't read input file " << argv[1] << std::endl;
    return 1;
  }

  // ---- Read file ----
  // First pass, calculate amount of tokens
  char c;
  int tokenAmount = 0;

  while (inFile.get(c)) {
    if (IS_CHAR_VALID(c)) {
      tokenAmount++;
    }
  }

  // ---- init 'ROM' ----
  std::vector<Token> commands;
  commands.resize(tokenAmount);

  // Rewind file
  inFile.clear();
  inFile.seekg(0);

  // ---- Store tokens ----
  // Second pass, store tokens
  int i = 0;
  std::stack<int> bracketStack;

  while (inFile.get(c)) {
    if (!IS_CHAR_VALID(c)) { continue; }

    int data = 0;

    if (c == '[') {
      // Store last opening bracket
      bracketStack.push(i);
    }
    else if (c == ']') {
      // Check for underflow
      if (bracketStack.size() == 0) {
        std::cout << "Error in input file at pos. " << inFile.tellg() << std::endl;
        throw std::runtime_error("Unmatched Closing Bracket");
      }

      // Assign latest opening bracket and pop the stack
      data = bracketStack.top();
      bracketStack.pop();
      // Assign current index to latest opening bracket
      commands[data].data = i;
    }

    commands[i++] = Token {
      .type = c,
      .data = data,
    };
  }

  // Check for overflow
  if (bracketStack.size() != 0) {
    std::cout << "Error in input file" << std::endl;
    throw std::runtime_error("Unmatched Opening Bracket");
  }

  // ---- Close file ----
  inFile.close();

  // ---- init memory ----
  std::array<uint8_t, MAX_TAPE_SIZE> tape = {0};
  size_t pointer = 0;

  // ---- Execute ----
  unsigned int idx = 0;

  while (idx != commands.size()) {
    auto t = commands[idx];

    switch (t.type) {
      case '>': {
        if (pointer == tape.size() - 1) { pointer = 0; }
        else { pointer++; }
        break;
      }
      case '<': {
        if (pointer == 0) { pointer = tape.size() - 1; }
        else { pointer--; }
        break;
      }
      case '+': {
        tape[pointer]++;
        break;
      }
      case '-': {
        tape[pointer]--;
        break;
      }
      case '.': {
        // TODO: Do better
        std::cout << tape[pointer];
        break;
      }
      case ',': {
        // TODO: Do better
        std::cin >> tape[pointer];
        break;
      }
      case '[': {
        if (tape[pointer] == 0) {
          idx = t.data;
        }
        break;
      }
      case ']': {
        if (tape[pointer] != 0) {
          idx = t.data;
        }
        break;
      }
      default:
        break;
    }

    idx++;
  }

  return 0;
}
