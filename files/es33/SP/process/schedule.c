#include <stdio.h>
#include <sched.h>

int main()
{
    int priority = sched_getscheduler(1);
    if (priority == SCHED_FIFO)
    {
        printf("sched fifo\n");
    }
    else if (priority == SCHED_RR)
    {
        printf("sched rr\n");
    }
    else if (priority == SCHED_OTHER)
    {
        printf("sched others\n");
    }
    return 0;
}