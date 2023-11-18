#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

char arr[256][20];
int k = 0;
void getdir(char * argv) {
  DIR * d1;
  struct dirent * entry;
  struct stat statbuf;
  d1 = opendir(argv);
  if (d1 == NULL) {
    printf("Error in opening directory");
    exit(0);
  }

  chdir(argv);
  while ((entry = readdir(d1)) != NULL) {
    lstat(entry -> d_name, & statbuf);
    if (S_ISDIR(statbuf.st_mode)) {
      if ((strcmp(entry -> d_name, "..") == 0) || (strcmp(entry -> d_name, ".") == 0))
        continue;
      strcpy(arr[k++], entry -> d_name);
      getdir(entry -> d_name);
    }
  }
 chdir("..");
 closedir(d1);
}

void sort() {
  for (int i = 0; i < k - 1; i++) {
    for (int j = 0; j < k - 1 - i; j++) {
      if (strcmp(arr[j], arr[j + 1]) > 0) {
        char temp[20];
        strcpy(temp, arr[j]);
        strcpy(arr[j], arr[j + 1]);
        strcpy(arr[j + 1], temp);
      }
    }
  }
}
void print() {
  for (int i = 0; i < k; i++)
    printf("%s\n", arr[i]);
}

int main(int argc, char * argv[]) {
  if (argc != 2) {
    printf("Error");
    exit(0);
  }
  getdir(argv[1]);
  sort();
  print();
}
