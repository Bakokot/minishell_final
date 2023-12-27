/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 00:09:08 by thibault          #+#    #+#             */
/*   Updated: 2023/12/27 12:51:28 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_new_line_pipe(char *line)
{
	char	*new_line;
	char	*temp;

	temp = line;
	new_line = readline("> ");
	if (new_line == NULL)
	{
		write(1, ERR_EOF3, ft_strlen(ERR_EOF2));
		free(line);
		return (NULL);
	}
	line = ft_strjoin(line, "\n");
	free(temp);
	temp = line;
	line = ft_strjoin(line, new_line);
	free(temp);
	return (line);
}

char	*read_new_line(char *line)
{
	char	*new_line;
	char	*temp;
	char	c;

	c = 0;
	temp = line;
	new_line = readline("> ");
	if (new_line == NULL)
	{
		c = strchr_quote(line);
		write(1, ERR_EOF1, ft_strlen(ERR_EOF1));
		write(1, &c, 1);
		write(1, ERR_EOF2, ft_strlen(ERR_EOF2));
		free(line);
		return (NULL);
	}
	line = ft_strjoin(line, "\n");
	free(temp);
	temp = line;
	line = ft_strjoin(line, new_line);
	free(temp);
	return (line);
}
