#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Token {
   char token_name[50];
   int row;
   int col;
}Token;

char *specialSymbols[] = {
    "+", "-", "*", "/", "=", "==", "<", "<=", ">", ">=", "<>", "(", ")", "{", "}", "[", "]", ",", ";", ":", ".", "&", "|", "~", "^", "%"
};

char *logicalOperators[] = {
    "&&", "||", "!"
};

char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default",
    "do", "double", "else", "enum", "extern", "float", "for", "goto",
    "if", "int", "long", "register", "return", "short", "signed",
    "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned",
    "void", "volatile", "while"
};
Token arr[100];
int k = 0;

void initToken(char name[], int r, int c) {
  strcpy(arr[k].token_name, name);
  arr[k].row = r;
  arr[k].col = c;
  k++;
}

int isSpecialSymbol(char * word) {
  int numSpecialSymbols = sizeof(specialSymbols) / sizeof(specialSymbols[0]);
  for (int i = 0; i < numSpecialSymbols; i++) {
    if (strcmp(word, specialSymbols[i]) == 0) {
      return 1; // It's a special symbol
    }
  }
  return 0; // Not a special symbol
}

int isKeyword(char * word) {
  int numKeywords = sizeof(keywords) / sizeof(keywords[0]);
  for (int i = 0; i < numKeywords; i++) {
    if (strcmp(word, keywords[i]) == 0) {
      return 1; // It's a keyword
    }
  }
  return 0; // Not a keyword
}
void isRelationalop(char s[], int row) {
  int n = strlen(s);
  for (int i = 0; i < n; i++) {
    char c = s[i];
    if (c == '=') {
      char c1 = s[i + 1];
      if (c1 == '=') {
        initToken("RELOP:==", row, i + 1);
        i++;
      }
    } else if (c == '<') {
      char c1 = s[i + 1];
      if (c1 == '=') {
        initToken("RELOP:<=", row, i + 1);
        i++;
      } else if (c1 == '>') {
        initToken("RELOP:<>", row, i + 1);
        i++;
      } else {
        initToken("RELOP:<", row, i);
      }
    } else if (c == '>') {
      char c1 = s[i + 1];
      if (c1 == '=') {
        initToken("RELOP:>=", row, i + 1);
        i++;
      } else {
        initToken("RELOP:>", row, i);
      }
    }
  }
}

void isStringLiteral(char s[], int row) {
  int n = strlen(s);
  for (int i = 0; i < n; i++) {
    if (s[i] == '"') {
      int j = i + 1;
      while (j < n && s[j] != '"') {
        j++;
      }
      if (j < n && s[j] == '"') {
        initToken("STRING_LITERAL", row, i + 1);
        i = j; // Move the index to the end of the string literal
      }
    }
  }
}

void isAssignmentop(char s[], int row) {
  int n = strlen(s);
  for (int i = 0; i < n; i++) {
    char c = s[i];
    if (c == '=') {
      char c1 = s[i + 1];
      if (c1 != '=') {
        initToken("ASSIGN:=", row, i);
      }
    } else if (c == '+') {
      char c1 = s[i + 1];
      if (c1 == '=') {
        initToken("ASSIGN:+=", row, i + 1);
        i++;
      } else {
        initToken("ASSIGN:+", row, i);
      }
    } else if (c == '-') {
      char c1 = s[i + 1];
      if (c1 == '=') {
        initToken("ASSIGN:-=", row, i + 1);
        i++;
      } else {
        initToken("ASSIGN:-", row, i);
      }
    } else if (c == '*') {
      char c1 = s[i + 1];
      if (c1 == '=') {
        initToken("ASSIGN:*=", row, i + 1);
        i++;
      } else {
        initToken("ASSIGN:*", row, i);
      }
    } else if (c == '/') {
      char c1 = s[i + 1];
      if (c1 == '=') {
        initToken("ASSIGN:/=", row, i + 1);
        i++;
      } else {
        initToken("ASSIGN:/", row, i + 1);
      }
    }

  }
}

int isLogicalOperator(char * word) {
  int numLogicalOperators = sizeof(logicalOperators) / sizeof(logicalOperators[0]);
  for (int i = 0; i < numLogicalOperators; i++) {
    if (strcmp(word, logicalOperators[i]) == 0) {
      return 1; // It's a logical operator
    }
  }
  return 0; // Not a logical operator
}

int isValidIdentifier(char * word) {
  int len = strlen(word);
  if (len == 0 || !isalpha(word[0])) {
    return 0; // Identifier must start with a letter
  }
  for (int i = 1; i < len; i++) {
    if (!isalnum(word[i]) && word[i] != '_') {
      return 0; // Invalid character in the identifier
    }
  }
  return 1; // Valid identifier
}

int isNumericalConstant(char * word) {
  int len = strlen(word);
  for (int i = 0; i < len; i++) {
    if (!isdigit(word[i]) && word[i] != '.') {
      return 0; // Not a numerical constant
    }
  }
  return 1; // Numerical constant
}

void identifyIdentifiers(char s[], int row) {
  char * token = strtok(s, " \t\n");
  while (token != NULL) {
    if (!isKeyword(token) && isValidIdentifier(token)) {
      initToken("IDENTIFIER", row, (int)(token - s) + 1);
    }
    token = strtok(NULL, " \t\n");
  }
}
int main() {
  FILE * f1;
  char filename[100];
  f1 = fopen("input.c", "r");
  if (f1 == NULL) {
    printf("Cannot open file");
    exit(1);
  }
  int r = 1;
  char line[256];
  while (fgets(line, 256, f1) != NULL) {
    isRelationalop(line, r);
    isAssignmentop(line, r);
    isStringLiteral(line, r);
    identifyIdentifiers(line, r);

    char * token = strtok(line, " \t\n");
    while (token != NULL) {
      if (isKeyword(token)) {
        initToken("KEYWORD", r, (int)(token - line) + 1);
      } else if (isLogicalOperator(token)) {
        initToken("LOGICAL_OPERATOR", r, (int)(token - line) + 1);
      } else if (isSpecialSymbol(token)) {
        initToken("SPECIAL_SYMBOL", r, (int)(token - line) + 1);
      }
      token = strtok(NULL, " \t\n");
    }

    r++;
  }

  for (int i = 0; i < k; i++) {
    printf("<%s, %d, %d>\n", arr[i].token_name, arr[i].row, arr[i].col);
  }

  fclose(f1);
}
