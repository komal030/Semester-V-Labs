#include <stdio.h>
#include <stdlib.h>

void sort(int arr[],int n)
{
for(int i=0;i<n;i++)
{
for(int j=0;j<n-i-1;j++)
{
if(arr[j+1]<arr[j])
{
int temp=arr[j];
arr[j]=arr[j+1];
arr[j+1]=temp;
}
}
}
}

int main()
{
int head=53;
int ledge=0;
int redge=199;
int arr[9] = {
    98,
    183,
    37,
    122,
    14,
    124,
    65,
    67
  };
  int n=8;
  arr[8]=53;
  sort(arr,n+1);
  int index=-1;
  for(int i=0;i<=n;i++)
  {
  if(arr[i]==head)
  {
  index=i;
  break;
  }
  }
  int diff;
  for(int i=index;i<n;i++)
  {
  diff=abs(arr[i]-arr[i+1]);
  printf("Move from %d to %d with seek %d\n",arr[i],arr[i+1],diff);
  }
  diff=abs(arr[n]-redge);
  printf("Move from %d to %d with seek %d\n",arr[n],redge,diff);
  diff=abs(ledge-redge);
  printf("Move from %d to %d with seek %d\n",redge,ledge,diff);
  diff=abs(ledge-arr[0]);
  printf("Move from %d to %d with seek %d\n",ledge,arr[0],diff);
  
  for(int i=0;i<index-1;i++)
  {
  diff=abs(arr[i]-arr[i+1]);
  printf("Move from %d to %d with seek %d\n",arr[i],arr[i+1],diff);
  }
  }
  
