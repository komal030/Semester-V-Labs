#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
FILE *f1,*f2;
char filename[100],c;
printf("Enter file name: ");
scanf("%s",filename);
f1=fopen(filename,"r");
if(f1==NULL)
{
printf("Cannot open file\n");
exit(0);
}
f2=fopen("q2output","w+");
char preprocessor[2][10] = {
    "#include",
    "#define"
};

c=fgetc(f1);
while(c!=EOF)
{
	int k=0;
	char temp[100];
	 while (c!=EOF && c != ' ' && c != '\n') 
	{
		temp[k++]=c;
		c=fgetc(f1);
	}

printf("temp %s:\n",temp);
	if(strcmp(temp,preprocessor[0])!=0 && strcmp(temp,preprocessor[1])!=0)
	{
		int i=0;
		while(i<k)
		{
		putc(temp[i],f2);
		i++;
		}
	}
	putc(c,f2);
	c=fgetc(f1);
	 for (int i = 0; i < k; i++) {
        temp[i] = '\0';
    }
}

fclose(f1);
fclose(f2);
return 0;
}
