
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
  int fd;
  char *ptr;

  fd = shm_open("/my_shm", O_RDONLY, 0666);
  if (fd == -1) {
    perror("shm_open");
    return 1;
  }

  ptr = mmap(NULL, 1024, PROT_READ, MAP_SHARED, fd, 0);
  if (ptr == MAP_FAILED) {
    perror("mmap");
    close(fd);
    return 1;
  }

  printf("receiver: message received: %s\n", ptr);

  munmap(ptr, 1024);

  close(fd);

// if (shm_unlink("/my_shm") == -1) {
    // perror("shm_unlink");
// }  
// 
 return 0;
}
