#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char * argv[]) {
  int f1;
  f1 = open(argv[1], O_RDONLY);
  if (f1 == -1) {
    printf("Error opening file\n");
    exit(1);
  }
  char c[200];
  int i = 1;
  while (read(f1, c + i, 1) > 0) {
    if (c[i] != '\n') {
      i++;
    } else {
      if (strstr(c, argv[2]) != NULL) {
        c[i] = '\0';
        printf("%s", c);
        memset(c, 0, 100);
      }
      printf("\n");
      i=0;
    }
  }
  close(f1);
}
