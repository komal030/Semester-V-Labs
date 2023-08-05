#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
FILE *f1,*f2;
char fname1[100],fname2[100];
printf("Enter the filename to open for reading\n");
scanf("%s",fname1);
f1=fopen(fname1,"r");
if(f1==NULL)
{
printf("File cannot be opened\n");
exit(1);
}
printf("Enter the filename to open for writing\n");
scanf("%s",fname2);
f2=fopen(fname2,"w+");
int count=0;
char c,a[10];
c=fgetc(f1);
while(c!=EOF)
{
fputc(c,f2);
if(c=='\n')
count++;
if(count>4)
{
count=0;
printf("Do you wish to continue\n");
scanf("%s",a);
if(strcmp(a,"Q")==0)
{
printf("Contents copied to file %s\n",fname2);
exit(1);
}
}
c=fgetc(f1);
}

fclose(f1);
fclose(f2);
return 1;
} 



