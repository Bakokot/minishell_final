/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:14:40 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/12/27 00:55:03 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static int	numeric(const char *str, int i)
{
	if (str[i] <= '9' && str[i] >= '0')
		return (1);
	else
		return (0);
}

static int	ft_isspace(const char *str, int i)
{
	if (str[i] == ' ' || str[i] == '\t' || str[i] == '\v')
		return (1);
	if (str[i] == '\n' || str[i] == '\f' || str[i] == '\r')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int						i;
	int						flag;
	long long unsigned int	nb;

	i = 0;
	flag = 1;
	nb = 0;
	while (ft_isspace(str, i))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			flag = -1;
		i++;
	}
	while (numeric(str, i))
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	nb *= flag;
	return (nb);
}
