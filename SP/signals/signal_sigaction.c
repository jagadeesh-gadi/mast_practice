// both signal and sigaction in on program
#include<stdio.h>
#include<signal.h>
#include<unistd.h>

int count =0;
void signal_handler(int sig){
    printf("signal (%d) : signal received :: %d \n",count ,sig);
}
void sigaction_details(int sig,siginfo_t *info,void *context){
    (void) context;
    printf("sigaction () : received : %d \n",sig);
    printf("sender pid :: %d \n",info->si_pid);
}
int main(){
    signal(SIGINT,signal_handler);

    struct sigaction action ={0};
    action.sa_sigaction=sigaction_details;
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1,&action,NULL);
    printf("process id :: %d\n",getpid());
    printf("wating for SAIUSR1.....\n");
    while(1)
    pause();
return 0;
}