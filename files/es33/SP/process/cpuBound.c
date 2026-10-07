#include <stdio.h>

int main()
{
    unsigned long int i = 0;
    while (1)
    {
        i++;
        i = i * 2 + 1;
        printf("%lu",i);
    }

    return 0;
}