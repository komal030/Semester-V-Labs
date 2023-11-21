#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#define FIFO_NAME "/home/komal/Desktop/OS/lab/fifo"
int main()
{
int res=access(FIFO_NAME,F_OK);
if(res!=-1)
{
printf("ERROR\n");
exit(0);
}
int num=5;
int arr[]={1,2,3,4,5};
mkfifo(FIFO_NAME,0666);
int fd=open(FIFO_NAME,O_WRONLY);
if(fd==-1)
{
printf("Error\n");
exit(0);
}
write(fd,&num,sizeof(num));
write(fd,arr,sizeof(arr));
close(fd);
}

