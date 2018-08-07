
#include "memoryallocation.h"

int		main()
{
	void	*test;
	char	*line;
	line = NULL;
	test = NULL;

	ft_putendl("->Test realloc & free with invalid pointer before mallocing");
//	realloc(test, 1);
	free(test);

	ft_putendl("\n->Malloc'ing an int");
	int *p = (int*)malloc(sizeof(int));
	ft_putendl("Printing Pools:");
	show_alloc_mem();

	ft_putendl("\n->Assigning Value");
	*p = 42;
	ft_putendl("Printing Pools:");
	show_alloc_mem();

	ft_putendl("\n->Re-test realloc & free with invalid pointer");
//	realloc(test, 1);
	free(test);

	ft_putendl("\n->Malloc'ing more ints");
	int *q = (int*)malloc(sizeof(int));
	int *r = (int*)malloc(sizeof(int));
	int *s = (int*)malloc(sizeof(int));
	ft_putendl("Printing Pools:");
	show_alloc_mem();

	ft_putendl("\n->Assigning Values:");
	*q = 42;
	*r = 42;
	*s = 42;
	ft_putendl("Printing Pools:");
	show_alloc_mem();

	ft_putendl("\n->Freeing 1 int:");
	free(p);
	ft_putendl("Printing Pools:");
	show_alloc_mem();
	ft_putendl("\nHex Dump of Pools:");
	show_alloc_mem_ex();




	ft_putendl("\n->Malloc'ing a string");
	char *str = (char*)malloc(sizeof(char*) * 29);
	ft_strcpy(str, "It's Working! Its's Working!");
	ft_putstr("->Testing malloc'd string: ");
	ft_putendl(str);
	ft_putendl("Printing Pools:");
	show_alloc_mem();

	ft_putendl("\n->Re-alloc'ing the string");
	str = realloc(str, sizeof(char*) * 49);
	ft_strcat(str, " It's still Working!");
	ft_putstr("->Testing re-alloc'd string: ");
	ft_putendl(str);
	ft_putendl("Printing Pools:");
	show_alloc_mem();

	ft_putendl("\n->Malloc'ing junk in 'Small' pool");
	void *junk1 = malloc(8096);
	ft_putendl("Printing Pools:");
	show_alloc_mem();

	ft_putendl("\n->Malloc'ing junk in 'Large' pool");
	void *junk2 = malloc(32768);
	ft_putendl("Printing Pools:");
	show_alloc_mem();
	ft_putendl("\nHex Dump of Pools:");
	show_alloc_mem_ex();




	ft_putendl("\n->Re-alloc'ing the large junk");
	junk2 = realloc(junk2, 65536);
	ft_putendl("Printing Pools:");
	show_alloc_mem();

	ft_putendl("\n->Freeing all:");
	free(q);
	free(r);
	free(s);
	free(str);
	free(junk1);
	free(junk2);
	ft_putendl("Printing Pools:");
	show_alloc_mem();
	ft_putendl("\n\nHex Dump of Pools:");
	show_alloc_mem_ex();




	ft_putendl("\n\nLet's add ZONE_MAX_ALLOCS + 1 junk in each pool for the finale.");
	int num = ZONE_MAX_ALLOCS + 1;

	ft_putendl("\n->First we alloc our arrays for each zone, at the start of our tiny zone");
	void **arr1 = (void**)malloc(sizeof(void*) * num);
	void **arr2 = (void**)malloc(sizeof(void*) * num);
	void **arr3 = (void**)malloc(sizeof(void*) * num);
	ft_putendl("Printing Pools:");
	show_alloc_mem_ex();

	ft_putendl("\n->Now we populate the array for the tiny pool");
	int counter = -1;
	size_t size = (getpagesize() * TINY_PAGES_PER_BLOCK) - sizeof(t_meta);
	void *ptr;
	while (++counter < num)
	{
		ptr = (void*)malloc(size);
		arr1[counter] = ptr;
	}
	ft_putendl("Printing Pools:");
	show_alloc_mem();

	ft_putendl("\n->Next, the array for the small pool");
	counter = -1;
	size = (getpagesize() * SMALL_PAGES_PER_BLOCK) - sizeof(t_meta);
	while (++counter < num)
	{
		ptr = (void*)malloc(size);
		arr2[counter] = ptr;
	}
	ft_putendl("Printing Pools:");
	show_alloc_mem();

	ft_putendl("\n->Finally the large pool");
	counter = -1;
	size = 2 * (getpagesize() * SMALL_PAGES_PER_BLOCK) - sizeof(t_meta);
	while (++counter < num)
	{
		ptr = (void*)malloc(size);
		arr3[counter] = ptr;
	}
	ft_putendl("Printing Pools:");
	show_alloc_mem();
	ft_putendl("\n\nHex Dump of Pools:");
	show_alloc_mem_ex();




	ft_putendl("\n->Re-alloc the 42nd element of each array");
	size = 1 + (getpagesize() * TINY_PAGES_PER_BLOCK) - sizeof(t_meta);
	ft_putstr("Tiny Size: ");
	ft_putnendl(size);
	arr1[42] = realloc(arr1[42], size);
	size = 1 + (getpagesize() * SMALL_PAGES_PER_BLOCK) - sizeof(t_meta);
	ft_putstr("Small Size: ");
	ft_putnendl(size);
	arr2[42] = realloc(arr2[42], size);
	size = 4 * (getpagesize() * SMALL_PAGES_PER_BLOCK) - sizeof(t_meta);
	ft_putstr("Large Size: ");
	ft_putnendl(size);
	arr3[42] = realloc(arr3[42], size);
	ft_putendl("\n\nHex Dump of Pools:");
	show_alloc_mem_ex();




	ft_putendl("\n->Free the large pool");
	counter = -1;
	while (++counter < num)
		free(arr3[counter]);
	free(arr3);
	ft_putendl("Printing Pools:");
	show_alloc_mem();

	ft_putendl("\n->Free the small pool");
	counter = -1;
	while (++counter < num)
		free(arr2[counter]);
	free(arr2);
	ft_putendl("Printing Pools:");
	show_alloc_mem();

	ft_putendl("\n->Free the tiny pool");
	counter = -1;
	while (++counter < num)
		free(arr1[counter]);
	free(arr1);
	ft_putendl("Printing Pools:");
	show_alloc_mem();
	ft_putendl("\n\nHex Dump of Pools:");
	show_alloc_mem_ex();

	return (0);
}
