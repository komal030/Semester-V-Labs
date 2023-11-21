#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Block * blockptr;
typedef struct Block {
  int size;
  int allocated;
  blockptr next;
}
Block;

typedef struct process {
  int size;
  char name[10];
}
Process;

Process P[10];
int n = 5;
Block * initializeMem() {
  Block * head = (Block * ) malloc(sizeof(Block));
  Block * m1 = (Block * ) malloc(sizeof(Block));
  Block * m2 = (Block * ) malloc(sizeof(Block));
  Block * m3 = (Block * ) malloc(sizeof(Block));
  Block * m4 = (Block * ) malloc(sizeof(Block));
  head -> next = m1;
  m1 -> next = m2;
  m2 -> next = m3;
  m3 -> next = m4;
  m4 -> next = NULL;
  head -> size = 200;
  m1 -> size = 70;
  m2 -> size = 250;
  m3 -> size = 20;
  m4 -> size = 400;
  Block * temp = head;
  while (temp != NULL) {
    printf("%d\n", temp -> size);
    temp -> allocated = 0;
    temp = temp -> next;
  }
  return head;
}

void initializeProcess(Process list[]) {
  strcpy(list[0].name, "P0");
  strcpy(list[1].name, "P1");
  strcpy(list[2].name, "P2");
  strcpy(list[3].name, "P3");
  strcpy(list[4].name, "P4");
  list[0].size = 300;
  list[1].size = 10;
  list[2].size = 60;
  list[3].size = 5;
  list[4].size = 25;
}
int isEmpty(Block * head) {
  if (head -> allocated == 0)
    return 1;
  else
    return 0;
}

int isCheck(Block * head, Process p) {
  if (head -> size - p.size >= 0)
    return 1;
  else
    return 0;
}

void bestfit(Block * first) {
  for (int i = 0; i < n; i++) {
    int diff = 9999;
    Block * index = (Block * ) malloc(sizeof(Block));
    Block * head = first;
    while (head != NULL) {
      if (isEmpty(head)) {
        if (isCheck(head, P[i])) {
          if (diff > head -> size - P[i].size) {
            diff = head -> size - P[i].size;
            index = head;

          }
        }
      }
      head = head -> next;
    }
    if (index == NULL) {
      printf("Cannot insert Process P%d\n", i);
    } else {
      printf("Process P%d of size %d inserted at size %d\n", i, P[i].size, index -> size);
      index -> allocated = P[i].size;
    }
  }
}

void worstfit(Block * first) {
  for (int i = 0; i < n; i++) {
    int diff = -1;
    Block * index = (Block * ) malloc(sizeof(Block));
    Block * head = first;
    while (head != NULL) {
      if (isEmpty(head)) {
        if (isCheck(head, P[i])) {
          if (diff < head -> size - P[i].size) {
            diff = head -> size - P[i].size;
            index = head;
          }
        }
      }
      head = head -> next;
    }
    if (index -> size == 0) {
      printf("Cannot insert Process P%d\n", i);
    } else {
      printf("Process P%d of size %d inserted at size %d\n", i, P[i].size, index -> size);
      index -> allocated = P[i].size;
    }
  }
}

void firstfit(Block * first) {
  for (int i = 0; i < n; i++) {
    int flag = 0;
    Block * head = first;
    while (head != NULL) {
      if (isEmpty(head) && isCheck(head, P[i])) {
        printf("Process P%d of size %d inserted at size %d\n", i, P[i].size, head -> size);
        head -> allocated = P[i].size;
        flag = 1;
        break;
      }
      head = head -> next;
    }
    if (flag == 0) {
      printf("Cannot insert Process P%d\n", i);
    }
  }
}

int main() {
  initializeProcess(P);
  Block * head = initializeMem();
  firstfit(head);
  //bestfit(head);
  //worstfit(head);
  return 0;
}
