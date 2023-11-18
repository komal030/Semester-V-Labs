#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>

int main(){
	int n, fd[2];
	char buf[1025], *data = "Komal Choudhry";
	pipe(fd);
	write(fd[1], data, strlen(data));
	n = read(fd[0], buf, 1024);
	if(n >= 0){
		buf[n] = 0;
		printf("Read %d bytes from the pipe\n", n);
		printf("Data read: %s\n", buf);
	}
	else
		perror("Read");
	exit(0);
}
