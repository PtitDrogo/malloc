#ifndef MALLOC_H
#define MALLOC_H

#define _DEFAULT_SOURCE

#include "libft.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <unistd.h>

#define PAGE_SIZE 4096


typedef struct s_block {
    size_t size;          /* usable size (without the header) */
    bool free;            /* 1 if free, 0 if in use */
    struct s_block *next; /* next block in the list */
    // struct s_block *prev; /* previous block (makes merging easy) */
} t_block;

void *ft_malloc(size_t size);
void ft_free(void *ptr);
void *ft_realloc(void *ptr, size_t size);
void ft_show_alloc_mem(void);

#endif