#include <stdio.h>
#include <stdlib.h> // For exit()
int main()
{
FILE *f1;
char filename[100], c;
printf("Enter the filename to open for reading: \n");
scanf("%s", filename);
f1 = fopen(filename, "r");
// Open one file for reading
if (f1 == NULL)
{
printf("Cannot open file %s \n", filename);
exit(0);
}
c = fgetc(f1);
// Read contents from file
int countchar=0;
int countline=0;
while (c != EOF)
{
if(c=='\n')
countline++;
else
countchar++;
c = fgetc(f1);
}
printf("\nNumber of characters = %d\nNumber of lines = %d\n",countchar,countline);
fclose(f1);
return 0;
}
