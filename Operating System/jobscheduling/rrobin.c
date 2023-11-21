#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct process {
  char name[10];
  int btime;
}
Process;

Process P[100];
int quantum;

void round_robin(int n) {
  int totaltime = 0;
  for (int i = 0; i < n; i++)
    totaltime += P[i].btime;
  int timer = 0;
  int k = 0;
  for (int i = 0; i <= totaltime / quantum; i++) {
    if (P[k].btime - quantum >= 0) {
      P[k].btime -= quantum;
      printf("Process %s runs from %d to %d\n", P[k].name, timer, timer + quantum);
      timer += quantum;
    } else if (P[k].btime != 0) {
      printf("Process %s runs from %d to %d\n", P[k].name, timer, timer + P[k].btime);
      timer += P[k].btime;
      P[k].btime = 0;
    } else
      i--;
    k = (k + 1) % n;
  }
}

void main() {
  quantum = 4;
  P[0].btime = 24;
  P[1].btime = 3;
  P[2].btime = 3;
  strcpy(P[0].name, "P0");
  strcpy(P[1].name, "P1");
  strcpy(P[2].name, "P2");
  round_robin(3);
}
