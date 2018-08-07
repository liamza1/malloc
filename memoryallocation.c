/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memoryallocation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstreak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 09:19:30 by lstreak           #+#    #+#             */
/*   Updated: 2018/07/03 10:42:05 by lstreak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memoryallocation.h"

void	*malloc(size_t size)
{
	void			*ptr;
	struct rlimit	rlim;

	if (!(g_base))
	{
		g_base = (t_zones*)mmap(0, sizeof(t_zones), MMAP_ARGS);
		getrlimit(RLIMIT_AS, &rlim);
		g_base->rlimit = (size_t)rlim.rlim_cur;
		create_heap((size_t)getpagesize());
	}
	if (g_base->tiny->start && g_base->small->start && size > 0)
	{
		if (size <= (g_base->tiny->max_block_size - sizeof(t_meta)))
			ptr = alloc_blocks(size, find_free_blocks(&g_base->tiny, size));
		else if (size <= (g_base->small->max_block_size - sizeof(t_meta)))
			ptr = alloc_blocks(size, find_free_blocks(&g_base->small, size));
		else
			ptr = large_map(size);
		if (ptr)
			return (ptr);
	}
	return (NULL);
}

void	*realloc(void *ptr, size_t size)
{
	void			*new_ptr;
	t_meta			*block;
	t_meta			*pre;

	new_ptr = NULL;
	if (g_base && ptr && size > 0 && ptr > (new_ptr + sizeof(t_meta)))
	{
		block = (t_meta*)(ptr - sizeof(t_meta));
		if (block->pool && ((search_pool(ptr, block, g_base->tiny) ||
		search_pool(ptr, block, g_base->small))))
			new_ptr = realloc_block(block, size);
		else if (block->pool && search_pool(ptr, block, g_base->large))
		{
			if ((pre = find_pre_blocks(block, g_base->large)))
				pre->next = block->next;
			else if (g_base->large->start == block)
				g_base->large->start = block->next;
			munmap((void*)block, sizeof(t_meta) + block->size);
			new_ptr = large_map(size);
		}
		else
			ft_putendl("Realloc: Pointer is not found in malloc address space");
	}
	return (new_ptr);
}

void	free(void *ptr)
{
	t_meta			*block;
	t_meta			*pre;

	if (g_base && ptr && ptr > (void*)(NULL + sizeof(t_meta)))
	{
		block = (t_meta*)(ptr - sizeof(t_meta));
		if (block->pool && ((search_pool(ptr, block, g_base->tiny) ||
		search_pool(ptr, block, g_base->small))))
		{
			block->free = 1;
			block->pool->cur_free++;
			defrag_pool(&block->pool);
		}
		else if (block->pool && search_pool(ptr, block, g_base->large))
		{
			if ((pre = find_pre_blocks(block, g_base->large)))
				pre->next = block->next;
			else if (g_base->large->start == block)
				g_base->large->start = block->next;
			munmap((void*)block, sizeof(t_meta) + block->size);
		}
		else
			ft_putendl("Free: Pointer is not found at malloc address space");
	}
}

void	show_alloc_mem(void)
{
	if (g_base)
	{
		ft_putstr("Tiny : ");
		ft_putpendl((void*)g_base->tiny->start);
		print_pool(&g_base->tiny, 0);
		ft_putstr("Small : ");
		ft_putpendl((void*)g_base->small->start);
		print_pool(&g_base->small, 0);
		if (g_base->large->start)
		{
			ft_putstr("Large : ");
			ft_putpendl((void*)g_base->large->start);
			print_pool(&g_base->large, 0);
		}
		else
			ft_putendl("No large zones have been malloc'd");
	}
}

void	show_alloc_mem_ex(void)
{
	if (g_base)
	{
		ft_putstr("Bytes Mapped ");
		ft_putnendl(g_base->mapped);
		ft_putstr("Bytes Limit: ");
		if (g_base->rlimit == RLIM_INFINITY)
			ft_putendl("sideway 8");
		else
			ft_putnendl(g_base->rlimit);
		ft_putstr("Tiny: ");
		ft_putpendl((void*)g_base->tiny->start);
		print_pool(&g_base->tiny, 1);
		ft_putstr("Small: ");
		ft_putpendl((void*)g_base->small->start);
		print_pool(&g_base->small, 1);
		if (g_base->large->start)
		{
			ft_putstr("\nLarge: ");
			ft_putpendl((void*)g_base->large->start);
			print_pool(&g_base->large, 1);
		}
		else
			ft_putendl("\nNO large zone malloc'd");
	}
}
