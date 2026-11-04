#ifndef MALLOC_H
#define MALLOC_H

#include "libft.h"
#include <stdbool.h>
#include <stddef.h>

typedef struct s_block {
    size_t size;          /* usable size (without the header) */
    bool free;            /* 1 if free, 0 if in use */
    struct s_block *next; /* next block in the list */
    struct s_block *prev; /* previous block (makes merging easy) */
} t_block;

void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);
void show_alloc_mem(void);

#endif