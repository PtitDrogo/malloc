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

#define PAGE_SIZE sysconf(_SC_PAGESIZE) // Change this later so i dont syscall everytime ig.
#define ALLOCS_PER_ZONE 128

typedef struct s_block {
    size_t size; // asked for size (for realloc) //we can potentially just store the size if we are being hackermen.
    bool free;
} t_block;

typedef struct s_zone {
    struct s_zone *next;
    // struct s_zone *prev; //Not super sure I need it but zones are kinda free.
    size_t total_size; // passed to mmap
    size_t used_count;
    int type; // TINY/SMALL/LARGE
} t_zone;

void *ft_malloc(size_t size);
void ft_free(void *ptr);
void *ft_realloc(void *ptr, size_t size);
void ft_show_alloc_mem(void);

#endif