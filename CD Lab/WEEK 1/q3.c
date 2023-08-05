#include <stdio.h>
#include <stdlib.h> 
int main()
{
FILE *f1, *f2, *f3;
char fname1[100],fname2[100],fname3[100],c1,c2;
printf("Enter the first filename to open for reading: \n");
scanf("%s", fname1);
f1 = fopen(fname1, "r");

printf("Enter the second filename to open for reading: \n");
scanf("%s", fname2);
f2 = fopen(fname2, "r"); 
if (f1 == NULL||f2==NULL)
{
printf("Cannot open file \n");
exit(0);
}
printf("Enter the filename to open for writing: \n");
scanf("%s", fname3);
f3 = fopen(fname3, "w+"); 
c1 = fgetc(f1);
c2 = fgetc(f2);
while (c1 != EOF && c2!= EOF)
{
while(c1!='\n')
{
fputc(c1, f3);
c1 = fgetc(f1);
}
fputc('\n',f3);
while(c2!='\n')
{
fputc(c2,f3);
c2=fgetc(f2);
}
fputc('\n',f3);
c1 = fgetc(f1);
c2 = fgetc(f2);
}
if(c1== EOF)
{
while(c2!=EOF)
{
fputc(c2,f3);
c2=fgetc(f2);
}
}
if(c2== EOF)
{
while(c1!=EOF)
{
fputc(c1,f3);
c1=fgetc(f1);
}
}
printf("\nContents copied to %s", fname3);
fclose(f1);
fclose(f2);
fclose(f3);
return 0;
}
