NAME = scop

# Sources with their directories
SRC_DIR = ./srcs
SRC_MAIN = main.c
OTHER_DIR =
SRC_OTHER =

SRCS = 	$(SRC_MAIN) \
		$(addprefix $(OTHER_DIR), $(SRC_OTHER))

# libraries
LIB_PATH_GLEW =	./glew-2.2.0/lib
LIB_INCLUDE_GLEW = ./glew-2.2.0/include
LIB_PATH_GLFW =	./glfw-3.3.4/src
LIB_INCLUDE_GLFW =	./glfw-3.3.4/include
LIB_PATH_OTHER =
LIB_INCLUDE_OTHER =

LIBS_PATH = $(LIB_PATH_GLEW) $(LIB_PATH_GLFW) $(LIB_PATH_OTHER)
LIBS_INCLUDE = $(LIB_INCLUDE_GLEW) $(LIB_INCLUDE_GLFW) $(LIB_INCLUDE_OTHER)
LIBS_LINK = GLEW glfw3 GL X11 pthread m dl

# Includes
INCLUDE_DIR =	./includes \
				$(LIBS_INCLUDE)


# Directory tree
DIRECTORIES = $(OTHER_DIR)
OBJ_DIR = ./bin
OBJ_DIRECTORIES =	$(OBJ_DIR) \
					$(addprefix $(OBJ_DIR)/, $(DIRECTORIES))

# All object files
OBJECTS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

# Some necessary vars
CC = gcc
FLAGS = -Wall -Wextra -Werror -Wno-unused

.PHONY: all
all: $(OBJ_DIRECTORIES) $(NAME)
	@echo "\033[32mScop successfully built\033[0m"

$(NAME): $(OBJECTS)
	@$(CC) $(FLAGS) $(OBJECTS) $(addprefix -L./, $(LIBS_PATH)) $(addprefix -l, $(LIBS_LINK)) -o $(NAME)

$(OBJ_DIRECTORIES):
	@mkdir -p $(OBJ_DIRECTORIES)

$(OBJECTS) : $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@/bin/echo -n $<
	@$(CC) $(FLAGS) $(addprefix -I./, $(INCLUDE_DIR)) -c $< -o $@
	@/bin/bash -c "echo -en \"\033[2K\033[0G\""
#include $(wildcard $(OBJ_DIR)/*.d $(OBJ_DIR)/*/*.d)

.PHONY: clean
clean:
	@rm -rf $(OBJ_DIR)

.PHONY: fclean
fclean: clean
	@rm -rf $(NAME)

.PHONY: re
re: fclean all

.PHONY: test
test:
	@echo "OBJECTS: "
	@echo $(OBJECTS)