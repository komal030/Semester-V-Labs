#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char * argv[]) {
  if (argc != 2) {
    printf("Error");
    exit(0);
  }
  DIR * d1;
  struct dirent * entry;
  struct stat statbuf;
  d1 = opendir(argv[1]);
  if (d1 == NULL) {
    printf("Error in opening directory");
    exit(0);
  }

  chdir(argv[1]);
  printf("Files in current directory:\n");
  while ((entry = readdir(d1)) != NULL) {
    lstat(entry -> d_name, & statbuf);

    if ((strcmp(entry -> d_name, "..") == 0) || (strcmp(entry -> d_name, ".") == 0))
      continue;
    printf("%s/\n", entry -> d_name);

  }
  printf("Name the file to remove:");
  char file[100];
  scanf("%s", file);
  remove(file);
  printf("Files in current directory after operation:\n");
  d1 = opendir(argv[1]);
  chdir(argv[1]);
  while ((entry = readdir(d1)) != NULL) {
    lstat(entry -> d_name, & statbuf);
    if ((strcmp(entry -> d_name, "..") == 0) || (strcmp(entry -> d_name, ".") == 0))
      continue;
    printf("%s/\n", entry -> d_name);

  }
}
