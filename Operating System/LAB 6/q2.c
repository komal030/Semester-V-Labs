#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<sys/msg.h>
#include<sys/shm.h>
#include<unistd.h>

typedef struct block
{
char ch;
}Block;
int main()
{
void* shared_memory=(void*)0;
Block* block;
int shm_id=shmget((key_t)1234, sizeof(Block),0666|IPC_CREAT);
if(shm_id==-1)
{
printf("Shared memory not created\n");
exit(0);
}
shared_memory=shmat(shm_id,(void*)0,0);
if(shared_memory==(void*)-1)
{
printf("Shared memory not attached\n");
exit(0);
}
block=(Block*)shared_memory;
printf("Enter alphabet ");
char alpha;
scanf("%c",&alpha);
block->ch=alpha;
int pid=fork();
if(pid==0)
{
alpha=(char)(alpha+1);
block->ch=alpha;
}
else
{
int status;
wait(&status);
printf("Character at parent is %c\n",block->ch);
exit(0);
}

}






