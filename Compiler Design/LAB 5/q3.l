%{
#include <stdio.h>
int pos_int=0;
int neg_int=0;
int pos_float=0;
int neg_float=0;
%}

%%
[-][0-9]+[.][0-9]+ {neg_float++;}
[0-9]+[.][0-9]+ {pos_float++;}
[-][0-9]+ {neg_int++;}
[0-9]+ {pos_int++;}
%%

int yywrap()
{
return 1;
}

void main()
{
char arr[100];
printf("Enter a string\n");
scanf("%s",arr);
yylex();
printf("Negative float %d\nPositive float %d\nNegative int %d\nPositive int %d",neg_float,pos_float,neg_int,pos_int);
}
