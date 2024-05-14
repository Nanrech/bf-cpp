#include <vector>
#include <iostream>

#define IS_VALID_CHAR(c) (c == '>' || c == '<' || c == '+' || c == '-' || c == '.' || c == ',' || c == '[' || c == ']')
#define IS_OPERATOR_CHAR(c) (c == '>' || c == '<' || c == '+' || c == '-' || c == '.' || c == ',')
#define IS_BRACKET_CHAR(c) (c == '[' || c == ']')

using namespace std;


typedef struct {
  unsigned int amount;  // Number of times this instruction is repeated OR where to jump (if bracket)
  char type;            // Operator
} BfToken;

class BfInterpreter {
  private:
    size_t program_pointer;            // For .tokens
    vector<char> tape = {0};  // Unlimited length tape
    unsigned int tape_pointer = 0;     // Current cell in tape

    void move_right() {
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

      program_pointer++;
    }

    void move_left() {
      // Move .amount to the left. No negative index allowed
      unsigned int token_amount = tokens[program_pointer].amount;
      // "error: cOmPaRiSoN oF uNsIgNeD eXpReSsIoN iN '>= 0' iS aLwAyS tRuE" 🤓☝
      int diff = tape_pointer - token_amount;

      if (diff >= 0) {
        tape_pointer -= token_amount;
      }
      else {
        tape_pointer = 0;
      }

      program_pointer++;
    }

    void increment() {
      tape[tape_pointer] += tokens[program_pointer].amount;
      program_pointer++;
    }

    void decrement() {
      tape[tape_pointer] -= tokens[program_pointer].amount;
      program_pointer++;
    }

    void output() {
      for (unsigned int _ = 0; _ < tokens[program_pointer].amount; _++) {
        cout << tape[tape_pointer];
      }
      program_pointer++;
    }

    void input() {
      // No idea why this (more than one consecutive ,) would ever be used but it is supported
      for (unsigned int _ = 0; _ < tokens[program_pointer].amount; _++) {
        char c;
        cin >> c;
        tape[tape_pointer] = c;
      }

      program_pointer++;
    }

    void bracket_open() {
      if (tape[tape_pointer] == 0) {
        program_pointer = tokens[program_pointer].amount + 1;
      }
      else {
        program_pointer++;
      }
    }

    void bracket_close() {
      if (tape[tape_pointer] != 0) {
        program_pointer = tokens[program_pointer].amount + 1;
      }
      else {
        program_pointer++;
      }
    }

  public:
    vector<BfToken> tokens; // No encapsulation. I'm taking the tokens from main and inserting them into this thing RAW.
    void run();             // Executes everything
    void view_tape();       // Debug function
};
