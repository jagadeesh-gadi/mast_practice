
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    char buf[100];

    int fd = open("/tmp/myfifo", O_RDONLY);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    ssize_t n = read(fd, buf, sizeof(buf) - 1);

    if (n > 0)
    {
        buf[n] = '\0';
        printf("Received message: %s\n", buf);
    }

    printf("Receiver PID is %d\n", getpid());

    close(fd);
    return 0;
}

