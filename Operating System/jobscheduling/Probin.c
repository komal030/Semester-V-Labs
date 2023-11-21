#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct process {
  char name[10];
  int btime;
  int atime;
  int priority;
}
Process;

Process P[100];
int quantum = 10;

void sort(int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (P[j].atime > P[j + 1].atime) {
        Process temp = P[j];
        P[j] = P[j + 1];
        P[j + 1] = temp;
      }
    }
  }
}

void round_robin(int n) {
  int iterations = n;
  int timer = 0;
  sort(n);
  while (iterations > 0) {
    int minp = 9999;
    int minindex = -1;
    int lowatime = 999;

    for (int i = 0; i < n; i++) {
      if (lowatime > P[i].atime && P[i].atime > timer)
        lowatime = P[i].atime;
      if (P[i].atime <= timer && P[i].priority < minp && P[i].btime != 0) {
        minp = P[i].priority;
        minindex = i;
      }
    }
    if (P[minindex].btime - quantum >= 0) {
      P[minindex].btime -= quantum;
      printf("Process %s runs from %d to %d\n", P[minindex].name, timer, timer + quantum);
      timer += quantum;
      if (P[minindex].btime == 0)
        iterations--;
    } else if (P[minindex].btime != 0) {
      printf("Process %s runs from %d to %d\n", P[minindex].name, timer, timer + P[minindex].btime);
      timer += P[minindex].btime;
      P[minindex].btime = 0;
      iterations--;
    } else {
      int tadd = lowatime - timer;
      printf("Process Pidle runs from %d to %d\n", timer, lowatime);
      timer = lowatime;
    }
  }
}

void main() {
  P[0].btime = 20;
  P[1].btime = 25;
  P[2].btime = 25;
  P[3].btime = 15;
  P[4].btime = 10;
  P[5].btime = 10;
  P[0].atime = 0;
  P[1].atime = 25;
  P[2].atime = 30;
  P[3].atime = 60;
  P[4].atime = 100;
  P[5].atime = 105;
  P[0].priority = 40;
  P[1].priority = 30;
  P[2].priority = 30;
  P[3].priority = 35;
  P[4].priority = 5;
  P[5].priority = 10;
  strcpy(P[0].name, "P1");
  strcpy(P[1].name, "P2");
  strcpy(P[2].name, "P3");
  strcpy(P[3].name, "P4");
  strcpy(P[4].name, "P5");
  strcpy(P[5].name, "P6");
  round_robin(6);
}
