/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:31:31 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/12/11 14:01:03 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <signal.h>
# include <sys/wait.h>

# include "../libft/inc/libft.h"

# define SUCCESS 0
# define ERROR 404

/**
 * ERROR MESSAGES
*/
# define ERR_MALLOC "Memory allocation error\n"

/*
		LITTERAL	--> (0)		An argument
		PIPE		-->	(1)		pipe (|)
		RI			-->	(2)		redirecting input (<)
		HEREDOC		-->	(3)		here documents (<<)
		RO			-->	(4)		redirecting output (>)
		ARO			-->	(5)		appending redirecting output (>>)
*/
typedef enum e_type
{
	LITTERAL,
	PIPE,
	RI,
	HEREDOC,
	RO,
	ARO,
}	t_type;

typedef struct s_token
{
	char			*token;
	t_type			type;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char				*key;
	char				*values;
	struct s_env		*next;
}	t_env;

/**
 * Tokenizer
*/
t_token	**tokenize(char *line, t_env *env);
void	replace_vars(t_token **token_lst, t_env *env);
void	skip_single_quotes(int *i, char *str);
bool	single_dollar(t_token *token);
char	*update_dollarless_token(t_token *token, int i, \
int marker, char *new_token);

/**
 * t_token struct utils
*/
t_token	*create_new_token(char *str, int type);
void	add_back_token(t_token **token_lst, t_token *token);
t_token	*get_last_token(t_token *lst);
void	delete_first_token(t_token **token_lst);
char	*add_litteral_dollar(char *dollarless_token, int *i, char *tkn);
void	set_new_token(t_token *token, char *dollarless);
size_t	token_size(t_token *token_lst);

/**
 * Environment
*/
t_env	*init_env(char **envp);

/**
 * t_env struct utils
*/
t_env	*get_last_env(t_env *lst);
t_env	*create_new_env(char *key, char *values);
char	*get_env_key(char *envp);
char	*get_env_values(char *envp);
char	**env_lst_into_char(t_env *env);
size_t	env_size(t_env *env);
char	*lookup_values(char *key, t_env *env);
void	add_back_env(t_env **env_lst, t_env *env);

/**
 * Utils
*/
int		ft_isspace(char c);
int		is_quote(char c);
int		is_metachar(char c);
int		is_double_redirection(char *str);
char	*ft_strndup(char *s1, size_t size);
int		ft_strcmp(char *s1, char *s2);
void	free_array(char **arr);

//Builtins
int	echo(t_token *token_lst);
int	env_builtin(t_env *env);
int	pwd(void);
int	cd(t_token	*token_lst, t_env *env);
int	export(t_token *token_lst, t_env **env);
int	unset(t_token *token_lst, t_env **env);
void	print_export(t_env *env);

//Exec
int	is_bultin(t_token *token_lst, t_env *env);
void	exec_command(t_token *token_lst, t_env *env);

/**
 * Freeing
*/
void	free_all(t_token **token_lst, t_env *env);
void	free_all_env(t_env *env_lst);
void	free_all_token(t_token **token_lst);

/**
 * Error management
*/
void	log_error(char *str);

/**
 * Signals management
*/
void	signal_handling(void);

/**
 * TO ERASE IN THE END
*/
void	print_env(t_env *env);

#endif
