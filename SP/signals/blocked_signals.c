#include<stdio.h>
#include<unistd.h>
#include<signal.h>
void handler(int sig){
    printf("sigint handler started\n");
    // fflush(stdout);
    sleep(15);
    printf("sigint handler finished\n");
    // fflush(stdout);
}
int main(){
    struct sigaction action ={0};
    action.sa_handler =handler;
    sigemptyset(&action.sa_mask);

    // blocked there signals during the sigint handler
    sigaddset(&action.sa_mask,SIGTERM);
    sigaddset(&action.sa_mask,SIGUSR1);
    action.sa_flags =0;
    if(sigaction(SIGINT,&action,NULL)==-1){
        perror("sigaction failed \n");
        return 1;
    }
    printf("process id :: %d \n",getpid());
    printf("waiting for SIGINT .......\n");
    // fflush(stdout);
    while(1)
    pause();
return 0;
}
