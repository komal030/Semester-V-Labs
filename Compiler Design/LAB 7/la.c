#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "la.h"

char *keywords[] = { "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto","if", "int", "long", "register", "return",   "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"};

int row = 1;
int col = 0;

int isSpecialSymbol(char c) {
   return c == '(' || c == ')' || c == '{' || c == '}' || c == ';' || c == ',' || c == '[' || c == ']';
}

int isArithmeticOp(char c) {
   return c == '*' || c == '/' || c == '+' || c == '-' || c == '%';
}

int isRelop(char c) {
   return c == '<' || c == '>' || c == '=' || c == '!';
}

int isBitwise(char c) {
   return c == '&' || c == '^' || c == '|';
}

int isKeyword(char arr[]) {
   for (int i = 0; i < 32; i++) {
      if (strcmp(keywords[i], arr) == 0)
         return 1;
   }
   return 0;
}

TOKEN makeToken(char type[], int lb, int fp, FILE * f1) {
   fseek(f1, lb, SEEK_SET);
   int n = fp - lb + 1;
   char * arr = (char * ) malloc(n * sizeof(char));
   TOKEN t;
   for (int i = 0; i < n; i++) {
      arr[i] = fgetc(f1);
   }

   strcpy(t.name, arr);
   strcpy(t.type, type);
   t.row = row;
   t.col = col;
   col += n;
   if (strcmp(type, "ID") == 0) {
      if (isKeyword(arr))
         strcpy(t.type, "Keyword");
   }
   return t;
}

TOKEN getNextToken(FILE * f1) {
   int lb = ftell(f1);
   int fp = lb;
   char ch = fgetc(f1);

   if (ch == ' ') {
      lb++;
      fp++;
      col++;
      ch = fgetc(f1);
   }
   if (ch == '\n') {
      row++;
      col = 0;
      lb++;
      fp++;
      ch = fgetc(f1);
   }
   if (isdigit(ch)) {
      col++;
      while (isdigit(ch)) {
         fp++;
         ch = fgetc(f1);
      }
      return makeToken("NUM", lb, fp - 1, f1);
   } else if (isSpecialSymbol(ch)) {
      fp++;
      return makeToken("SS", lb, fp - 1, f1);
   } else if (isArithmeticOp(ch)) {
      char prev = ch;
      ch = fgetc(f1);
      fp++;
      if (prev == '+' && ch == '+') {
         fp++;
         return makeToken("INC", lb, fp - 1, f1);
      } else if (prev == '-' && ch == '-') {
         fp++;
         return makeToken("DEC", lb, fp - 1, f1);
      } else
         return makeToken("ARITH", lb, fp - 1, f1);
   } else if (isRelop(ch)) {
      char prev = ch;
      ch = fgetc(f1);
      fp++;
      if (prev == '<' && ch == '=') {
         fp++;
         return makeToken("Relop", lb, fp - 1, f1);
      } else if (prev == '>' && ch == '=') {
         fp++;
         return makeToken("Relop", lb, fp - 1, f1);
      } else if (prev == '!' && ch == '=') {
         fp++;
         return makeToken("Relop", lb, fp - 1, f1);
      } else if (prev == '=' && ch == '=') {
         fp++;
         return makeToken("Relop", lb, fp - 1, f1);
      } else
         return makeToken("Relop", lb, fp - 1, f1);
   } else if (isBitwise(ch)) {
      fp++;
      char prev = ch;
      ch = fgetc(f1);
      fp++;
      if (prev == '&' && ch == '&') {
         fp++;
         return makeToken("Logical", lb, fp - 1, f1);
      } else if (prev == '|' && prev == '|') {
         fp++;
         return makeToken("Logical", lb, fp - 1, f1);
      } else
         return makeToken("Bitwise", lb, fp - 1, f1);
   } else if (ch == '"') {
      fp++;
      ch = fgetc(f1);
      while (ch != '"') {
         fp++;
         ch = fgetc(f1);
      }
      fp++;
      return makeToken("String", lb, fp - 1, f1);
   } else if (isalpha(ch)) {
      ch = fgetc(f1);
      fp++;
      while (isalpha(ch) || isdigit(ch) || ch == '_') {
         ch = fgetc(f1);
         fp++;
      }
      return makeToken("ID", lb, fp - 1, f1);
   }
   if (ch == EOF)
      exit(0);
}
