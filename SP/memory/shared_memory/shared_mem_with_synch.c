#include <fcntl.h>
#include <sched.h>
#include <semaphore.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>
#define COUNT 1000

typedef struct {
  char message[100];
  int count;
  sem_t lock;
} shareddata;

int main() {

  setbuf(stdout, NULL);
  shm_unlink("/msg_count");

  //   file descriptor
  int fd = shm_open("/msg_count", O_CREAT | O_RDWR, 0666);
  if (fd == -1) {
    perror("failed open");
    return 1;
  }

  //   truncate the fd size
  if (ftruncate(fd, sizeof(shareddata)) == -1) {
    perror("failed to trunctae");
    close(fd);
    shm_unlink("/msg_count");
    return 1;
  }

  //   memory mapping
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
  if (sem_init(&p->lock, 1, 1) == -1) {
    perror("semphore error");
    munmap(p, sizeof(shareddata));
    close(fd);
  }
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
    sem_wait(&p->lock);
    printf("child recevied :: %s\n", p->message);
    strcpy(p->message, "hello from child ");
    sem_post(&p->lock);
    for (int i = 0; i < COUNT; i++) {
      sem_wait(&p->lock);
      p->count++;
      sem_post(&p->lock);
    }

    close(fd);
    munmap(p, sizeof(shareddata));
    _exit(0);
  }

  //  parent process
  for (int i = 0; i < COUNT; i++) {
    sem_wait(&p->lock);
    p->count++;
    sem_post(&p->lock);
  }
  wait(NULL);
  sem_wait(&p->lock);
  printf("parent received :: %s\n", p->message);
  sem_post(&p->lock);
  printf("expected output :: %d\n", 2 * COUNT);
  printf("Actual output :: %d\n", p->count);

  sem_destroy(&p->lock);
  munmap(p, sizeof(shareddata));
  close(fd);
  shm_unlink("/msg_count");

  return 0;
}
