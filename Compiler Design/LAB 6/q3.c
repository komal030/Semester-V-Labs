#include <stdio.h>

#include <stdlib.h>

#include <string.h>

char str[100];
int curr;

void S();
void A();
void Aprime();
void B();

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
    A();
    if (str[curr] == 'c') {
      curr++;
      B();
      if (str[curr] == 'e') {
        curr++;
        return;
      } else
        invalid();
    } else
      invalid();
  } else
    invalid();
}
void A() {
  if (str[curr] == 'b') {
    curr++;
    Aprime();
  } else
    invalid();
}

void Aprime() {
  if (str[curr] == 'b') {
    curr++;
    Aprime();
  }
}

void B() {
  if (str[curr] == 'd') {
    curr++;
    return;
  } else
    return;
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
