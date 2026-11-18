#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include<sys/wait.h>
int main()
{

    pid_t pid = fork();
    if (pid == -1)
    {
        perror("faild pid");
        return 1;
    }
    if (pid == 0)
    {
        printf("child process is running .....\n");
        // sleep(5);
        printf("getid  :: %d\n", getpid());
        printf("getppid :: %d\n", getppid());
        printf("\n");
    }
    else
    {
        printf("parent process running .... \n");
        printf("getid  :: %d\n", getpid());
        printf("getppid :: %d\n", getppid());
        printf("child pid :: %d \n", pid);
        printf("\n");
    }

    return 0;
}