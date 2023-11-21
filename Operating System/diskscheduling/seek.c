#include <stdio.h>

#include <stdlib.h>

#include <string.h>

int main() {
  int arr[9] = {
    98,
    183,
    37,
    122,
    14,
    124,
    65,
    67
  };
  int n = sizeof(arr) / sizeof(int);
  int head = 53;
  arr[8] = head;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (arr[j] > arr[j + 1]) {
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
  for (int i = 0; i < n; i++)
    printf("%d ", arr[i]);
  printf("\n");
  int index = -1;
  for (int i = 0; i < n; i++)
    if (arr[i] == head) {
      index = i;
      break;
    }
  int temp;
  for (int i = index; i < n - 1; i++) {
    temp = abs(arr[i] - arr[i + 1]);
    printf("Move from %d to %d with seek %d\n", arr[i], arr[i + 1], temp);

  }
  temp = abs(arr[n - 1] - arr[0]);
  printf("Move from %d to %d with seek %d\n", arr[n - 1], arr[0], temp);

  for (int i = 0; i < index; i++) {
    temp = abs(arr[i] - arr[i + 1]);
    printf("Move from %d to %d with seek %d\n", arr[i], arr[i + 1], temp);

  }
}
