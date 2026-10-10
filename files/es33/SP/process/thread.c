
#include <stdio.h>
#include <pthread.h>

void *task1(void *arg)
{
    printf("Thread 1 is executing\n");
    return NULL;
}

void *task2(void *arg)
{
    printf("Thread 2 is executing\n");
    return NULL;
}

int main()
{
    pthread_t t1, t2;

    printf("Main thread starts\n");

    pthread_create(&t1, NULL, task1, NULL);
    pthread_create(&t2, NULL, task2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Main thread ends\n");

    return 0;
}