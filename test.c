#include "ft_malloc.h"

#define ALLOC_SIZE 4000

int main(void) {

    char *ptr = ft_malloc(ALLOC_SIZE);

    for (int i = 0; i < ALLOC_SIZE; i++) {
        printf("%X", ptr[i]);
    }

    struct rlimit rl;
    getrlimit(RLIMIT_AS, &rl);
    printf("LIMIT: soft: %lu, hard: %lu\n", (unsigned long)rl.rlim_cur, (unsigned long)rl.rlim_max);

    t_block *metadata = (t_block *)ptr - 1;

    ft_printf("Block address: %p\n", metadata);
    ft_printf("Size: %u bytes\n", (unsigned int)metadata->size);
    ft_printf("Free: %s\n", metadata->free ? "yes" : "no");
    ft_printf("Next: %p\n", metadata->next);
    ft_printf("-------------------------\n");

    return 0;
}

// int fd = open("README.MD", O_RDWR);
// struct stat sb;

// if (fstat(fd, &sb) == -1) {
//     perror("Could not get file size");
// }
// printf("the size of a page is %ld\n", sysconf(_SC_PAGESIZE));
// char *mapped_memory = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, fd, 0);
// if (mapped_memory == MAP_FAILED) {
//     perror("mmap failed for some reason");
//     return 1;
// }

// for (int i = 0; i < sb.st_size; i++) {
//     printf("%c", mapped_memory[i]);
//     mapped_memory[i] = '5';
// }
// printf("\n");
// printf("The size of the mapped memory is %lu\n", sb.st_size);

// munmap(mapped_memory, sb.st_size);