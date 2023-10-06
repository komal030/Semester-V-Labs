#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

int n;
int m;
int p;
typedef struct num {
  int arr[10][10];
  int brr[10][10];
}
NUM;

void * thread_handler(void * param) {
  NUM* num = (NUM * ) param;
  int ** crr;
  crr = (int ** ) malloc(n * sizeof(int * ));
  for (int i = 0; i < n; i++) {
    crr[i] = (int * ) malloc(p * sizeof(int));
    for (int j = 0; j < p; j++) {
      for (int k = 0; k < m; k++) {
        crr[i][j] = crr[i][j] + num -> arr[i][k] * num -> brr[k][j];
      }
    }
  }
  return (void * ) crr;
}

int main() {
  NUM * num = (NUM * ) malloc(sizeof(NUM));
  printf("Enter matrix 1 and 2 size\n");
  scanf("%d", & n);
  scanf("%d", & m);
  scanf("%d", & p);
  printf("Enter matrix 1 elements\n");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      scanf("%d", & num -> arr[i][j]);
    }
  }
  printf("\nEnter matrix 2 elements\n");
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < p; j++) {
      scanf("%d", & num -> brr[i][j]);
    }
  }
  pthread_t thread;
  pthread_create( & thread, 0, & thread_handler, (void * ) num);
  int ** crr = (int ** ) malloc(n * sizeof(int * ));
  for (int i = 0; i < n; i++)
    crr[i] = (int * ) malloc(p * sizeof(int));
  pthread_join(thread, (void ** ) & crr);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < p; j++) {
      printf("%d ", crr[i][j]);
    }
    printf("\n");
  }
}
