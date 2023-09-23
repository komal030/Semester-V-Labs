#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

typedef struct token {
  char name[100];
  char type[100];
  int row;
  int col;
}TOKEN;

char keywords[][32] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "int", "long", "register", "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
};
TOKEN token[1000];
int p = 0;

void makeToken(char brr[], char crr[], int r, int c) {
  strcpy(token[p].name, brr);
  strcpy(token[p].type, crr);
  token[p].row = r;
  token[p].col = c;
  p++;
}
void removeString(char line[], char arr[]) {
  int k = 0;
  int n = strlen(line);

  for (int i = 0; i < n; i++) {
    if (line[i] == '"') {
      i++;
      while (i < n && line[i] != '"') {
        i++;
      }
    } else {
      arr[k++] = line[i];
    }
  }
  arr[k] = '\0';
}

void display() {

  for (int i = 0; i < p; i++) {
    printf("<%s , %s , %d , %d>\n", token[i].name, token[i].type, token[i].row, token[i].col);
  }

}
void ArithmeticOp(char line[], int row) {
  char arr[256];
  removeString(line, arr);

  for (int i = 0; i < strlen(arr); i++) {
    if (arr[i] == '/') {
      makeToken("/", "Arithmetic", row, i);
    }
    if (arr[i] == '*') {
      makeToken("*", "Arithmetic", row, i);
    }
    if (arr[i] == '+' && (i + 1 >= strlen(arr) || arr[i + 1] != '+')) {
      makeToken("+", "Arithmetic", row, i);
    } else if (arr[i] == '+' && arr[i + 1] == '+') {
      makeToken("++", "Arithmetic", row, i);
      i++;
    }
    if (arr[i] == '-' && (i + 1 >= strlen(arr) || arr[i + 1] != '-')) {
      makeToken("-", "Arithmetic", row, i);
    } else if (arr[i] == '-' && arr[i + 1] == '-') {
      makeToken("--", "Arithmetic", row, i);
      i++;
    }
  }
}

int isKeyword(char brr[]) {
  for (int i = 0; i < 32; i++) {
    if (strcmp(brr, keywords[i]) == 0)
      return 1;
  }
  return 0;
}

void Keyword(char line[], int row) {
  char arr[256];
  removeString(line, arr);

  char * word = strtok(arr, " \n");
  int start = 1;
  while (word != NULL) {
    if (isKeyword(word))
    {
      makeToken(word, "Keyword", row, start);
      }
       start = start + strlen(word)+1;
    word = strtok(NULL, " \n");
  }
}

void Identifier(char line[], int row) {
  char arr[256];
  removeString(line, arr);
  char * word = strtok(arr, " \n");
  int start = 1;
  while (word != NULL) {
    if (isalpha(word[0]) && !isKeyword(word))
    {
      makeToken(word, "Identifier", row, start);
      }
    start = start + strlen(word)+1;
    word = strtok(NULL, " \n");
  }
}

void Numerical(char line[], int row) {
  char arr[256];
  removeString(line, arr);
  for (int i = 0; i < strlen(arr); i++) {
    char word[20];
    int k = 0, start;
    while (isdigit(arr[i])) {
      start = i;
      word[k++] = arr[i++];
    }

    if (k > 0) {
      word[k] = '\0';
      makeToken(word, "Numerical", row, start);
    }

  }
}
int isNotRelational(char c) {
  if (c != '!' && c != '>' && c != '<' && c != '=')
    return 1;
  return 0;
}
void RelationalOp(char line[], int row) {
  char arr[256];
  removeString(line, arr);

  for (int i = 0; i < strlen(arr) - 1; i++) {
    char c = arr[i];
    char ch = arr[i + 1];
    if (c == '<' && ch == '=')
      makeToken("<=", "Relational", row, i);

    if (c == '>' && ch == '=')
      makeToken(">=", "Relational", row, i);

    if (c == '!' && ch == '=')
      makeToken("!=", "Relational", row, i);

    if (c == '=' && ch == '=')
      makeToken("==", "Relational", row, i);

    if (c == '<' && isNotRelational(ch))
      makeToken("<", "Relational", row, i);

    if (c == '>' && isNotRelational(ch))
      makeToken(">", "Relational", row, i);
  }
}
void SpecialSymbol(char line[], int row) {
  char arr[256];
  removeString(line, arr);
  for (int i = 0; i < strlen(arr); i++) {
    char ch = arr[i];
    if (ch == '(')
      makeToken("(", "Special Symbol", row, i);
    if (ch == ')')
      makeToken(")", "Special Symbol", row, i);
    if (ch == ';')
      makeToken(";", "Special Symbol", row, i);
    if (ch == '[')
      makeToken("[", "Special Symbol", row, i);
    if (ch == ']')
      makeToken("]", "Special Symbol", row, i);
    if (ch == ']')
      makeToken("{", "Special Symbol", row, i);
    if (ch == '{')
      makeToken("{", "Special Symbol", row, i);
    if (ch == '}')
      makeToken("}", "Special Symbol", row, i);
    if (ch == ',')
      makeToken(",", "Special Symbol", row, i);
  }
}

