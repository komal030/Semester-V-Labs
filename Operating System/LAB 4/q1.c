#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>

int main() {
  printf("Enter filename: ");
  char filename[50];
  scanf("%s", filename);

  struct stat statbuf;
  int result = stat(filename, & statbuf);
  if (result == -1) {
    printf("Error");
    exit(0);
  }

  printf("Inode value: %ld\n", statbuf.st_ino);
}
