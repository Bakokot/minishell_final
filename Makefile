NAME	=	minishell

LIBFT_DIR	=	libft/
LIBFT_NAME	=	libft.a
LIBFT		=	$(addprefix $(LIBFT_DIR), $(LIBFT_NAME))

FT_PRINTF_DIR = ft_printf/
FT_PRINTF_NAME = libftprintf.a
FT_PRINTF = $(addprefix $(FT_PRINTF_DIR), $(FT_PRINTF_NAME))

INC            :=    minishell.h
INC_DIR        :=    inc/

HEADERS        := $(addprefix $(INC_DIR), $(INC))

SRC_DIR        :=	src/
SRC            :=	main.c new_line.c\
					utils/error.c utils/utils.c utils/freeing.c utils/ft_strcmp.c utils/quotes_utils.c\
					env/env_utils.c env/env.c \
					tokenizer/tokenizer.c tokenizer/token_utils.c tokenizer/token_utils2.c\
					tokenizer/new_replace_var.c tokenizer/new_replace_var_utils.c tokenizer/replace_var_special_cases.c\
					tokenizer/remove_token_quotes.c\
					signals/signals.c signals/ctrl_d.c\
					builtins/echo.c builtins/env.c builtins/pwd.c builtins/cd.c \
					builtins/unset.c builtins/export.c builtins/export2.c builtins/ft_exit.c exec/exec.c exec/is_builtin.c\
					exec/utils.c exec/handle_command.c exec/redirection.c exec/heredoc.c exec/heredoc2.c exec/pipe.c exec/pipe2.c exec/pipe_utils.c\
					exec/check_args.c exec/check_dir.c

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


all: libft ft_printf $(NAME)

$(NAME): $(OBJ) $(FT_PRINTF) $(LIBFT)
	$(CC) $(CC_FLAGS) $(OBJ) -L ./libft -lft -L ./ft_printf -lftprintf -lreadline -o $@
	@echo "All compiled"

$(OBJ): $(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS) Makefile
	@mkdir -p $(@D)
	@$(eval COMPILED=$(shell echo $$((${COMPILED}+1))))
	@echo "Compiling in progress ${COMPILED}/${TOTAL_COMPILATION}"
	$(CC) $(CC_FLAGS) -I $(INC_DIR) -c $< -o $@

ft_printf:
	@make -C ft_printf

libft:
	@make -C libft

clean: cleanlibft cleanprintf
	@rm -rf $(OBJ_DIR)
	@echo "Everything removed"

fclean: fcleanlibft fcleanprintf clean
	@rm -rf $(NAME)

cleanlibft:
	@make clean -C ${LIBFT_DIR}

fcleanlibft: cleanlibft
	@make fclean -C ${LIBFT_DIR}

cleanprintf:
	@make clean -C $(FT_PRINTF_DIR)

fcleanprintf: cleanprintf
	@make fclean -C $(FT_PRINTF_DIR)

re: fclean
	make all

.PHONY: all clean fclean re libft ft_printf
