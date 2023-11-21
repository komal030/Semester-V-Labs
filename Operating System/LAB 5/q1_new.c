#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{
int fd[2];
int res=pipe(fd);
int n;
if(res==-1)
{
printf("Error ");
exit(0);
}
char arr[]="Hello boki";
char buf[20];
int pid=fork();
if(pid==0)
{
 close(fd[1]);
 while( (n=read(fd[0],&buf,1))>0)
 write(1,buf,1);
 close(fd[0]);
}
else
{
close(fd[0]);
write(fd[1],arr,sizeof(arr));
close(fd[1]);
wait(NULL);
exit(0);
}
}

 
