# yeag 27/VI/2023

https://esolangs.org/wiki/brainfuck

Really simple program. `main.cpp` takes in a file through the command line (`.\bfc.exe hello_world.bf`) &
```cpp
  BfInterpreter Interpreter; // Create interpreter instance
  vector<char> tokens;
  char aux_char;

  // Every *valid* token in the file is slurped into the tokens vector, the file is closed when the process is finished
  while (in_file.get(aux_char)) {
    if (Interpreter.is_opcode(aux_char)) {
      tokens.insert(tokens.end(), aux_char);
    }
  }
  in_file.close();
```
\-\- This is how we determine if a token (any character inside the provided file) is a valid op_code. It's just a simple range loop over a predefined set of valid codes.
```cpp
bool BfInterpreter::is_opcode(const char c) {
  for (char i : {'>', '<', '+', '-', '.', '[', ']'}) {
    if (i == c) {
      return true;
    }
  }
  return false;
}
```
And finally, `Interpreter.run(tokens);`, which is just a switch statement that executes the appropiate function for each token in the vector.
