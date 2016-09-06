#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>

int umaVariavel = 0;

int main() {

  int fd = shm_open("area_teste", O_RDWR | O_CREAT, 0666);
  if (fd == -1) {
    perror("shm_open");
    exit(-1);
  }

  ftruncate(fd, 1024*1024*64);

  void *ptr = mmap(0, 1024*1024*64, PROT_READ | PROT_WRITE, MAP_SHARED,  fd, 0);


  pid_t pid;

  pid = fork();//The child receives 0

  if(pid == 0) {
    umaVariavel++;
    strcpy(ptr, "alguma besteira");
    printf("Filho. Escrevi %s - %d %d %d \n", ptr, pid, getpid(), getppid());
    sleep(5);
    exit(0);
//    printf("Eu sou o filho e o meu PID é %d. Meu pai é %d\n", getpid(), getppid());
  } else if (pid > 0) {
    int status;
    waitpid(pid, &status, 0);
    printf("Pai. Meu filho escreveu %s - %d %d %d \n", ptr, pid, getpid(), getppid());

//    printf("Eu sou o pai. Meu pid é %d. Meu filho é %d\n", getpid(), pid);
  } else {
    perror("fork");
    exit(-1);
  }

  munmap(ptr, 1024*1024*64);
  shm_unlink("area_teste");
}
