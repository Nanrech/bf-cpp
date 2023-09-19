#include <vector>
#include <stack>
#include <iostream>
#include <stdexcept>


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
    bool is_opcode(const char c);
    void run(const std::vector<char> &tokens);
    // Debug function
    void view_tape();
};
