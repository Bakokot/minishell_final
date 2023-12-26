NAME = libftprintf.a

CC = cc
FLAGS = -Wall -Wextra -Werror

SRC_DIR = src/
OBJ_DIR = obj/

HEADER = ft_printf.h
SRC = ft_printf.c ft_putchar.c ft_putstr.c ft_putnbr.c ft_putnbr_base.c
OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER) Makefile | $(OBJ_DIR)
	@$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "ft_printf clean"

fclean: clean
	@rm -f $(NAME)
	@echo "ft_printf fclean"

re: fclean
	all

.PHONY : all clean fclean re
