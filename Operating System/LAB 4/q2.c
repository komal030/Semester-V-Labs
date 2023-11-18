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
  int result = lstat(filename, & statbuf);
  if (result == -1) {
    printf("Error");
    exit(0);
  }
  char * accesst = ctime( & statbuf.st_atime);
  char * modifyt = ctime( & statbuf.st_mtime);
  char * changet = ctime( & statbuf.st_ctime);
  printf("Inode number: %ld\n", statbuf.st_ino);
  printf("User id: %ld\n", statbuf.st_uid);
  printf("File size: %ld\n", statbuf.st_size);
  printf("Number of blocks : %ld\n", statbuf.st_blocks);
  printf("Block size: %ld\n", statbuf.st_blksize);
  printf("Device node in which file resides: %ld\n", statbuf.st_dev);
  printf("Number of hard links: %ld\n", statbuf.st_nlink);
  printf("Access time: %s\n", accesst);
  printf("Modify time: %s\n", modifyt);
  printf("Change time: %s\n", changet);
  printf("File type: ");
  switch (statbuf.st_mode & S_IFMT) {
  case S_IFIFO:
    printf("FIFO");
    break;
  case S_IFDIR:
    printf("DIRECTORY");
    break;
  case S_IFSOCK:
    printf("SOCKET");
    break;
  case S_IFREG:
    printf("REGULAR");
    break;
  case S_IFBLK:
    printf("BLOCK");
    break;
  case S_IFCHR:
    printf("CHARACTER");
    break;
  case S_IFLNK:
    printf("SYMBOLIC LINK");
    break;
  default:
    printf("Unknown");
  }
  printf("\n");
}
