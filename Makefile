NAME = WebServ

CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98 -O3 #-fsanitize=address -g
INCLUDES = -I include

RM = rm -rf

SRC_DIR = src/
OBJ_DIR = obj/

SRC_FILES = Server

OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
SRC = $(addprefix $(SRC_DIR), $(addsuffix .cpp, $(SRC_FILES)))

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\033[0;33m\nCOMPILING WebServ...\n"
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "\033[1;32m./WebServ created\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re