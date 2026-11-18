#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    int stack_var = 10;

    // Allocate 1 MiB of heap memory
    int *heap_var = malloc(1024 * 1024);

    if (heap_var == NULL) {
        perror("malloc");
        return 1;
    }

    *heap_var = 20;

    printf("PID: %d\n", (int)getpid());

    printf("Stack variable address: %p\n", (void *)&stack_var);

    printf("Heap pointer address (stack): %p\n", (void *)&heap_var);

    printf("Heap allocated address: %p\n", (void *)heap_var);

    printf("Stack variable value: %d\n", stack_var);

    printf("Heap variable value: %d\n", *heap_var);

    printf("Inspect the process using /proc/%d/maps\n", (int)getpid());

    printf("Press Enter to exit...\n");
    getchar();

    free(heap_var);

    return 0;
}
