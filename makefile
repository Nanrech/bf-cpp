CC = g++

SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

EXE = bfc
CFLAGS = -I$(INC_DIR) -Wall -Wfatal-errors -Wextra -Werror -MMD -MP

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)


$(EXE): $(OBJ)
		$(CC) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm $(OBJ_DIR)/*.o $(OBJ_DIR)/*.d
