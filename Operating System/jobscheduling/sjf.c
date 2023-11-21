#include <stdio.h>
#include <stdlib.h>

typedef struct process
{
char name[100];
int btime;
}Process;

Process P[100];

void sort(int n)
{
for(int i=0;i<n-1;i++)
{
for(int j=0;j<n-i-1;j++)
{
if(P[j].btime>P[j+1].btime)
{
int temp=P[j].btime;
P[j].btime=P[j+1].btime;
P[j+1].btime=temp;
}
}
}
}

void wait(int n)
{
int waittime[n];
waittime[0]=0;
int totaltime=0;
for(int i=1;i<n;i++)
{
waittime[i]=waittime[i-1]+P[i-1].btime;
totaltime+=waittime[i];
}
int avgtime=totaltime/n;
for(int i=0;i<n;i++)
printf("Start time of Process %d: %d\n",i,waittime[i]);
printf("Average wait time %d\n",avgtime);
}

int main()
{
int n=4;
P[0].btime=6;
P[1].btime=8;
P[2].btime=7;
P[3].btime=3;
sort(n);
wait(n);
}
