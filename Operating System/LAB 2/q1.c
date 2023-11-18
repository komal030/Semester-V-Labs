#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

int main() {
  char path[100];
  printf("Enter path\n");
  scanf("%s", path);

  DIR *directory=opendir(path);
  struct stat statbuf;
  struct dirent *entry;

  if (directory == NULL) {
    printf("File not found\n");
    exit(1);
  }

  chdir(path);

  while ((entry=readdir(directory))!= NULL) {
    if (strcmp("..", entry -> d_name) != 0 && strcmp(".", entry -> d_name) != 0) {
      lstat(entry -> d_name, & statbuf);
      printf("\n%s", entry -> d_name);

      if (statbuf.st_mode & S_IRUSR)
        printf("\nUser has read access");
      if (statbuf.st_mode & S_IRGRP)
        printf("\nGroup has read access");
      if (statbuf.st_mode & S_IROTH)
        printf("\nOthers have read access");
      if (statbuf.st_mode & S_IWUSR)
        printf("\nUser has write access");
      if (statbuf.st_mode & S_IWGRP)
        printf("\nGroup has write access");
      if (statbuf.st_mode & S_IWOTH)
        printf("\nOthers have write access");
      if (statbuf.st_mode & S_IXUSR)
        printf("\nUser has execute access");
      if (statbuf.st_mode & S_IXGRP)
        printf("\nGroup has execute access");
      if (statbuf.st_mode & S_IXOTH)
        printf("\nOthers have execute access");
    }
  }
}
