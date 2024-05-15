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
    size_t program_pointer;         // For .tokens
    vector<char> tape = {0};        // Unlimited length tape
    unsigned int tape_pointer = 0;  // Current cell in tape

    void move_right();
    void move_left();
    void increment();
    void decrement();
    void output();
    void input();
    void bracket_open();
    void bracket_close();

  public:
    vector<BfToken> tokens;  // No encapsulation needed
    void run();              // Executes everything
    void view_tape();        // Debug function
};
