#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <pthread.h>

typedef struct num {
  int n;
  int arr[100];
}NUM;

void * thread_handler(void * param) {
  NUM * num = (NUM * ) param;
  int * sum = (int * ) malloc(sizeof(int));
  * sum = 0;
  for (int i = 0; i < num -> n; i++) {
    if (num -> arr[i] > 0)
      *
      sum = * sum + num -> arr[i];
  }

  return (void * ) sum;
}

int main() {
  NUM * num = (NUM * ) malloc(sizeof(NUM));
  printf("Enter number of elements: ");
  int n;
  scanf("%d", & num -> n);
  printf("Enter the elements:\n");
  for (int i = 0; i < num -> n; i++) {
    scanf("%d", & num -> arr[i]);
  }
  pthread_t thread;
  pthread_create( & thread, 0, & thread_handler, (void * ) num);
  int * sum = malloc(sizeof(int));
  pthread_join(thread, (void ** ) & sum);
  printf("SUM %d", * sum);
}
