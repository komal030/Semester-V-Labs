#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<sys/stat.h>

int main() {
  pid_t id;
  id = fork();
  if (id == -1) {
    printf("ERROR");
  } else if (id == 0) {
    printf("PPID :%d\n", getppid());
    printf("Child process\n");
    sleep(5);
    printf("PPID:%d\n", getppid());
    exit(1);
  } else {
    int status;
    wait( & status);
    printf("Parent process running %d\n", status);
  }
  exit(0);
}
