#include<stdio.h>
#include<signal.h>
#include<unistd.h>
int count=0;
void handler(int sig)
{
    count++;
    printf("Count = %d | Caught signal = %d\n", count, sig);
}

int main(){
   
    struct  sigaction action;
    action.sa_handler=handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags=0;
    sigaction(SIGINT,&action,NULL);
    printf("process id : %d\n",getpid());
    while(1)
    // pause();
sleep(10);
return 0;
}