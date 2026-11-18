
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;
    char buffer[100];

    // 1. Open or create a file
    fd = open("test.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    // 2. Write data into the file
    write(fd, "Hello Ubuntu\n", 13);

    // 3. Move file offset to the beginning
    lseek(fd, 0, SEEK_SET);

    // Read data from the file
    int n = read(fd, buffer, sizeof(buffer) - 1);

    if (n >= 0) {
        buffer[n] = '\0';
        printf("File content: %s", buffer);
    }

    // 4. Close the file
    close(fd);

    return 0;
}

