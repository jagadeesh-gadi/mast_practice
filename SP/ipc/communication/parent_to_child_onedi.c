
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    int fd[2];
    pipe(fd);

    if (fork() == 0)
    {
        // Child process
        close(fd[0]);

        char msg[] = "hello jagadeesh how are you";

        write(fd[1], msg, strlen(msg));

        close(fd[1]);
    }
    else
    {
        // Parent process
        close(fd[1]);

        char buff[20];

        ssize_t h = read(fd[0], buff, sizeof(buff) - 1);

        printf("Return value: %zd\n", h);

        if (h > 0)
        {
            buff[h] = '\0';
            printf("Parent received: %s\n", buff);
        }

        close(fd[0]);

        wait(NULL);
    }

    return 0;
}

