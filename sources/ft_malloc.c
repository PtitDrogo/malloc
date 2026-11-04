#include "ft_malloc.h"
#include <pthread.h>

static t_block *g_heap = NULL;
static pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;

void *malloc(size_t size) {
    (void)size;
    return (NULL);
}

void free(void *ptr) { (void)ptr; }

void *realloc(void *ptr, size_t size) {
    (void)ptr;
    (void)size;
    return (NULL);
}

void show_alloc_mem(void) {
    ft_printf("g_heap ptr address %p\n", g_heap);
    ft_printf("g_heap ptr address %p\n", g_lock);
    return;
}