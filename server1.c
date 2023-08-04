#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<fcntl.h>
#include<arpa/inet.h>
#define PORTNO 10201
int main()
{
int sockfd,newsockfd,portno,clilen,n=1;
struct sockaddr_in seraddr,cliaddr;
int i,value;
sockfd = socket(AF_INET,SOCK_STREAM,0);
seraddr.sin_family = AF_INET;
seraddr.sin_addr.s_addr = inet_addr("172.16.57.199");
seraddr.sin_port = htons(PORTNO);
bind(sockfd,(struct sockaddr *)&seraddr,sizeof(seraddr));
listen(sockfd,5);
char buf[256];
printf("server waiting\n");
clilen = sizeof(clilen);
newsockfd=accept(sockfd,(struct sockaddr *)&cliaddr,&clilen);
n = read(newsockfd,buf,sizeof(buf));
printf("Encrypted String: %s\n",buf);

for(int i=0;i<strlen(buf);i++)
{
buf[i]=(char)((int)buf[i]-4);
}
printf("Decrypted String: %s\n",buf);
n = write(newsockfd,buf,sizeof(buf));

}
