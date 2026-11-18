#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("process running...\n");
    printf("getpid :: %d\n", getpid());
    printf("getppid :: %d\n", getppid());
    sleep(2);
    return 0;
}