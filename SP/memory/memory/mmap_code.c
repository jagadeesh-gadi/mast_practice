
// #include <stdio.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <fcntl.h>
// #include <sys/mman.h>
// #include <sys/stat.h>
// #include <string.h>

// int main(void)
// {
//     int fd;
//     char *ptr;
//     size_t size = 4096;

//     printf("Process ID: %ld\n", (long)getpid());

//     // Step 1: Open or create the file
//     fd = open("data.txt", O_RDWR | O_CREAT, 0644);

//     if (fd == -1) {
//         perror("open failed");
//         return 1;
//     }

//     printf("File descriptor: %d\n", fd);

//     // Step 2: Set the file size
//     if (ftruncate(fd, (off_t)size) == -1) {
//         perror("ftruncate failed");
//         close(fd);
//         return 1;
//     }

//     // Step 3: Map the file using MAP_SHARED
//     ptr = mmap(NULL, size,
//                PROT_READ | PROT_WRITE,
//                MAP_PRIVATE, fd, 0);

//     if (ptr == MAP_FAILED) {
//         perror("mmap failed");
//         close(fd);
//         return 1;
//     }

//     printf("Mapped address: %p\n", (void *)ptr);

//     // Step 4: Display the current contents
//     printf("Before modification: %s\n", ptr);

//     // Step 5: Modify the mapped file contents
//     const char *message = "Data modified using mmap!";
//     size_t len = strlen(message);

//     // Clear the old contents first
//     memset(ptr, 0, size);

//     // Copy the new contents into mapped memory
//     memcpy(ptr, message, len + 1);

//     // Step 6: Synchronize changes with the file
//     if (msync(ptr, size, MS_SYNC) == -1) {
//         perror("msync failed");
//         munmap(ptr, size);
//         close(fd);
//         return 1;
//     }

//     printf("After modification: %s\n", ptr);

//     printf("Press Enter to unmap memory...");
//     getchar();

//     // Step 7: Release the mapping
//     if (munmap(ptr, size) == -1) {
//         perror("munmap failed");
//         close(fd);
//         return 1;
//     }

//     // Step 8: Close the file
//     close(fd);

//     printf("Mapping released.\n");

//     return 0;
// }




#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>

int main(void)
{
    int fd;
    char *ptr;
    size_t size = 4096;

    printf("Process ID: %ld\n", (long)getpid());

    // Step 1: Open or create the file
    fd = open("data.txt", O_RDWR | O_CREAT, 0644);

    if (fd == -1) {
        perror("open failed");
        return 1;
    }

    printf("File descriptor: %d\n", fd);

    // Step 2: Set the file size to 4096 bytes
    if (ftruncate(fd, (off_t)size) == -1) {
        perror("ftruncate failed");
        close(fd);
        return 1;
    }

    // Step 3: Map the file privately
    ptr = mmap(NULL, size,
               PROT_READ | PROT_WRITE,
               MAP_PRIVATE, fd, 0);

    if (ptr == MAP_FAILED) {
        perror("mmap failed");
        close(fd);
        return 1;
    }

    printf("Mapped address: %p\n", (void *)ptr);

    // Step 4: Display original mapped contents
    printf("Before modification: %s\n", ptr);

    // Step 5: Modify the private memory mapping
    const char *message = "Modified privately using mmap!";
    size_t len = strlen(message);

    memset(ptr, 0, size);
    memcpy(ptr, message, len + 1);

    printf("After modification: %s\n", ptr);

    // Step 6: Synchronize request (does not write
    // private modifications back to the file)
    if (msync(ptr, size, MS_SYNC) == -1) {
        perror("msync failed");
        munmap(ptr, size);
        close(fd);
        return 1;
    }
 printf("Mapped address: %p\n", (void *)ptr);
    printf("Check data.txt from another terminal now.\n");
    printf("Press Enter to unmap memory...");
    getchar();

    // Step 7: Release private mapping
    if (munmap(ptr, size) == -1) {
        perror("munmap failed");
        close(fd);
        return 1;
    }

    // Step 8: Close the file
    close(fd);

    printf("Mapping released.\n");

    return 0;
}
