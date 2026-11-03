#include "malloc.h"

void	*malloc(size_t size)
{
	(void)size;
	return (NULL);
}

void	free(void *ptr)
{
	(void)ptr;
}

void	*realloc(void *ptr, size_t size)
{
	(void)ptr;
	(void)size;
	return (NULL);
}

void	show_alloc_mem(void)
{
    return;
}