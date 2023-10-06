#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  pid_t id;
  id = fork();

  if (id == -1) {
    printf("ERROR");
    exit(0);
  } else if (id == 0) {
    printf("CHILD PROCESS RUNNING\nPID:%d\nPPID:%d\n", getpid(), getppid());
  } else {
    int status;
    wait( & status);
    printf("PARENT PROCESS RUNNING: PID:%d\nCHILD PID:%d\n", getpid(), id);
  }
  exit(0);
}
