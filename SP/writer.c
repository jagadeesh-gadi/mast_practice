
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
    int fd = open("myfifo333", O_WRONLY);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    const char msg[] = "Hello through FIFO";

    if (write(fd, msg, sizeof(msg)) == -1)
        perror("write");
    printf("data send \n");

    close(fd);
    return 0;
}

