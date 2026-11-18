#include<stdio.h>
#include<unistd.h>
#include<mqueue.h>
#include<sys/wait.h>
int main(){

    mqd_t mq;
    // unsigned int priority;
    // char msg[25];
    struct mq_attr attr;

    attr.mq_maxmsg =5;
    attr.mq_msgsize =25;
    mq=mq_open("/myqueue22",O_CREAT | O_WRONLY,0666,&attr);
    if(mq==(mqd_t)-1){
        perror("mq_queue open");
        return 1;
    }
    mq_send(mq,"low",4,2);
    mq_send(mq,"high",5,4);
    mq_send(mq,"medium",7,3);
    mq_send(mq,"urgent",7,5);
    mq_send(mq,"normal",7,1);

    printf("sender send data succesfully\n");

    mq_close(mq);
    return 0;
}