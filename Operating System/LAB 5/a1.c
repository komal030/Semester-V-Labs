#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
  int fd[2];
  int result = pipe(fd);
  if (result == -1) {
    printf("Error making pipe\n");
    exit(1);
  }
  char buff[] = "happyday";
  int id = fork();
  if (id == -1) {
    printf("Error forking");
    exit(0);
  } else if (id == 0) {
    close(fd[1]);
    char c;
    printf("Reading:\n");
    while (read(fd[0], & c, sizeof(c)) != 0)
      printf("%c\n", c);
    printf("Finished reading\n");
    close(fd[0]);
    exit(0);
  } else {
    close(fd[0]);
    write(fd[1], buff, sizeof(buff));
    close(fd[1]);
    wait(NULL);

    printf("Finished writing to file\n");
    exit(0);
  }
}
