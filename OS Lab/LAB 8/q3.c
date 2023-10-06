#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>

typedef struct num {
  int a;
  int b;
}
NUM;

int isPrime(int n) {
  for (int i = 2; i < n; i++) {
    if (n % i == 0)
      return 0;
  }
  return 1;
}

void * thread_handler(void * param) {
  NUM * num = (NUM * ) param;
  int * sequence = malloc(100 * sizeof(int));
  int k = 0;
  for (int i = num -> a; i < num -> b; i++) {
    if (isPrime(i))
      sequence[k++] = i;
  }
  sequence[k] = -1;
  return (void * ) sequence;
}
int main() {
  NUM * num = (NUM * ) malloc(sizeof(NUM));

  printf("Enter first number: ");
  scanf("%d", & num -> a);
  printf("Enter ending number: ");
  scanf("%d", & num -> b);

  pthread_t thread;
  pthread_create( & thread, 0, & thread_handler, (void * ) num);
  int * seq = (int * ) malloc(100 * sizeof(int));
  pthread_join(thread, (void ** ) & seq);
  for (int i = 0; seq[i] != -1; i++)
    printf("%d ", *(seq + i));
  printf("\n");
}
