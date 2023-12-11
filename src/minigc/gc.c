#include "minishell.h"

void	gc_init(t_gc_glob *gc)
{
	gc->first_node = NULL;
	gc->last_node = NULL;
	gc->nb_allocs = 0;
	gc->total_size = 0;
}

/**
 * Malloc the size wanted and store it in the garbage collector
 * If first_node is not allocated :
 * - We initialize the first ptr of the gc
 * Else :
 * - We add a new ptr to the gc and update the last node
 * @return the adress of the mallocated object 
 * (that's why we return adress of last_node and + 1)
*/
void	*gc_malloc(t_gc_glob *gc, size_t size)
{
	t_gc_node	*temp;
	if (gc->first_node == NULL)
	{
		gc->first_node = malloc(sizeof(t_gc_glob) + size);
		if (gc->first_node == NULL)
			return (NULL);
		gc->last_node = gc->first_node;
		gc->last_node->prev = NULL;
	}
	else
	{
		gc->last_node->next = malloc(sizeof(t_gc_glob) + size);
		if (gc->last_node->next == NULL)
			return (NULL);
		temp = gc->last_node;
		gc->last_node = temp->next;
		gc->last_node->prev = temp;
	}
	gc->total_size += size;
	gc->nb_allocs += 1;
	gc->last_node->next = NULL;
	gc->last_node->size = size;
	return (gc->last_node + 1);
}
/**
 * First we find out the node we need to erase :
 * - It's the adress just before the allocation of the pointer
 * Then we check if the node to erase is the first one : 
 * - We update the structure accordingly 
 * Then we check if the node to erase is the last one :
 * - We update the structure accordingly
 * Eventually we free what needs to be freed and reset the value to NULL after that
*/
/*
NOT WORKING : WHEN WE FREE ONE AND MULTIPLE OBJECTS HAVE BEEN MALLOCATED, SEGFAULT !
*/
void	gc_free(t_gc_glob *gc, void **ptr)
{
	t_gc_node	*node_to_erase;
	t_gc_node	*temp;

	node_to_erase = ((t_gc_node *)(*ptr) - 1);
	if (node_to_erase->prev == NULL)
		gc->first_node = node_to_erase->next;
	else
	{
		temp = node_to_erase->next;
		temp->prev = node_to_erase->prev;
	}
	if (node_to_erase->next == NULL)
		gc->last_node = node_to_erase->prev;
	else
	{
		temp = node_to_erase->prev;
		temp->next = node_to_erase->next;
	}
	gc->total_size -= node_to_erase->size;
	gc->nb_allocs -= 1;
	free(node_to_erase);
	(*ptr = NULL);
	return ;
}

/**
 * @brief free all the memory allocated and stored in the garbage collector
*/
void	gc_free_all(t_gc_glob *gc)
{
	t_gc_node	*temp;

	while (gc->first_node)
	{
		temp = gc->first_node->next;
		free(gc->first_node);
		gc->first_node = temp;
	}
	gc->first_node = NULL;
	gc->last_node = NULL;
	gc->total_size = 0;
	gc->nb_allocs = 0;
}