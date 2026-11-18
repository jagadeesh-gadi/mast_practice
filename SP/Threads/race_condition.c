#include <stdio.h>
#include <pthread.h>

int count = 0;
//pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *task(void *arg)
{
    for (int i = 0; i < 100000; i++)
    {
        // pthread_mutex_lock(&lock);
        count++;
        //  pthread_mutex_unlock(&lock);
    }

    return NULL;
}

int main(void)
{
    pthread_t t1, t2;

    pthread_create(&t1, NULL, task, NULL);
    pthread_create(&t2, NULL, task, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Count = %d\n", count);

    return 0;
}