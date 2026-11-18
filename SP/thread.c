#include <stdio.h>
#include <pthread.h>

void *task(void *arg)
{
    while(1){
    printf("Thread is running\n");
    // sleep(20);
}
    return NULL;
}

int main(void)
{
    pthread_t t;

    pthread_create(&t, NULL, task, NULL);

    pthread_join(t, NULL);

    printf("Main function finished\n");

    return 0;
}