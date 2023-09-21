#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
FILE *f1;
char filename[]="input.c";
f1=fopen(filename,"r");
if(f1==NULL)
{
printf("Error");
exit(0);
}
char c=fgetc(f1);
int blankspaces=0;
int semicolon=0;
int blanklines=0;
char s1[100];
while(fgets(s1,100,f1)!=NULL)
{
if(strcmp(s1,"\n")==0)
blanklines++;
}
rewind(f1);
while(c!=EOF)
{
if(c==' ')
blankspaces++;
if(c==';')
{
c=fgetc(f1);
if(c=='\n')
semicolon++;
fseek(f1,-1,SEEK_CUR);
}
c=fgetc(f1);
}
printf("Semicolons %d\nBlanklines %d\nBlankSpaces %d\n",semicolon,blanklines,blankspaces);
fclose(f1);
}
