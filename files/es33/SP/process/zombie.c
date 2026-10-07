#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
int main()
{
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("get pid failed \n");
        return 1;
    }
    if (pid == 0)
    {
        printf("child :: teriminatiing\n");
        exit(0);
    }
    else
    {
        //  wait(NULL);  //the parent collects the child's termination status, and the child will not remain as a zombie
        printf("parent getid  :: %d\n", getpid());

        printf("child pid :: %d \n", pid);
        sleep(30);
    }
    return 0;
}