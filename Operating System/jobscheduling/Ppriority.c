#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct process {
  char name[10];
  int atime;
  int btime;
  int priority;
}
Process;

Process P[100];
int waittime[100];

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

void preemptive_priority(int n) {
  sort(n);
  int totaltime = 0;
  for (int i = 0; i < n; i++) {
    totaltime += P[i].btime;
    waittime[i] = 0;
  }
  int timer = 0;
  while (timer < totaltime) {
    int minpri = 999;
    int minindex = -1;
    for (int i = 0; i < n; i++) {
      if (P[i].btime > 0 && P[i].atime <= timer && P[i].priority < minpri) {
        minpri = P[i].priority;
        minindex = i;
      }
    }
    printf("Process %s ran from %d to %d\n", P[minindex].name, timer, timer + 1);
    P[minindex].btime--;
    timer++;
    for (int i = 0; i < n; i++) {
      if (minindex != i && P[i].btime != 0 && P[i].atime < timer)
        waittime[i] = waittime[i] + 1;
    }
  }
  double avgwait = 0;
  for (int i = 0; i < n; i++) {
    avgwait += waittime[i];
    printf("Wait time for %s : %d\n", P[i].name, waittime[i]);
  }
  avgwait /= n;
  printf("Average waittime %lf\n", avgwait);
}
int main() {
  strcpy(P[0].name, "P1");
  P[0].btime = 6;
  P[0].atime = 0;
  P[0].priority = 3;
  strcpy(P[1].name, "P2");
  P[1].btime = 8;
  P[1].atime = 1;
  P[1].priority = 1;
  strcpy(P[2].name, "P3");
  P[2].btime = 4;
  P[2].atime = 2;
  P[2].priority = 2;
  preemptive_priority(3);
  return 0;
}
