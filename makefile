# Compiler & language choice
CC = g++
CF = .cpp

# Directory names
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

# Executable name
EXE = bfc

# CFlags
CFLAGS = -I$(INC_DIR) -std=c++23 -Wall -Wfatal-errors -Wextra -Werror -MMD -MP -O2

# Makefile wizardry
SRC = $(wildcard $(SRC_DIR)/*$(CF))
OBJ = $(SRC:$(SRC_DIR)/%$(CF)=$(OBJ_DIR)/%.o)

$(EXE): $(OBJ)
		$(CC) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%$(CF)
		$(CC) $(CFLAGS) -c $< -o $@
