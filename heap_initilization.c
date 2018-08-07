/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_initilization.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstreak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 09:19:56 by lstreak           #+#    #+#             */
/*   Updated: 2018/06/25 09:19:58 by lstreak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memoryallocation.h"

void	map_pool(t_pool **p, int space_size, size_t s, size_t i)
{
	t_meta	*cur;
	t_meta	*next;
	t_pool	*pool;

	pool = *p;
	g_base->mapped += s;
	cur = (t_meta*)pool->pool;
	cur->size = (size_t)space_size;
	cur->next = NULL;
	cur->pool = pool;
	cur->free = 1;
	pool->start = cur;
	while (++i <= pool->max_allocs)
	{
		if (i != pool->max_allocs)
			next = (t_meta*)((char*)cur + (size_t)space_size + sizeof(t_meta));
		next->size = (size_t)space_size;
		next->next = NULL;
		cur->next = next;
		cur->pool = pool;
		cur->free = 1;
		cur = cur->next;
	}
	pool->end = cur;
}

void	p_mappool(t_pool *pool, int space_size)
{
	size_t	s;
	size_t	i;

	i = 0;
	s = pool->max_block_size * pool->max_allocs;
	if ((s + g_base->mapped <= g_base->rlimit) ||
	(g_base->rlimit == RLIM_INFINITY))
	{
		if ((char*)(pool->pool = mmap(0, s, MMAP_ARGS)) == MAP_FAILED)
			ft_putendl("MMAP failed");
		else
		{
			map_pool(&pool, space_size, s, i);
			pool->end->next = NULL;
		}
	}
}

void	create_heap(size_t pg_size)
{
	g_base->tiny = (t_pool*)mmap(0, sizeof(t_pool), MMAP_ARGS);
	g_base->small = (t_pool*)mmap(0, sizeof(t_pool), MMAP_ARGS);
	g_base->large = (t_pool*)mmap(0, sizeof(t_pool), MMAP_ARGS);
	g_base->mapped = sizeof(t_zones) + (sizeof(t_pool) * 3);
	if (g_base->tiny && g_base->small)
	{
		g_base->tiny->max_allocs = (size_t)ZONE_MAX_ALLOCS;
		g_base->tiny->cur_free = (size_t)ZONE_MAX_ALLOCS;
		g_base->tiny->max_block_size = (size_t)TINY_PAGES_PER_BLOCK * pg_size;
		g_base->tiny->next = NULL;
		g_base->tiny->prev = NULL;
		p_mappool(g_base->tiny, g_base->tiny->max_block_size - sizeof(t_meta));
		g_base->small->max_allocs = ZONE_MAX_ALLOCS;
		g_base->small->cur_free = ZONE_MAX_ALLOCS;
		g_base->small->max_block_size = SMALL_PAGES_PER_BLOCK * pg_size;
		g_base->small->next = NULL;
		g_base->small->prev = NULL;
		p_mappool(g_base->small,
		g_base->small->max_block_size - sizeof(t_meta));
		g_base->large->prev = NULL;
		g_base->large->next = NULL;
		g_base->large->max_allocs = -1;
		g_base->large->cur_free = -1;
		g_base->large->max_block_size = -1;
	}
}

t_meta	*extend_heap(t_pool **cur)
{
	t_pool	*pool;
	t_pool	*next;

	pool = *cur;
	if (sizeof(t_pool) + g_base->mapped <= g_base->rlimit)
	{
		next = (t_pool*)mmap(0, sizeof(t_pool), MMAP_ARGS);
		pool->next = next;
		g_base->mapped += sizeof(t_pool);
		if (pool->next)
		{
			pool->next->max_allocs = ZONE_MAX_ALLOCS;
			pool->next->cur_free = ZONE_MAX_ALLOCS;
			pool->next->max_block_size = pool->max_block_size;
			pool->next->next = NULL;
			pool->next->prev = pool;
			p_mappool(pool->next, pool->next->max_block_size - sizeof(t_meta));
			return (pool->next->start);
		}
	}
	return (NULL);
}

void	*large_map(size_t size)
{
	t_meta	*last;

	if (g_base->large && g_base->mapped + size +
	sizeof(t_meta) <= g_base->rlimit)
	{
		last = (t_meta*)mmap(0, size + sizeof(t_pool), MMAP_ARGS);
		g_base->mapped += size + sizeof(t_meta);
		last->size = size;
		last->next = NULL;
		last->free = 0;
		if (!(g_base->large->start && g_base->large->end))
			g_base->large->start = last;
		else
			g_base->large->end->next = last;
		last->pool = g_base->large;
		g_base->large->end = last;
		return ((void*)(last) + sizeof(t_meta));
	}
	return (NULL);
}
