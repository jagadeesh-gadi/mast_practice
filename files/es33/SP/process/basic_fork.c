#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("before fork process \n");
    fork();
    printf("hello from fork process \n");
    return 0;
}