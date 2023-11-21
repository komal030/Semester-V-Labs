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
int fd=open(FIFO_NAME,O_RDONLY);
int num;
read(fd,&num,sizeof(num));
int arr[num];
read(fd,arr,sizeof(arr));
printf("Size %d\n",num);
for(int i=0;i<num;i++)
printf("Element %d \n",arr[i]);
}
