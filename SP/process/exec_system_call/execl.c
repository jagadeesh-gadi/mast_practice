#include <stdio.h>
#include <unistd.h>
int main()
{
    printf("before exec() call\n");

    // execl("/bin/ls", "ls", "-l","-lh", NULL);
    printf("after execl()");
     execl("/bin/date", "date", "+%y-%m-%d", NULL);
    execl("/usr/bin/time", "time", "date", NULL);
    return 0;
}