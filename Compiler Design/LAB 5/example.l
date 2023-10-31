%{
  #include <stdio.h>

  %} 
%%
[a - zA - z_][_0 - 9 a - zA - z] * {printf("......%s is an ID\n", yytext);} 
%%

int yywrap() {
  return 1;
}

void main() {
  char arr[20];
  printf("Enter the string\n");
  scanf("%s", arr);
  yylex();
}
