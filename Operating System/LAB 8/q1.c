#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

void * thread_handler(void * param) {
  int n = (int) param;
  int * series=(int * ) malloc(n * sizeof(int));;
  int a = 0, b = 1;
  series[0] = a;
  series[1] = b;
  for (int i = 2; i < n; i++) {
    int c = a + b;
    a = b;
    b = c;
    series[i] = c;
  }
  return (void * ) series;
}

int main() {
  pthread_t thread;
  printf("Enter N: ");
  int n;
  scanf("%d", & n);
  pthread_create( & thread, 0, & thread_handler, (void * ) n);
  int * series = (int * ) malloc(n * sizeof(int));
  pthread_join(thread, (void ** ) & series);
  for (int i = 0; i < n; i++)
    printf("%d ", *(series + i));
  printf("\n");
}
