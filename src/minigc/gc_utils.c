/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:10:15 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/12/08 14:57:54 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Create a new t_token and fills the char * value
*/
t_gc	*create_new_gc(void *ptr, void (*free_function)(t_ptr))
{
	t_gc	*new_gc;

	new_gc = malloc(sizeof(t_gc));
	if (!new_gc)
		return (log_error(ERR_MALLOC), NULL);
	new_gc->ptr = ptr;
	new_gc->free_function = free_function;
	new_gc->next = NULL;
	return (new_gc);
}

void	add_back_gc(t_gc **gc, t_gc *new)
{
	if (!gc || !new)
		return ;
	if (*gc)
	{
		get_last_gc(*gc)->next = new;
	}
	if (*gc == NULL)
	{
		*gc = new;
	}
}

t_gc	*get_last_gc(t_gc *lst)
{
	while (lst && lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}
