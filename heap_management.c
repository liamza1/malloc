/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstreak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 09:20:11 by lstreak           #+#    #+#             */
/*   Updated: 2018/06/25 09:20:12 by lstreak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memoryallocation.h"

int		search_pool(void *ptr, t_meta *block, t_pool *pool)
{
	t_meta	*cur;

	if (block && pool)
	{
		while (pool)
		{
			cur = pool->start;
			while (cur)
			{
				if ((((void*)cur) + sizeof(t_meta)) == ptr)
					return (1);
				else if (cur)
					cur = cur->next;
			}
			pool = pool->next;
		}
	}
	return (0);
}

void	*realloc_block(t_meta *block, size_t size)
{
	if (size <= (block->pool->max_block_size - sizeof(t_meta)) &&
	block->next->free == 1)
	{
		block->size += block->next->size + sizeof(t_meta);
		block->next = block->next->next;
		block->pool->max_allocs--;
		return (alloc_blocks(size, block));
	}
	else
	{
		block->free = 1;
		block->pool->cur_free++;
		return (malloc(size));
	}
}

void	*alloc_blocks(size_t size, t_meta *block)
{
	t_meta	*temp;
	int		leftover;
	void	*ptr;

	if (block)
	{
		leftover = (int)block->size - (int)size;
		block->free = 0;
		ptr = (void*)block + sizeof(t_meta);
		if ((leftover - (int)sizeof(t_meta)) > 0)
		{
			block->pool->max_allocs++;
			block->size = size;
			temp = block->next;
			block->next = (t_meta*)(block + (size + sizeof(t_meta)));
			block->next->size = leftover - sizeof(t_meta);
			block->next->next = temp;
			block->next->pool = block->pool;
			block->next->free = 1;
		}
		else
			block->pool->cur_free--;
		return (ptr);
	}
	return (NULL);
}

t_meta	*find_free_blocks(t_pool **pool, size_t size)
{
	t_pool	*cur_p;
	t_meta	*cur_m;
	int		i;

	i = -1;
	cur_p = *pool;
	while (cur_p->prev)
		cur_p = cur_p->prev;
	while (cur_p)
	{
		if (cur_p->cur_free > 0)
		{
			cur_m = cur_p->start;
			while (cur_m)
			{
				if (size <= cur_m->size && cur_m->free == 1)
					return (cur_m);
				cur_m = cur_m->next;
			}
		}
		cur_p = cur_p->next;
	}
	return (extend_heap(pool));
}

t_meta	*find_pre_blocks(t_meta *block, t_pool *pool)
{
	t_meta	*cur;

	cur = pool->start;
	while (cur)
	{
		if (cur->next == block)
			return (cur);
		else
			cur = cur->next;
	}
	return (NULL);
}
