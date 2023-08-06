#include <stdio.h>
#include <stdlib.h>
int main() {
  FILE *f1;
  char fname[100], c;
  printf("Enter name of file to read\n");
  scanf("%s", fname);
  f1 = fopen(fname, "r");
  if (f1 == NULL) {
    printf("Cannot open file\n");
    exit(1);
  }
  int blankline = 0, semi = 0, blankspace = 0;
  c = fgetc(f1);
  while (c != EOF) {
    if (c == ' ')
      blankspace++;
    if (c == ';') {
      c = fgetc(f1);
      if (c == '\n') {
        semi++;
        fseek(f1, -1, SEEK_CUR);
      }
    }
    if (c == '\n') {
      c = fgetc(f1);
      if (c == '\n') {
        blankline++;
      }
    }
    c=fgetc(c);
  }
 
 printf("Number of sentences ending with semi colon: %d\nNumber of blank sentences: %d\nNumber of blank spaces: %d", semi, blankline, blankspace);
  fclose(f1);
  return 1;
}
