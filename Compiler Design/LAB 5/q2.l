% {
  #include<stdio.h>
  int vowel = 0;
  int consonant = 0; %
} %
% [aeiouAEIOU] {
  vowel++;
}
[a - zA - Z] {
  consonant++;
} %
%
int yywrap() {
  return 1;
}
int main(int argc, char ** argv) {
  yylex();
  printf("Vowels:%d\nConsonants:%d\n", vowel, consonant);
}
