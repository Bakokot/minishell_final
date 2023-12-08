/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:00:07 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/12/08 14:57:47 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief free all the ptr of the garbage collector
 * + the struct of the garbage collector itself
*/
void	gc_free_all(t_gc *gc)
{
	t_gc	*temp;

	while (gc)
	{
		temp = gc;
		if (gc->free_function != NULL && gc->ptr != NULL)
			gc->free_function(gc->ptr);
		else if (gc->ptr != NULL)
			free(gc->ptr);
		gc = gc->next;
		free(temp);
	}
}

/**
 * @brief malloc a ptr and store it in the garbage collector chained list 
*/
void	gc_malloc(t_gc **gc, size_t size, void **ptr, \
void (*free_function)(t_ptr))
{
	*ptr = malloc(size);
	if (!ptr)
		return ;
	add_back_gc(gc, create_new_gc(*ptr, free_function));
}
