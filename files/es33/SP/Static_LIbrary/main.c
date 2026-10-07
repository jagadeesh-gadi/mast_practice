#include <stdio.h>
#include "my_math.h"

int main()
{
    int x = add(10, 20);
    int y = subtract(20, 10);

    printf("Addition = %d\n", x);
    printf("Subtraction = %d\n", y);

    return 0;
}
