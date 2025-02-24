# Executable name
EXE = bfc

# Compiler
CC = g++

# CFlags
CFLAGS = -Iinclude -std=c++23 -Wall -MMD -MP # -Wfatal-errors -Wextra -Werror

# Makefile wizardry
SRC = $(wildcard src/*.cpp)
OBJ = $(patsubst src/%, obj/%, $(SRC:.cpp=.o))

# Make targets
$(EXE): $(OBJ)
		$(CC) $^ -o $@

obj/%.o: src/%.cpp
		$(CC) $(CFLAGS) -c $< -o $@

run: $(EXE)
		./$(EXE)

clean:
		@del /q obj
		@del /q $(EXE).exe
