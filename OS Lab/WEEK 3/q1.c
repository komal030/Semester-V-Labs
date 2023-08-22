#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
int main() {
  pid_t pid = fork();
  char message[50];
  int n, status;
  if (pid < 0) {
    printf("Error encountered");
    exit(-1);
  } else if (pid == 0) {
    strcpy(message, "I am child process");
    n = 5;
  } else {
    wait( & status);
    printf("Child process returned: %d\n", status);
    strcpy(message, "I am parent process");
    n = 3;
  }
  for (; n > 0; n--)
    printf("%s\n", message);
}