void StringLiteral(char line[], int row) {
  for (int i = 0; i < strlen(line); i++) {
    char word[100];
    int k = 0;

    if (line[i] == '"') {
      int start = i;
      i++;
      while (line[i] != '"')
        word[k++] = line[i++];
      word[k] = '\0';
      makeToken(word, "String literal", row, start);
    }
  }
}
void Logical(char line[], int row) {
  char arr[256];
  removeString(line, arr);
  for (int i = 0; i < strlen(arr) - 1; i++) {
    char c = arr[i];
    char ch = arr[i + 1];
    if (c == '&' && ch == '&')
      makeToken("&&", "Logical", row, i);
    if (c == '|' && ch == '|')
      makeToken("||", "Logical", row, i);
    if (c == '!' && isNotRelational(ch))
      makeToken("!", "Logical", row, i);
  }
}

typedef struct table {
  char lex_name[100];
  char lex_type[100];
}
TABLE;
TABLE table[100009];

int hashfunc(TOKEN t) {
  int p = 31;
  int m = 100009;
  char temp[30];
  strcpy(temp, t.name);
  //printf("%s",temp);
  long sum = 0;
  for (int i = 0; i < strlen(temp); i++) {
    sum = sum + (int) temp[i] * pow(p, i);
  }
  int hash = sum % m;
  if (hash < 0 || hash >= 100009) {
    printf("%d Error: Invalid hash value generated!\n", hash);
    exit(1); // Exit the program due to error
  }
  return hash;
}

void addEntry(int hash, char tname[], char vartype[]) {
  strcpy(table[hash].lex_name, tname);
  strcpy(table[hash].lex_type, vartype);
}

int containsEntry(TOKEN t) {
  int hash = hashfunc(t);
  if (strcmp(table[hash].lex_name, t.name) == 0)
    return 1;
  else
    return 0;
}

void printTable() {
  for (int i = 0; i < 100009; i++) {
    if (strcmp(table[i].lex_name, "") != 0)
      printf("%s\t\t\t%s\n", table[i].lex_name, table[i].lex_type);
  }
}
void makeTable() {
  printf("NAME\t\t\tTYPE\n\n");
  for (int i = 0; i < p; i++) {
    TOKEN t = token[i];
    if (strcmp(token[i].type, "Identifier") == 0) {
      int hash = hashfunc(t);
      if (i + 1 < p) {
        TOKEN tnext = token[i + 1];
        if (strcmp(tnext.name, "(") == 0)
          addEntry(hash, t.name, "Function");

        else
          addEntry(hash, t.name, "Variable");
      } else
        addEntry(hash, t.name, "Variable");

    }
  }
}

void sortTokens() {
  for (int i = 0; i < p - 1; i++) {
    for (int j = 0; j < p - i - 1; j++) {
      if (token[j].row == token[j + 1].row) {
        if (token[j].col > token[j + 1].col) {
          TOKEN temp = token[j];
          token[j] = token[j + 1];
          token[j + 1] = temp;
        }
      }
    }
  }
}

int main() {
  FILE * f1;
  f1 = fopen("input.c", "r");
  if (f1 == NULL) {
    printf("Cannot open file\n");
    exit(1);
  }
  char buff[500];
  int row = 1;
  while (fgets(buff, 500, f1)) {
    ArithmeticOp(buff, row);
    Keyword(buff, row);
    Identifier(buff, row);
    Numerical(buff, row);
    RelationalOp(buff, row);
    SpecialSymbol(buff, row);
    Logical(buff, row);
    StringLiteral(buff, row);
    row++;
  }
  sortTokens();
  display();
  makeTable();
  printTable();
  fclose(f1);
  return 0;
}
