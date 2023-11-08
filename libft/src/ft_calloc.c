/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:09:44 by tbarde-c          #+#    #+#             */
/*   Updated: 2022/11/14 16:42:21 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*ret;

	if (size != 0 && count > SIZE_MAX / size)
		return (0);
	ret = malloc(size * count);
	if (!ret)
		return (0);
	ft_bzero(ret, count * size);
	return (ret);
}
