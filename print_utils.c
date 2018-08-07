/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstreak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 09:20:33 by lstreak           #+#    #+#             */
/*   Updated: 2018/06/25 09:20:34 by lstreak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memoryallocation.h"

void	print_meta(t_meta **c)
{
	t_meta	*cur;
	void	*meta_ptr;
	void	*data_ptr;

	cur = *c;
	meta_ptr = (void*)cur;
	data_ptr = meta_ptr + sizeof(t_meta);
	ft_putstr("META: ");
	ft_putptr(meta_ptr);
	ft_putstr(" - ");
	ft_putptr(data_ptr);
	ft_putstr(" : ");
	ft_putnbr((int)sizeof(t_meta));
	ft_putstr(" bytes\tFREE: ");
	if (cur->free == 1)
		ft_putstr("Yes\tDATA: ");
	else
		ft_putstr("No\tDATA: ");
}

void	print_data(t_meta **c)
{
	t_meta	*cur;
	void	*data_ptr;
	void	*next_ptr;

	cur = *c;
	data_ptr = (void*)cur + sizeof(t_meta);
	next_ptr = data_ptr + cur->size;
	ft_putptr(data_ptr);
	ft_putstr(" - ");
	ft_putptr(next_ptr);
	ft_putstr(" : ");
	ft_putnbr((int)cur->size);
	ft_putendl(" bytes");
}

void	print_pool(t_pool **p, int all)
{
	t_pool	*pool;
	t_meta	*cur;

	pool = *p;
	while (pool)
	{
		print_stats(pool, 0);
		cur = pool->start;
		while (cur)
		{
			if ((all == 0 && cur->free == 0) || (all == 1))
			{
				if (all == 1)
					print_meta(&cur);
				print_data(&cur);
			}
			cur = cur->next;
		}
		pool = pool->next;
	}
}

void	print_stats(t_pool *pool, size_t num_used)
{
	t_meta	*cur;

	cur = pool->start;
	num_used = pool->max_allocs - pool->cur_free;
	ft_putstr("Max allocs: ");
	if ((int)pool->max_allocs > 0)
	{
		ft_putnendl(pool->max_allocs);
		ft_putstr("Max block size: ");
		ft_putnendl(pool->max_block_size);
		ft_putstr("Max block space: ");
		ft_putnendl(pool->max_block_size - sizeof(t_meta));
		ft_putstr("Free Blocks : ");
		ft_putnendl(pool->cur_free);
		ft_putstr("Used Blocks: ");
		ft_putnendl(num_used);
	}
	else
		ft_putendl("Pool configured to be limited to rlimit");
}

void	defrag_pool(t_pool **p)
{
	t_pool	*pool;
	t_meta	*cur;

	pool = *p;
	while (pool)
	{
		cur = pool->start;
		while (cur && cur->next)
		{
			if (cur->free == 1 && cur->next->free == 1 && cur->size +
			cur->next->size <= cur->pool->max_block_size - sizeof(t_meta))
			{
				cur->size += cur->next->size + sizeof(t_meta);
				cur->next = cur->next->next;
				cur->pool->max_allocs--;
				cur->pool->cur_free--;
			}
			else
				cur = cur->next;
		}
		pool = pool->next;
	}
}
