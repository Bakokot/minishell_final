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
 * Then we update the structure to prepare the deletion of the node :
 * - Set the previous node->next to the current next
 * - Set the next node->prev to the current previous
 * If the node we free is the first / last node, we just update the first / last node of gc global (since prev / next == NULL)

 	-------------------------------------------------
	|								   				|
	|								   				|
	|								   				V
	Node prev->Next		Current Node			Node next
	Node prev		      					Node next->prev
	^								   				|
	|							           			|
	|								   				|
	-------------------------------------------------

node->prev->next has to become current next & node->next->prev has to become current prev
 *
*/
void	gc_free(t_gc_glob *gc, void **ptr)
{
	t_gc_node	*node_to_erase;
	t_gc_node	*temp_next;
	t_gc_node	*temp_prev;

	node_to_erase = ((t_gc_node *)(*ptr) - 1);
	if (node_to_erase->prev == NULL)
	{
		gc->first_node = node_to_erase->next;
	}
	else
	{
		node_to_erase->prev->next = node_to_erase->next;
	}
	if (node_to_erase->next == NULL)
	{
		gc->last_node = node_to_erase->prev;
	}
	else
	{
		node_to_erase->next->prev = node_to_erase->prev;
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