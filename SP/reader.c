
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    char buffer[100];
    int fd = open("myfifo333", O_RDONLY);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    ssize_t n = read(fd, buffer, sizeof(buffer) - 1);

    if (n > 0)
    {
        buffer[n] = '\0';
        printf("Received: %s\n", buffer);
    }

    close(fd);
    return 0;
}

