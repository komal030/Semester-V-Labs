#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

int main(int argc, char * argv[]) {
  if (argc < 2) {
    printf("Insufficient arguments\n");
    exit(1);
  }

  int i = 1;
  while (i < argc) {
    int f1 = open(argv[i], O_RDONLY);
    if (f1 == -1) {
      printf("Cannot open file\n");
      exit(1);
    }
    char c;
    int k = 0;
    while (k < 20 && read(f1, & c, sizeof(c) > 0)) {
      if (c == '\n') {
        k++;
      }
      printf("%c", c);
    }
    if (k == 20)
      fgetc(stdin);
    close(f1);
    i++;
  }
  printf("Contents printed\n");
}
