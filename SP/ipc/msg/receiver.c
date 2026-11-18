#include<stdio.h>
#include<unistd.h>
#include<mqueue.h>
#include<sys/wait.h>
#include <fcntl.h>
int main(){
mqd_t mq;
char bud[30];
unsigned int priority;

mq=mq_open("/myqueue22",O_RDONLY);

if(mq==(mqd_t)-1){
    perror("my_open failed\n");
    return 1;
}

for(int i=0;i<5;i++){
    if(mq_receive(mq,bud,sizeof(bud),&priority)==-1){
        perror("mq_receive failed");
        mq_close(mq);
        return 1;
    }
    printf("message :: %s || priority :: %u\n",bud,priority);
}
mq_close(mq);
mq_unlink("/myqueue22");
return 0;
}

// #include <stdio.h>
// #include <unistd.h>
// #include <mqueue.h>
// #include <fcntl.h>
// #include <sys/wait.h>

// int main(void)
// {
//     mqd_t mq;
//     char bud[26];
//     unsigned int priority;

//     // Open an existing message queue for reading
//     mq = mq_open("/myqueue22", O_RDONLY);

//     if (mq == (mqd_t)-1) {
//         perror("mq_open failed");
//         return 1;
//     }

//     for (int i = 0; i < 5; i++) {
//         ssize_t n = mq_receive(mq, bud, 25, &priority);

//         if (n == -1) {
//             perror("mq_receive failed");
//             mq_close(mq);
//             return 1;
//         }

//         // Add string terminator
//         bud[n] = '\0';

//         printf("message :: %s || priority :: %u\n",
//                bud, priority);
//     }

//     mq_close(mq);

//     // Remove the queue name after use, if intended
//     if (mq_unlink("/myqueue22") == -1) {
//         perror("mq_unlink failed");
//         return 1;
//     }

//     return 0;
// }
