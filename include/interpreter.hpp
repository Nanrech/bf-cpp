#include <vector>
#include <stack>
#include <iostream>
#include <stdexcept>
#include "opcodes.hpp"


class BfInterpreter {
  private:
    unsigned int pointer = 0;
    std::vector<unsigned char> tape = {0};
    std::stack<unsigned int> stack;

    void move_right();
    void move_left();
    void increment();
    void decrement();
    void output();
    void input();
    void bracket_open(const size_t i);
    void bracket_close(size_t &i);

  public:
    // Debug function
    void view_tape();
    void run(const std::vector<char> &tokens);
};
