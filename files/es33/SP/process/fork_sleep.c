#include <stdio.h>

int main()
{
    printf("getid  :: %d\n", getpid());
    while (1)
    {
        // printf("parent is running\n");
        sleep(2);
    }

    return 0;
}