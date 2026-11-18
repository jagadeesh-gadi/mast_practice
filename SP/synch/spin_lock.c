#include<stdio.h>
#include<pthread.h>
#define n 1000000
int counter =0;
pthread_spinlock_t lock;
void *increment(void *arg){
    for(int i=0;i<n;i++){
        pthread_spin_lock(&lock);
        counter++;
         pthread_spin_unlock(&lock);
    }
    return NULL;
}

int main(){
pthread_t t1,t2;
pthread_spin_init(&lock,PTHREAD_PROCESS_PRIVATE);
pthread_create(&t1,NULL,increment,NULL);
pthread_create(&t2,NULL,increment,NULL);
pthread_join(t1,NULL);
pthread_join(t2,NULL);
printf("experted counter :: %d\n",2*n);
printf("actuall counter :: %d\n",counter);
pthread_spin_destroy(&lock);
return 0;
}