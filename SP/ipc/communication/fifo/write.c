#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd = open("/tmp/myfifo", O_WRONLY);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    write(fd, "hello jagadeesh", 16);

    printf("Sender process PID is %d\n", getpid());

    close(fd);
    return 0;
}
