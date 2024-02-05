#include <vector>
#include <stack>
#include <iostream>
#include <stdexcept>


enum {
  BFT_MOVR = '>',
  BFT_MOVL = '<',
  BFT_INC = '+',
  BFT_DEC = '-' ,
  BFT_OUT = '.',
  BFT_INP = ',',
  BFT_BRO = '[',
  BFT_BRC = ']'
};

typedef struct {
  // Number of repeat instructions OR 0
  unsigned int amount;
  // BfTokenType
  char type;
} BfToken;

class BfInterpreter {
  private:
    unsigned int pointer = 0;
    std::vector<unsigned char> tape = {0};
    std::stack<unsigned long int> stack;

    void move_right();
    void move_left();
    void increment();
    void decrement();
    void output();
    void input();
    void bracket_open(size_t &i, const BfToken token);
    void bracket_close(size_t &i, const BfToken token);

  public:
    bool is_opcode(const char c);
    void run(const std::vector<BfToken> &tokens);
    // Debug function
    void view_tape();
};
