#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int status;
    pid_t ret;

    pid = fork();

    if (pid == -1)
    {
        perror("fork");
        return 1;
    }

    if (pid == 0)
    {
        printf("Child: running...\n");
        sleep(50);
        printf("Child: terminating\n");
        exit(0);
    }
    else
    {
        printf("Parent: checking child...\n");

        ret = waitpid(pid, &status, WNOHANG);

        if (ret == 0)
        {
            printf("Child is still running\n");
        }
        else if (ret == pid)
        {
            printf("Child has terminated\n");
        }
    }

    return 0;
}