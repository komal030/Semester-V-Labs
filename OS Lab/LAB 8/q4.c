#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<pthread.h>

typedef struct num {
  int arr[100];
  int n;
}
NUM;
void* thread_odd(void * param) {
  NUM * num = (NUM * ) param;
  int * sum = (int * ) malloc(sizeof(int));
  * sum = 0;
  for (int i = 0; i < num -> n; i++) {
    if (num -> arr[i] % 2 == 1)
      *sum = * sum + num -> arr[i];
  }
  return (void * ) sum;
}
void* thread_even(void * param) {
  NUM * num = (NUM * ) param;
  int * sum = (int * ) malloc(sizeof(int));
  * sum = 0;
  for (int i = 0; i < num -> n; i++) {
    if (num -> arr[i] % 2 == 0)
      *sum = * sum + num -> arr[i];
  }
  return (void * ) sum;
}
int main() {
  NUM * num = (NUM * ) malloc(sizeof(NUM));
  printf("Enter number of elements: ");
  scanf("%d", & num -> n);
  printf("Enter array elements:\n");
  for (int i = 0; i < num -> n; i++)
    scanf("%d", & num -> arr[i]);

  pthread_t thread1;
  pthread_t thread2;
  pthread_create( & thread1, 0, & thread_odd, (void * ) num -> arr);
  pthread_create( & thread2, 0, & thread_even, (void * ) num -> arr);
  int * sumodd = (int * ) malloc(sizeof(int));
  int * sumeven = (int * ) malloc(sizeof(int));
  pthread_join(thread1, (void ** ) &sumodd);
  pthread_join(thread2, (void ** ) &sumeven);
  printf("Sum of odd numbers: %d\n", * sumodd);
  printf("Sum of even numbers: %d\n", * sumeven);
}
