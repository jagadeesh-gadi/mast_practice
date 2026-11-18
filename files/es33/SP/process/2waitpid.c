#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
int main()
{
    pid_t child1, child2;
    int status;

    child1 = fork();
    if (child1 == 0)
    {
        printf("child 1 pid :: %d\n", getpid());
        sleep(2);
        printf("child teriminated\n");
        return 10;
    }
    child2 = fork();
    if (child2 == 0)
    {
        printf("child 2 pid :: %d\n", getpid());
        sleep(2);
        printf("child teriminated\n");
        return 20;
    }
    printf("\nParent waiting for child 1...\n");
    waitpid(child1, &status, 0);
    printf("Child 1 completed\n");

    printf("\nParent waiting for child 2...\n");
    waitpid(child2, &status, 0);
    printf("Child 2 completed\n");

    printf("\nBoth are terminated\n");
    // printf("both are teriminated\n");
    return 0;
}
