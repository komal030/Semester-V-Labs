#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

int n;
int m;

void * thread_handler1(void * param) {
  int ** num = (int ** ) param;
  int * crr;
  crr = (int * ) malloc(n * sizeof(int));
  for (int i = 0; i < n; i++) {
    int sum = 0;
    for (int j = 0; j < m; j++) {
      sum = sum + num[i][j];
    }
    crr[i] = sum;
  }
  return (void * ) crr;
}

void * thread_handler2(void * param) {
  int ** num = (int ** ) param;
  int * crr;
  crr = (int * ) malloc(m * sizeof(int));
  for (int i = 0; i < m; i++) {
    int sum = 0;
    for (int j = 0; j < n; j++) {
      sum = sum + num[j][i];
    }
    crr[i] = sum;
  }
  return (void * ) crr;
}

int main() {
  printf("Enter matrix dimensions\n");
  scanf("%d", & n);
  scanf("%d", & m);
  int ** arr = (int ** ) malloc(n * sizeof(int * ));
  printf("Enter matrix elements\n");
  for (int i = 0; i < n; i++) {
    arr[i] = (int * ) malloc(m * sizeof(int));
    for (int j = 0; j < m; j++) {
      scanf("%d", & arr[i][j]);
    }
  }
  pthread_t thread1;
  pthread_create( & thread1, 0, & thread_handler1, (void * ) arr);
  int * rowsum = (int * ) malloc(n * sizeof(int));

  pthread_join(thread1, (void ** ) & rowsum);
  for (int i = 0; i < n; i++) {
    printf("ROW %d sum: %d\n", (i + 1), rowsum[i]);
  }

  pthread_t thread2;
  pthread_create( & thread2, 0, & thread_handler2, (void * ) arr);
  int * colsum = (int * ) malloc(m * sizeof(int));

  pthread_join(thread2, (void ** ) & colsum);
  for (int i = 0; i < m; i++) {
    printf("COL %d sum: %d\n", (i + 1), colsum[i]);
  }

}
