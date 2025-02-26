#include <cstdint>
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <array>

#define MAX_TAPE_SIZE 30000
#define IS_CHAR_VALID(currentChar) (currentChar == '>' || currentChar == '<' || currentChar == '+' || currentChar == '-' || currentChar == '.' || currentChar == ',' || currentChar == '[' || currentChar == ']')
#define IS_CHAR_MULTI(currentChar) (currentChar == '>' || currentChar == '<' || currentChar == '+' || currentChar == '-')

typedef struct Token {
  char type;
  size_t data; // index to matching jump instruction OR nº times command should be repeated
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
  // First pass, get amount of tokens
  char currentChar;
  char lastChar = '\0';

  int tokenAmount = 0;

  while (inFile.get(currentChar)) {
    if (!IS_CHAR_VALID(currentChar)) { continue; }

    // Some successive characters are just stored as a single command
    // Their 'data' field represents how many times it should be executed
    if (!IS_CHAR_MULTI(currentChar) || currentChar != lastChar) {
      tokenAmount++;
    }

    lastChar = currentChar;
  }

  // ---- init 'ROM' ----
  std::vector<Token> commands;
  commands.resize(tokenAmount);

  // Rewind file
  inFile.clear();
  inFile.seekg(0);

  // ---- Store tokens ----
  // Second pass, store tokens
  size_t i = 0;
  size_t data = 1;
  lastChar = '\0';
  std::stack<size_t> bracketStack;

  while (inFile.get(currentChar)) {
    if (!IS_CHAR_VALID(currentChar)) { continue; }

    if (currentChar == '[') {
      bracketStack.push(i);
      data = 1;
    }
    else if (currentChar == ']') {
      if (bracketStack.empty()) {
        std::cout << "Error in input file at pos. " << inFile.tellg() << std::endl;
        throw std::runtime_error("Unmatched Closing Bracket");
      }
      // Assign last opening bracket's index to this one
      data = bracketStack.top();
      bracketStack.pop();
      // Assign this one's index to last bracket
      commands[data].data = i;
    }
    else {
      // Optimize
      if (IS_CHAR_MULTI(currentChar) && currentChar == lastChar) {
        commands[i - 1].data += 1;
        continue;
      }
      else {
        data = 1;
      }
    }

    lastChar = currentChar;
    commands[i++] = Token {
      .type = currentChar,
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
  size_t idx = 0;

  while (idx != commands.size()) {
    auto t = commands[idx];

    switch (t.type) {
      case '>': {
        if (pointer == tape.size() - 1) { pointer = 0; }
        else { pointer += t.data; }
        break;
      }
      case '<': {
        if (pointer == 0) { pointer = tape.size() - 1; }
        else { pointer -= t.data; }
        break;
      }
      case '+': {
        tape[pointer] += t.data;
        break;
      }
      case '-': {
        tape[pointer] -= t.data;
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
