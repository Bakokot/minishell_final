#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../libft/inc/libft.h"

# define SUCCESS 0
# define ERROR 404

/**
 * ERROR MESSAGES
*/
# define ERR_MALLOC "Memory allocation error"

/*
		LITTERAL	--> (0)		An argument
		PIPE		-->	(1)		pipe (|)
		RI			-->	(2)		redirecting input (<)
		HD			-->	(3)		here documents (<<)
		RO			-->	(4)		redirecting output (>)
		ARO			-->	(5)		appending redirecting output (>>)
*/
typedef enum e_type
{
	LITTERAL,
	PIPE,
	RI,
	HD,
	RO,
	ARO,
	
}	t_type;

typedef struct s_token
{
	char			*token;
	t_type			type;
	struct s_token	*next;
}	t_token;

/**
 * TOKENIZER
*/
t_token	**tokenize(char *line);

/**
 * UTILS
*/
int		ft_isspace(char c);
int		is_quote(char c);
int		is_metachar(char c);
int		is_double_redirection(char *str);
char	*ft_strndup(char *s1, size_t size);

/**
 * t_token struct utils
*/
t_token	*create_new_token(char *str);
void	add_back_token(t_token **token_lst, t_token *token);
void	add_one_token(t_token *token, char *str);
t_token	*get_last_token(t_token *lst);

/**
 * Error management
*/
void	log_error(char *str);

#endif