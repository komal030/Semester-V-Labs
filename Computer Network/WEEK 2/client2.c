#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define PORTNO 10201

int main() {
  int socket_id = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = inet_addr("172.16.57.199"); 
  int result= connect(socket_id, (struct sockaddr * ) & address, sizeof(address));

  if (result== -1) {
    printf("\nClient Error");
    exit(1); 
  }

  int num1,num2,answer=0;
  char op;
  
  printf("Enter first number: ");
  scanf("%d",&num1);
  printf("\nEnter second number: ");
  scanf("%d",&num2);
  
  
  // Clear the input buffer before reading the operator
while (getchar() != '\n'); // This line will consume the newline character

printf("Enter operator: ");
scanf(" %c", &op);
  
  write(socket_id,&num1,sizeof(num1));
  write(socket_id,&num2,sizeof(num2));
  write(socket_id,&op,sizeof(op));
  read(socket_id,&answer,sizeof(answer));
  printf("Result of arithmetic operation %d\n",answer);
  close(socket_id);
  return 0;
}
