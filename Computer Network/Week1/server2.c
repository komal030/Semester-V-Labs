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
#define PORTNO 10202
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
while(1)
{
char buf[256];
printf("server waiting\n");
clilen = sizeof(clilen);
newsockfd=accept(sockfd,(struct sockaddr *)&cliaddr,&clilen);
do{

n = read(newsockfd,buf,sizeof(buf));
printf("Given String: %s\n",buf);
    char str[64];
    char words[10][20];
    i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    while (buf[i] != 0) {
        if (buf[i] == ' ') {
            words[k][j] = '\0';
            k++;
            j = 0;
        }
        else {
            words[k][j] = buf[i];
            j++;
        }
        i++;
    }
    words[k][j] = '\0';

    j = 0;
    for (i = 0; i < k; i++) {
        int present = 0;
        for (l = 1; l < k + 1; l++) {
            if (words[l][j] == '\0' || l == i)
                continue;

            if (strcmp(words[i], words[l]) == 0) {
                words[l][j] = '\0';
                present = present + 1;
            }
        }
    }
    char ans[256],temp[20];
    j = 0;
    for (i = 0; i < k + 1; i++) {
        if (words[i][j] == 0)
            continue;
        else
            {strcpy(temp,words[i]);
            strcat(ans,temp);
            strcat(ans," ");
    }
    }
n = write(newsockfd,ans,sizeof(ans));
ans="";
}while(1);
}
}

