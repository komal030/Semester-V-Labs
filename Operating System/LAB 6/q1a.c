#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <string.h>
#include <stdlib.h>

typedef struct message
{
char ch;
}Message;

int main()
{
Message message;
int msg_id=msgget((key_t)1234, 0666| IPC_CREAT);
if(msg_id==-1)
{
printf("Error in creating message queue\n");
exit(0);
}
while(1)
{
printf("Enter the character :");
scanf(" %c",&(message.ch));
int res=msgsnd(msg_id,(void*)&message,512,0);
if(res==-1)
{
printf("Error in sending message\n");
exit(0);
}
if(message.ch=='-')
{
printf("End of program\n");
exit(0);
}
}
}
