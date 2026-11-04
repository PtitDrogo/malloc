#include "ft_malloc.h"
#include <pthread.h>

static t_block *g_heap = NULL;
// static pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;

#define TINY 1
#define SMALL 2
#define LARGE 3

// Introducing "ft_" in front of each function while coding them

void *ft_malloc(size_t size) {
    if (size == 0) {
        return NULL;
    }

    // Get the type of allocation
    //  int alloc_type;
    //  if (size <= 128) {
    //      alloc_type = TINY;
    //  } else if (size <= 4096) {
    //      alloc_type = SMALL;
    //  } else {
    //      alloc_type = LARGE;
    //  }

    size_t pages = (size + PAGE_SIZE - 1) / PAGE_SIZE; // tkt
    printf("%lu\n", pages);

    size_t page_len = pages * PAGE_SIZE + sizeof(t_block);

    void *ptr = mmap(NULL, page_len, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        return NULL;
    }

    if (!g_heap) {
        g_heap = (t_block *)ptr;
        *g_heap = (t_block){
            .size = size,
            .free = false,
            .next = NULL,
        };
    } else {
        t_block *cur = g_heap;

        while (cur->next)
            cur = cur->next;

        cur->next = ptr;
        *cur->next = (t_block){
            .size = size,
            .free = false,
            .next = NULL,
        };
    }

    return ptr + sizeof(t_block);
}

void ft_free(void *ptr) {
    // I love freeing memory !! Wahoo !!
    (void)ptr;
}

void *ft_realloc(void *ptr, size_t size) {
    (void)ptr;
    (void)size;
    return (NULL);
}

void ft_show_alloc_mem(void) {
    t_block *cur = g_heap;

    ft_printf("g_heap ptr address %p\n", g_heap);

    while (cur) {
        ft_printf("Block address: %p\n", cur);
        ft_printf("Size: %zu bytes\n", cur->size);
        ft_printf("Free: %s\n", cur->free ? "yes" : "no");
        ft_printf("Next: %p\n", cur->next);
        ft_printf("-------------------------\n");

        cur = cur->next;
    }
}