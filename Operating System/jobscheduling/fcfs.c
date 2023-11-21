#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct process
{
char name[100];
int btime;
}Process;

Process P[100];

void waitTime(int n)
{
int arr[n];
arr[0]=0;
for(int i=1;i<n;i++)
arr[i]=arr[i-1]+P[i-1].btime;
int totaltime=0;
for(int i=0;i<n;i++)
{
totaltime+=arr[i];
printf("Wait time for P%d is %d\n",i,arr[i]);
}
double avgtime=totaltime/n;
printf("Average wait time %lf\n",avgtime);
}

int main()
{
printf("Enter number of Processes:\n");
int n;
scanf("%d",&n);
for(int i=0;i<n;i++)
{
printf("Enter burst time of Process %d: ",i);
char temp[10];
char temp2[]="P";
sprintf(temp,"%d",i);
scanf("%d",&P[i].btime);
strcat(temp2,temp);
strcpy(P[i].name,temp2);
}
waitTime(n);
}

