#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void handler(int sig){
    printf("signed recieved :: %d\n",sig);
}

int main(){

    signal(SIGINT ,SIG_IGN);
    printf("signal ignored , ctrl +c \n");
    sleep(10);

    signal(SIGTERM ,handler);
    printf("signal handler , ctrl +c \n");
    sleep(20);

    signal(SIGINT ,SIG_DFL);
    printf("deafult action restored , ctrl +c \n");
    sleep(30);
    return 0;
}