#include <stdio.h>

int main()
{
    printf("getid  :: %d\n", getpid());

    printf("parent is running\n");
    sleep(20);

    printf("parent woke up\n");
    return 0;
}