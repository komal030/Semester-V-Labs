#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char str[100];
int curr;

void T();
void S();
void Tprime();
void valid() {
  printf("SUCCESS");
  exit(0);
}

void invalid() {
  printf("FAIL");
  exit(0);
}

void S() {
  if (str[curr] == 'a') {
    curr++;
    return;
  } else if (str[curr] == '>') {
    curr++;
    return;
  } else if (str[curr] == '(') {
    curr++;
    T();
    if (str[curr] == ')') {
      curr++;
      return;
    } else
      invalid();
  } else
    invalid();
}

void T() {
  S();
  Tprime();
}

void Tprime() {
  if (str[curr] == ',') {
    curr++;
    S();
    Tprime();
  }

}

void main() {
  printf("\nEnter input String: ");
  scanf("%s", str);
  S();
  if (str[curr] == '$')
    valid();
  else
    invalid();
}
