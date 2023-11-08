#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "la.h"

void Program();
void declarations();
void data_type();
void identifier_list();
void assign_stat();
TOKEN t;
FILE * f1;

void match() {
   t = getNextToken(f1);
}

void valid() {
   printf("SUCCESS\n");
   exit(1);
}

void invalid(char arr[]) {
   printf("Error %s\n", arr);

}

void Program() {
   if (strcmp(t.name, "main") == 0) {
      match();
      if (strcmp(t.name, "(") == 0) {
         match();
         if (strcmp(t.name, ")") == 0) {
            match();
            if (strcmp(t.name, "{") == 0) {
               match();
               declarations();
               assign_stat();
               if (strcmp(t.name, "}") == 0) {
                  return;
               } else
                  invalid("}");
            } else
               invalid("{");
         } else
            invalid(")");
      } else
         invalid("(");
   } else
      invalid("main");
}

void declarations() {
   data_type();
   identifier_list();
   if (strcmp(t.name, ";") == 0) {
      match();
      if (strcmp(t.name, "int") == 0 || strcmp(t.name, "char") == 0) {
         declarations();
      }
   } else {
      invalid(";");
      //match();
   }
}
void data_type() {

   if (strcmp(t.name, "int") == 0 || strcmp(t.name, "char") == 0)
      match();
   else
      invalid("int/char");
}

void identifier_list() {

   if (strcmp(t.type, "ID") == 0) {
      match();
      if (strcmp(t.name, ",") == 0) {
         identifier_list();
      }
   } else
      invalid("ID");
}

void assign_stat() {

   if (strcmp(t.type, "ID") == 0) {
      match();
      if (strcmp(t.name, "=") == 0) {
         match();
         if (strcmp(t.type, "ID") == 0) {
            match();
            if (strcmp(t.name, ";") == 0)
               match();
            else
               invalid(";");

         } else if (strcmp(t.type, "NUM") == 0) {
            match();
            if (strcmp(t.name, ";") == 0) {
               match();
            } else
               invalid(";");
         } else invalid("id/num");
      } else invalid("=");
   } else invalid("ID");
}

void main() {
   f1 = fopen("input1.c", "r");
   match();
   Program();
   valid();
}
