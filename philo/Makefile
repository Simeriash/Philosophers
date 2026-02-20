NAME := philo

CC := cc
CFLAGS := -Wall -Wextra -Werror -g # -fsanitize=address

HEADER := philo.h


SOURCES := philo.c ft_init_input.c ft_everyone_to_the_table.c ft_table_utils.c

SRC_DIR := src/
SRC := $(addprefix $(SRC_DIR), $(SOURCES))

OBJ_DIR := obj/
OBJ := $(addprefix $(OBJ_DIR), $(SOURCES:.c=.o))

.PHONY : all clean fclean re

all : $(NAME)

$(NAME) : $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -pthread -o $@

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -I $(HEADER) -c $< -o $@

clean :
	rm -rf $(OBJ)
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -rf $(NAME)

re : fclean all
