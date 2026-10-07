// Copy On Write (COW)

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int var = 10;

    printf("Before fork:\n");
    printf("var = %d\n", var);

    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork failed");
        return 1;
    }

    if (pid == 0)
    {
        // Child
        printf("\nChild before modification:\n");
        // printf("var = %d\n", var);
        printf("before PID: %d, &var = %p, var = %d\n",
               getpid(), (void *)&var, var);

        var = 20;

        printf("Child after modification:\n");
        // printf("var = %d\n", var);
        printf("after PID: %d, &var = %p, var = %d\n",
               getpid(), (void *)&var, var);
    }
    else
    {
        // Parent
        wait(NULL);

        printf("\nParent after child modification:\n");
        printf("var = %d\n", var);
        printf("PID: %d, &var = %p, var = %d\n",
               getpid(), (void *)&var, var);
    }

    return 0;
}