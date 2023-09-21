#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/wait.h>
#define PORTNO 10201

int main() {
  int socket_id = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in serveraddress;
  serveraddress.sin_family = AF_INET;
  serveraddress.sin_addr.s_addr = inet_addr("172.16.57.199"); // Bind to all available interfaces
  serveraddress.sin_port = htons(PORTNO);

  bind(socket_id, (struct sockaddr * ) & serveraddress, sizeof(serveraddress));
  listen(socket_id, 5);
  int n;
  while (1) {
    struct sockaddr_in clientaddress;
    int clientlength = sizeof(clientaddress);
    int new_socket_id = accept(socket_id, (struct sockaddr * ) & clientaddress, & clientlength);

    int parent_id = fork();

    if (parent_id == 0) 
    {
      close(socket_id);
      int num1,num2,result;
      char op;
      read(new_socket_id,&num1,sizeof(num1));
      read(new_socket_id,&num2,sizeof(num2));
      read(new_socket_id,&op,sizeof(op));
      
      printf("Number 1: %d\nNumber 2: %d\nOperator: %c\n",num1,num2,op);
      
      if(op=='+')
 
      result=num1+num2;
      
      else if(op=='-')
      
      result=num1-num2;
     
      else if(op=='*')
     
      result=num1*num2;
      
      else if(op=='/')
      result=num1/num2;
      
      write(new_socket_id,&result,sizeof(result));
      printf("Returned result to client\n");
      close(new_socket_id);
      exit(0);
    } 
    else {
      close(new_socket_id); 
    }
    }
  close(socket_id); 
  return 0; 
}
