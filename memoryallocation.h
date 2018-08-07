/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memoryallocation.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstreak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 09:19:35 by lstreak           #+#    #+#             */
/*   Updated: 2018/07/03 10:42:20 by lstreak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORYALLOCATION_H
# define MEMORYALLOCATION_H
# include <stdlib.h>
# include <unistd.h>
# include <sys/mman.h>
# include <sys/time.h>
# include <sys/resource.h>
# include "libft/libft.h"

# define ZONE_MAX_ALLOCS 100
# define TINY_PAGES_PER_BLOCK 1
# define SMALL_PAGES_PER_BLOCK 4
# define DATA_PTR
# define MMAP_ARGS PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0

typedef struct			s_meta
{
	size_t				size;
	struct s_meta		*next;
	struct s_pool		*pool;
	int					free;
}						t_meta;

typedef struct			s_pool
{
	size_t				max_allocs;
	size_t				cur_free;
	size_t				max_block_size;
	void				*pool;
	t_meta				*start;
	t_meta				*end;
	struct s_pool		*next;
	struct s_pool		*prev;
}						t_pool;

typedef struct			s_zones
{
	t_pool				*tiny;
	t_pool				*small;
	t_pool				*large;
	size_t				mapped;
	size_t				rlimit;
}						t_zones;

t_zones					*g_base;

void					free(void *ptr);
void					*malloc(size_t size);
void					*realloc(void *ptr, size_t size);
void					show_alloc_mem(void);
void					show_alloc_mem_ex(void);

void					p_mappool(t_pool *pool, int space_size);
void					map_pool(t_pool **p, int space_size,
						size_t s, size_t i);
void					create_heap(size_t pg_size);
t_meta					*extend_heap(t_pool **cur);
void					*alloc_blocks(size_t size, t_meta *block);
t_meta					*find_free_blocks(t_pool **pool, size_t size);
t_meta					*find_pre_blocks(t_meta *block, t_pool *pool);
void					*large_map(size_t size);
int						search_pool(void *ptr, t_meta *block, t_pool *pool);
void					*realloc_block(t_meta *block, size_t size);
void					print_pool(t_pool **p, int all);
void					print_meta(t_meta **c);
void					print_stats(t_pool *pool, size_t num_used);
void					defrag_pool(t_pool **p);

#endif
