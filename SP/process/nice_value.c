#include <stdio.h>
#include <unistd.h>
int main()
{
    printf("pid :: %d\n", getpid());
    while (1)
    {
        printf("Runnig ....\n");
        sleep(2);
    }

    return 0;
}