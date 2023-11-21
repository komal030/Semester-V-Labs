#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
int arr[]={98,183,37,122,14,124,65,67};
  int n = sizeof(arr) / sizeof(arr[0]);
  int head = 53;
  int source = head;
  int temp = 0, dest, k = 0;
  while (k < n) {
  int diff = 99999;
  int index=-1;
    for (int i = 0; i < n; i++) {
      if (arr[i] != -1) {
        temp = abs(arr[i] - source);
        if (temp < diff) {
          index = i;
          dest = arr[i];
          diff=temp;
        }
      }
    }
    printf("Move from %d to %d with seek %d\n", source, dest, temp);
    source = arr[index];
    arr[index] = -1;
    k++;
  }
}
