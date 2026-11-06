#include "ft_malloc.h"
#include <pthread.h>
#include <stdint.h>

// Points to the first allocated zone header.
static t_zone *g_heap = NULL;
// static pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;

#define TINY 1
#define SMALL 2
#define LARGE 3
#define ALIGN16(n) (((n) + 15) & ~(size_t)15)



//tricks to store the free bit into the aligned size.
//Technicaly breaks the exemple in the subject, but idc maybe i can be a cool kid.
#define FREE_BIT 1UL

#define GET_SIZE(h)     ((h)->size & ~(size_t)15)
#define IS_FREE(h)      ((h)->size & FREE_BIT)
#define SET_FREE(h)     ((h)->size |= FREE_BIT)
#define SET_USED(h)     ((h)->size &= ~FREE_BIT)


// Introducing "ft_" in front of each function while coding them

int get_alloc_type(size_t size) {
    int alloc_type;
    if (size <= 128) {
        alloc_type = TINY;
    } else if (size <= 4096) {
        alloc_type = SMALL;
    } else {
        alloc_type = LARGE;
    }
    return alloc_type;
}

void *ft_malloc(size_t size) {
    if (size == 0 || size > SIZE_MAX - 15) {
        return NULL;
    }

    // Get the type of allocation
    int alloc_type = get_alloc_type(size);

    // I should look if there is already an allocation of this caliber that exists.
    // so theres already at least one other allocation
    if (g_heap && alloc_type != LARGE) {
        t_zone *cur = g_heap;

        while (cur->next) {
            if (cur->type == alloc_type && cur->used_count < ALLOCS_PER_ZONE) {
                // we can pick the first available zone here and call it a day.
                t_block *header = cur + sizeof(t_zone);
                //Fuck the linked list we just advance one by one.

                if (header->free) {
                    header->free = false;
                    cur->used_count++;
                    return header + 1;
                }
            }
            cur = cur->next;
        }
    }

    size_t pages = (size + PAGE_SIZE - 1) / PAGE_SIZE; // tkt
    size_t page_len = pages * PAGE_SIZE + sizeof(t_block);
    printf("%lu\n", pages);

    void *ptr = mmap(NULL, page_len, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        return NULL;
    }

    // Lets pretend this is the case where nothing has been allocated yet.

    if (!g_heap) {
        g_heap = (t_zone *)ptr;
        *g_heap = (t_zone){
            .next = NULL,
            // .prev = NULL,
            .total_size = page_len,
            .type = alloc_type,
            .used_count = 1,
        };
    }

    // Returning the start of the usable memory.
    return ptr + sizeof(t_zone) + sizeof(t_block);
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