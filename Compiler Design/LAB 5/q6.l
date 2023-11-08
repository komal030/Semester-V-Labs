% {
  #include <stdio.h>

  %} 
%%
"//" [a - zA - Z0 - 9 " "] * {
  fprintf(yyout, "%s", yytext);
}
"/*" [a - zA - Z0 - 9_ " "
  "\n"
] * "*/" {
  fprintf(yyout, "%s", yytext);
}
[A - Z] {
  fprintf(yyout, "%c", yytext[0] + 32);
}
. {
  fprintf(yyout, "%s", yytext);
} 
%%

int yywrap() {
  return 1;
}

int main() {
  yyin = fopen("input.c", "r");
  yyout = fopen("output1.c", "w+");
  yylex();
  printf("Succesfull\n");
}
