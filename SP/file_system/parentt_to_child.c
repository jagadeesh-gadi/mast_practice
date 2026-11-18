
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int fd[2];
    int num, received;
    pid_t pid;

    pipe(fd);

    pid = fork();

    if (pid > 0)
    {
        // Parent process
        close(fd[0]);

        printf("Parent: Enter a number: ");
        scanf("%d", &num);

        write(fd[1], &num, sizeof(num));

       // close(fd[1]);
        wait(NULL);
    }
    else if (pid == 0)
    {
        // Child process
      //  close(fd[1]);

        read(fd[0], &received, sizeof(received));

        printf("Child received number: %d\n", received);

        close(fd[0]);
    }

    return 0;
}


