// normal state waitpid 0 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int status;

    pid = fork();

    if (pid == -1)
    {
        perror("fork");
        return 1;
    }

    if (pid == 0)
    {
        printf("Child: PID = %d\n", getpid());
        sleep(5);
        printf("Child: terminating\n");
        exit(10);
    }
    else
    {
        printf("Parent: waiting for child...\n");

        waitpid(pid, &status, 0);

        printf("Parent: child terminated\n");

        if (WIFEXITED(status))
        {
            printf("Child exit status = %d\n",
                   WEXITSTATUS(status));
        }
    }

    return 0;
}