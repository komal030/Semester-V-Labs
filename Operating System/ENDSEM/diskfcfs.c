#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int main()
{
int arr[7]={3,4,1,6,8,7};
int n=6;
int head=2;
int totaltime=0;
double avgtime=0;
for(int i=n;i>0;i--)
{
arr[i]=arr[i-1];
}
arr[0]=head;
for(int i=0;i<n;i++)
{
int diff=arr[i]-arr[i+1];
if(diff<0)
diff=abs(diff);
totaltime+=diff;
printf("Move from %d to %d with seek %d\n",arr[i],arr[i+1],diff);
}
avgtime=totaltime/(double)n;
printf("Total seek time %d\nAverage seek time %lf\n",totaltime,avgtime);
}
