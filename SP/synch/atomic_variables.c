
#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>

#define N 100000

atomic_int counter = 0;

void *increment(void *arg)
{
    for (int i = 0; i < N; i++)
    {
        atomic_fetch_add(&counter, 1);
    }

    return NULL;
}

int main(void)
{
    pthread_t t1, t2;

    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Expected: %d\n", 2 * N);
    printf("Actual:   %d\n", atomic_load(&counter));

    return 0;
}
