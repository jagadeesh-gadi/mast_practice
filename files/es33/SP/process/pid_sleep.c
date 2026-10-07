#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main()
{
    printf("getpid == %d\n", getpid());

    sleep(20);

    write(1, "hello", 3);

    return 0;
}