#include<sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main() {
  pid_t id;
  id = fork();
  if (id == -1) {
    printf("ERROR\n");
    exit(0);
  } else if (id == 0) {
    exit(0);
  } else {
    sleep(10000);
  }
  exit(0);
}
