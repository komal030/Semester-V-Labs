%{
#include <stdio.h>
int p=0;
int s=0;
%}
%%
"printf" {p++;fprintf(yyout,"%s", "READ");}
"scanf" {s++;fprintf(yyout,"%s", "WRITE");}
. {fprintf(yyout,"%s",yytext);}
%%
int yywrap()
{
return 1;
}

int main()
{
yyin=fopen("input.c","r");
yyout = fopen("output.c","w+");
yylex();
printf("Printf count: %d\nScanf count :%d\n",p,s);
return 0;
}
