
#include <stdio.h>
#include <stdlib.h> 
int main()
{
FILE *f1, *f2;
char fname1[100],fname2[100],rev[100],c;
int k=0;
printf("Enter the first filename to open for reading: \n");
scanf("%s", fname1);
f1 = fopen(fname1, "r");

if (f1 == NULL)
{
printf("Cannot open file \n");
exit(0);
}


printf("Enter the filename to open for writing: \n");
scanf("%s", fname2);
f2 = fopen(fname2, "w"); 

c = fgetc(f1);
while (c != EOF )
{
rev[k++]=c;
c = fgetc(f1);
}

while(k>=0)
{
fputc(rev[k--],f2);
}
int size=0;
fseek(f1,0,SEEK_END);
size=ftell(f1);
printf("\nSize of file is: %d\n",size);
printf("\nContents copied to %s", fname2);
fclose(f1);
fclose(f2);
return 0;
}
