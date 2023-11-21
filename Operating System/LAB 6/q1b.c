#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>

typedef struct message
{
char ch;
}Message;

int main()
{
int msg_id=msgget((key_t)1234,0666|IPC_CREAT);
Message message;
if(msg_id==-1)
{
printf("Message queue not created");
exit(0);
}
while(1)
{
int res=msgrcv(msg_id,(void*)&message,BUFSIZ,0,0);
if(res==-1)
{
printf("Error in receiving message\n");
exit(0);
}
if(message.ch=='-')
{
printf("End of program\n");
int k=msgctl(msg_id,IPC_RMID,0);
exit(0);
}
message.ch=(char)(message.ch+1);
printf("Character + 1 = %c\n",message.ch);
}
}

