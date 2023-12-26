/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 00:14:00 by thibault          #+#    #+#             */
/*   Updated: 2023/12/27 00:15:54 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_directory(char *path)
{
	struct stat	file;

	if (stat(path, &file) == -1)
		return (NULL);
	if (access(path, F_OK) == 0)
	{
		if (S_ISDIR(file.st_mode))
		{
			ft_printf(2, "%s: Is a directory\n", path);
			g_exit_status = 126;
			return (NULL);
		}
		return (ft_strdup(path));
	}
	ft_printf(2, "%s: No such file or directory\n", path);
	g_exit_status = 127;
	return (NULL);
}
