#include <fcntl.h>
#include <sched.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

#define COUNT 1000

typedef struct {
  char message[100];
  int count;
} shareddata;

int main() {

  setbuf(stdout, NULL);
  shm_unlink("/msg_count");

  int fd = shm_open("/msg_count", O_CREAT | O_RDWR, 0666);
  if (fd == -1) {
    perror("failed open");
    return 1;
  }

  if (ftruncate(fd, sizeof(shareddata)) == -1) {
    perror("failed to trunctae");
    close(fd);
    shm_unlink("/msg_count");
    return 1;
  }

  shareddata *p =
      mmap(NULL, sizeof(shareddata), PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);

  if (p == MAP_FAILED) {
    perror("mmap failed");
    close(fd);
    shm_unlink("/msg_count");
    return 1;
  }

  p->count = 0;
  strcpy(p->message, "hello from parent");

  pid_t pid = fork();

  if (pid == -1) {
    perror("fork failed to open");
    close(fd);
    shm_unlink("/msg_count");
    munmap(p, sizeof(shareddata));
    return 1;
  }

  if (pid == 0) // child process
  {
    printf("child recevied :: %s\n", p->message);
    strcpy(p->message, "hello from child ");

    for (int i = 0; i < COUNT; i++) {
      int temp = p->count;
      sched_yield();
      p->count = temp + 1;
    }

    close(fd);
    munmap(p, sizeof(shareddata));
    _exit(0);
  }

  //  parent process
  for (int i = 0; i < COUNT; i++) {
    int temp = p->count;
    sched_yield();
    p->count = temp + 1;
  }
  wait(NULL);
  printf("parent received :: %s\n", p->message);
  printf("expected output :: %d\n", 2 * COUNT);
  printf("Actual output :: %d\n", p->count);

  munmap(p, sizeof(shareddata));
  close(fd);
  shm_unlink("/msg_count");

  return 0;
}
