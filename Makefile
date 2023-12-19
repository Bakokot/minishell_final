NAME	=	minishell

LIBFT_DIR	=	libft/
LIBFT_NAME	=	libft.a
LIBFT		=	$(addprefix $(LIBFT_DIR), $(LIBFT_NAME))

INC            :=    minishell.h
INC_DIR        :=    inc/

HEADERS        := $(addprefix $(INC_DIR), $(INC))

SRC_DIR        :=	src/
SRC            :=	main.c\
					utils/error.c utils/utils.c utils/freeing.c utils/ft_strcmp.c\
					env/env_utils.c env/env.c \
					tokenizer/tokenizer.c tokenizer/token_utils.c\
					tokenizer/new_replace_var.c tokenizer/new_replace_var_utils.c\
					minigc/gc.c\
					signals/signals.c\
					builtins/echo.c builtins/env.c builtins/pwd.c builtins/cd.c \
					builtins/unset.c builtins/export.c builtins/export2.c exec/exec.c exec/is_builtin.c exec/utils.c\
					exec/handle_command.c exec/redirection.c

COMPILED = 0
TOTAL_COMPILATION = $(shell ((echo ${SRC}) | wc -w | sed -e 's/^[ \t]*//'))

OBJ_DIR        :=    obj/
OBJ            :=    $(SRC:%.c=$(OBJ_DIR)%.o)

# define standard colors
_END        :=    \x1b[0m
_BOLD       :=    \x1b[1m
_UNDER      :=    \x1b[4m
_REV        :=    \x1b[7m
_GREY       :=    \x1b[30m
_RED        :=    \x1b[31m
_GREEN      :=    \x1b[32m
_YELLOW     :=    \x1b[33m
_BLUE       :=    \x1b[34m
_PURPLE     :=    \x1b[35m
_CYAN       :=    \x1b[36m
_WHITE      :=    \x1b[37m

#Compiler
CC            :=    cc
CC_FLAGS      :=    -Wextra -Werror -Wall


all: $(NAME)

$(NAME): libft $(OBJ)
	$(CC) $(CC_FLAGS) $(OBJ) -L ./libft -lft -lreadline -o $@
	@echo "All compiled"

$(OBJ): $(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS) Makefile
	@mkdir -p $(@D)
	@$(eval COMPILED=$(shell echo $$((${COMPILED}+1))))
	@echo "Compiling in progress ${COMPILED}/${TOTAL_COMPILATION}"
	@$(CC) $(CC_FLAGS) -I $(INC_DIR) -c $< -o $@

libft:
	@make -C libft

clean: cleanlibft
	@rm -rf $(OBJ_DIR)
	@echo "Everything removed"

fclean: fcleanlibft clean
	@rm -rf $(NAME)

cleanlibft:
	@make clean -C ${LIBFT_DIR}

fcleanlibft: cleanlibft
	@make fclean -C ${LIBFT_DIR}

re: fclean
	make all

.PHONY: all clean fclean re libft
