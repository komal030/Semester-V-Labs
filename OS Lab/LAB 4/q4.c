#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
  char oldpath[100];
  char newpath[100];
  printf("Enter old path: ");
  scanf("%s", oldpath);
  //Enter old path: /home/komal/Desktop/oslab/lab4/q1.c
  //Enter new path: /home/komal/Desktop/oslab/lab4/q1_t.c
  printf("Enter new path: ");
  scanf("%s", newpath);
  int result1 = symlink(oldpath, newpath);
  if (result1 == -1) {
    printf("Error linking\n");
    exit(0);
  }
  printf("Succesful linking\n");
  int result2 = unlink(newpath);
  if (result2 == -1) {
    printf("Error unlinking\n");
    exit(0);
  }
  printf("Succesful unlinking\n");
}
