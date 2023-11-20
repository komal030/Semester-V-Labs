#include <stdio.h>
#include <stdlib.h>

int m = 3;
int frames[] = {-1,-1,-1}

int k = 0;
int n = 20;
int isPresent(int ele) {
  for (int i = 0; i < m; i++) {
    if (ele == frames[i])
      return 1;
  }
  return 0;
}

int isFull() {
  if (frames[k] != -1)
    return 1;
  else
    return 0;
}

void display() {
  for (int i = 0; i < k; i++) {
    printf("%d ", frames[i]);
  }
  printf("\n");
}

void finddistance(int k, int * distance, int ref[]) {
  for (int i = 0; i < m; i++) {
    for (int j = k; j < n; j++) {
      if (ref[j] == frames[i]) {
        distance[i] = j;
        break;
      }
    }
  }
}

int mostfar(int k, int ref[]) {
  int * distance = (int * ) malloc(m * sizeof(int));
  for (int i = 0; i < m; i++)
    distance[i] = 9999;

  finddistance(k, distance, ref);
  int max = 0;
  int index = 0;
  for (int i = 0; i < m; i++)
    if (distance[i] > max) {
      max = distance[i];
      index = i;
    }
  return index;
}

void optimal(int ref[]) {
  for (int i = 0; i < n; i++) {
    if (isPresent(ref[i])) {
      printf("Page hit at %d\n", ref[i]);
    } else if (k != m) {
      printf("Page fault at %d\n", ref[i]);
      frames[k++] = ref[i];
    } else {
      printf("Page fault at %d\n", ref[i]);
      int index = mostfar(i, ref);
      frames[index] = ref[i];
    }
    display();
  }
}

int main() {
  int ref[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
  optimal(ref);
}
