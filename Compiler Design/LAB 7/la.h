#ifndef LA_H
#define LA_H

typedef struct token {
   char name[100];
   char type[100];
   int row;
   int col;
}TOKEN;

TOKEN getNextToken();
#endif
