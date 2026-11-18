#include<stdio.h>
#include<unistd.h>
#include<sched.h>
#include<pthread.h>

pthread_spinlock_t lock;
void *holder(void *args){
    printf("Holder : Acurring sprin lock \n");
    pthread_spin_lock(&lock);
    printf("Holder : lock acquried : holding 45 seconds\n");
    sleep(45);
    pthread_spin_unlock(&lock);

    printf("Holder : lock released  \n");
    return NULL;
}
void  *waiter(void *args){
    sleep(2);
    printf("Waiting : trying to acquire spin lock\n");
    pthread_spin_lock(&lock);
    printf("Waiting : lock acquried \n");
    pthread_spin_unlock(&lock);
     printf("wating :: lock realased \n");
    return NULL;
}

int main(){
    pthread_t t1,t2;
    setvbuf(stdout,NULL,_IONBF,0);
    pthread_spin_init(&lock,PTHREAD_PROCESS_PRIVATE);
    pthread_create(&t1,NULL,holder,NULL);
    pthread_create(&t2,NULL,waiter,NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_spin_destroy(&lock);
    printf("main :: program compeleted \n");
    return 0;

}