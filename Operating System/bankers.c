#include <stdio.h>
#include <stdlib.h>

int m = 3, n = 5;
int ind = 0;
int alloc[5][3] = { { 0, 1, 0 }, // P0 // Allocation Matrix
	        { 2, 0, 0 }, // P1
		{ 3, 0, 2 }, // P2
		{ 2, 1, 1 }, // P3
		{ 0, 0, 2 } }; // P4

int max[5][3] = { { 7, 5, 3 }, // P0 // MAX Matrix
 		{ 3, 2, 2 }, // P1
          	{ 9, 0, 2 }, // P2
		{ 2, 2, 2 }, // P3
		{ 4, 3, 3 } }; // P4

int avail[3] = {3,3,2};
int need[5][3];
int visit[5];
int safe[5];
void needCal() {
  for (int i = 0; i < n; i++) {
    safe[i] = -1;
    visit[i] = 0;
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      need[i][j] = max[i][j] - alloc[i][j];
    }
  }
}
void safeSeq() {
  int flag = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (visit[j] == 0) {
        flag = 0;
        for (int k = 0; k < m; k++) {
          if (need[j][k] > avail[k]) {
            flag = 1;
            break;
          }
        }
        if (flag == 0) {
          visit[j] = 1;
          safe[ind++] = j;
          for (int k = 0; k < m; k++) {
            avail[k]+=alloc[j][k]; 
          }
        }
      }
    }
  }
}

void display() {
  int flag = 0;
  for (int i = 0; i < n; i++) {
    if (visit[i] == 0) {
      flag = 1;
      break;
    }
  }
  if (flag == 1)
    printf("Not in safe state\n");
  else {
    printf("Safe State sequence\n");
    for (int i = 0; i < n; i++)
      printf("P%d ", safe[i]);
  }
}
int main() {
  needCal();
  safeSeq();
  display();
}
