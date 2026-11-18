
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    int fd[2];
    char str[100];

    pipe(fd);

    if (fork() == 0)
    {
        // Child process
        close(fd[0]);

        printf("Child: Enter a string: ");
        fgets(str, sizeof(str), stdin);

        write(fd[1], str, strlen(str) + 1);
        
        //close(fd[1]);
    }
    else
    {
        // Parent process
        //close(fd[1]);

        read(fd[0], str, sizeof(str));

        printf("Parent received string: %s", str);

        close(fd[0]);
       sleep(20);
        wait(NULL);
    }

    return 0;
}

