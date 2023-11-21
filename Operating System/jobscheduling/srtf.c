#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct process {
  char name[100];
  int btime;
  int atime;
}
Process;
Process P[100];

void sort(int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (P[j].btime > P[j + 1].btime) {
        Process temp = P[j];
        P[j] = P[j + 1];
        P[j + 1] = temp;
      }
    }
  }
}

void wait(int n) {
  int totaltime = 0;
  for (int i = 0; i < n; i++)
    totaltime += P[i].btime;
  sort(n);
  int timer = 0;
  while (timer < totaltime) {
    int minindex = -1;
    int minval = INT_MAX;
    for (int i = 0; i < n; i++) {
      if (P[i].btime != 0 && timer >= P[i].atime && P[i].btime < minval) {
        minindex = i;
        minval = P[i].btime;
      }
    }
    printf("Process %s ran from t = %d to t = %d\n", P[minindex].name, timer, timer + 1);
    P[minindex].btime--;
    timer++;
  }
}

int main() {
  strcpy(P[0].name, "P0");
  P[0].btime = 8;
  P[0].atime = 0;
  strcpy(P[1].name, "P1");
  P[1].btime = 4;
  P[1].atime = 1;
  strcpy(P[2].name, "P2");
  P[2].btime = 9;
  P[2].atime = 2;
  strcpy(P[3].name, "P3");
  P[3].btime = 5;
  P[3].atime = 3;
  wait(4);
  return 0;
}

/*int main() {
    printf("Enter number of processes: ");
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        char temp[100];
        sprintf(temp, "P%d", i);
        strcpy(P[i].name, temp);
        printf("Enter burst time of P%d: ", i);
        scanf("%d", &P[i].btime);
        printf("Enter arrival time of P%d : ", i);
        scanf("%d", &P[i].atime);
    }
    wait(n);
    return 0;
}*/
