%{
  #include <stdio.h>

%} 
%% [0 - 9] + {
  int dec = atoi(yytext);
  printf("decimal %d hexadecimal %x", dec, dec);
} %
%

int yywrap() {
  return 1;
}

int main() {
  char arr[100];
  printf("Enter string\n");
  scanf("%s", arr);
  yylex();
  return 1;
}
