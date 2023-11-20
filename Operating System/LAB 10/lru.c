#include <stdio.h>
#include <stdlib.h>


int k = 0;
int m = 3;
int n = 20;
int ref[20];

int isPresent(int ele, int frame[]) {
  for (int i = 0; i < k; i++) {
    if (ele == frame[i])
      return 1;
  }
  return 0;
}

int isFull() {
  if (k == m)
    return 1;
  else
    return 0;
}

int mindist(int ref[], int frame[], int index) {
  int * distance = (int * ) malloc(m * sizeof(int));
  for (int i = 0; i < m; i++)
    distance[i] = 9999;
  for (int i = 0; i < m; i++) {
    for (int j = index - 1; j >= 0; j--) {
      if (frame[i] == ref[j]) {
        distance[i] = j;
        break;
      }
    }
  }
  int max = distance[0];
  int in = 0;
  for (int i = 0; i < m; i++) {
    if (distance[i] < max) {
      max = distance[i];
      in = i;
    }
  }
  return in;
}
void display(int frame[]) {
  for (int i = 0; i < k; i++)
    printf("%d ", frame[i]);
  printf("\n");
}

void lru(int ref[], int frame[]) {
  for (int i = 0; i < n; i++) {
    if (isPresent(ref[i], frame)) {
      printf("Page hit at %d\n", ref[i]);
    } else if (!isFull()) {
      printf("Page fault at %d\n", ref[i]);
      frame[k++] = ref[i];
    } else {
      printf("Page fault at %d\n", ref[i]);
      int index = mindist(ref, frame, i);
      frame[index] = ref[i];
    }
    display(frame);
  }
}
int main() {
  int ref[] ={7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
  int frame[] = {-1,-1,-1};
  lru(ref, frame);
  return 0;
}
