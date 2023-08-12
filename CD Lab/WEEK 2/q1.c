#include <stdio.h>
#include <stdlib.h> 
int main()
{
FILE *f1, *f2;
char filename[100], c;
printf("Enter the filename to open for reading: \n");
scanf("%s", filename);
f1 = fopen(filename, "r");
if (f1 == NULL)
{
printf("Cannot open file\n");
exit(0);
}

f2=fopen("q1output","w+");
c = fgetc(f1);
while (c != EOF)
{
if(c!='\t' && c!=' ')
{
putc(c,f2);
c=fgetc(f1);
}
else
{
while(c != EOF && (c==' '|| c=='\t'))
{
c = fgetc(f1);
}
putc(' ',f2);
}
}

fclose(f1);
fclose(f2);
return 0;
}
