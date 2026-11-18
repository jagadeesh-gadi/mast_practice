// shared memory for the sender program using this we can send data to the
// receiver

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
  int fd;
  char *ptr;

  char *msg = "hello jagadeesh from sender";

  fd = shm_open("/my_shm", O_CREAT | O_RDWR, 0666);
  if (fd == -1) {
    perror("shm_open");
    return 1;
  }

  if (ftruncate(fd, 1024) == -1) {
    perror("ftruncate");
    close(fd);
    return 1;
  }

  ptr = mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

  if (ptr == MAP_FAILED) {
    perror("mmap");
    close(fd);
    return 1;
  }

  memcpy(ptr, msg, strlen(msg) + 1);

  printf("sender: message written: %s\n", ptr);

  munmap(ptr, 1024);

  close(fd);

  return 0;
}
