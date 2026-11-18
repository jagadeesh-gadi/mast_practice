#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void handler(int sig){
 
 if(sig == SIGTERM)
    printf("sigterm received from SIGTERM : %d \n",sig);
else if
printf("sigterm received from  :  %d \n",sig);
}
int main(){
    signal(SIGTERM,handler);
    signal(SIGUSR1,handler);
signal(SIGFPE,handler);
    printf("get pid : %d \n",getpid());
    while(1)
    // pause();
 sleep(10);
    return 0;
}