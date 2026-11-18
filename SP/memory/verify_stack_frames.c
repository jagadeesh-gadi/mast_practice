
#include <stdio.h>
#include <stdlib.h>

void sensor(void)
{
    volatile int data[100];

    data[0] = 10;
    printf("sensor running: %d\n", data[0]);
}

void process(void)
{
  volatile int data[200];

data[0] = 20;

     sensor();

   printf("process running: %d\n", data[0]);
}

int main(void)
 { 
    // int data[100] = {0};
    process();
   
    return 0;
}
