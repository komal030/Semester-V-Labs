#include <stdio.h>
#include <stdlib.h>

typedef struct queue {
  int arr[100];
  int rear;
  int front;
}queue;

queue Q;
int size = 3;

int isFull() {
  if (Q.front == (Q.rear + 1) % size)
    return 1;
  else
    return 0;
}

int isEmpty() {
  if (Q.front == -1)
    return 1;
  else
    return 0;
}

void enqueue(int ele) {
  if (isFull()) {
    printf("isFull");
  } else if (isEmpty()) {
    Q.front = 0;
    Q.rear = 0;
  } else {
    Q.rear = (Q.rear + 1) % size;
  }
  Q.arr[Q.rear] = ele;
}

void dequeue() {
  if (isEmpty()) {
    printf("isEmpty");
  } else if (Q.rear == Q.front) {
    Q.front = (Q.front + 1) % size;
    Q.rear = -1;
    Q.front = -1;
  } else
    Q.front = (Q.front + 1) % size;
}

void display() {
  int i = Q.front;
  do {
    printf("%d ", Q.arr[i]);
    i = (i + 1) % size;
  } while (i != (Q.rear + 1) % size);
  printf("\n");
}

int isPresent(int ele, int frames[], int m) {
  int i = Q.front;
  do {
    if (ele == Q.arr[i])
      return 1;
    i = (i + 1) % size;
  } while (i != (Q.rear + 1) % size);
  return 0;
}

void fifo(int ref[], int frames[], int n, int m) {
  for (int i = 0; i < n; i++) {
    if (isPresent(ref[i], frames, m))
      printf("Page hit for element %d\n", ref[i]);
    else if (isFull()) {
      printf("Page fault for element %d\n", ref[i]);
      dequeue();
      enqueue(ref[i]);
    } else {
      printf("Page fault for element %d\n", ref[i]);
      enqueue(ref[i]);
    }
    display();
  }
}

int main() {
  Q.rear = -1;
  Q.front = -1;
  int n = 20;
  int ref[] = = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
  int m = 3;
  int frames[] = {-1,-1,-1};
  fifo(ref, frames, n, m);
}
