#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>

int main() {
  pid_t id;
  printf("Fork starting\n");

  id = fork();

  if (id == -1) {
    printf("Error in forking\n");
    exit(0);
  } else if (id == 0) {
    printf("Original child running started\n");
    execl("/home/komal/Desktop/oslab/lab3/q1", "q1", NULL);
    printf("Original child done running\n");
  } else {
    wait(NULL);
    printf("Parent running\n");
  }
  exit(0);
}
