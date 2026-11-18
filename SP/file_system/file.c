
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int fd[2];

    pipe(fd);

    printf("Read FD  = %d\n", fd[0]);
    printf("Write FD = %d\n", fd[1]);

    return 0;
}

