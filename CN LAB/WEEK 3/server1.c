#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/wait.h>
#define PORTNO 10200

int main() {
  int socket_id = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in serveraddress;
  serveraddress.sin_family = AF_INET;
  serveraddress.sin_addr.s_addr = inet_addr("172.16.57.84");
  serveraddress.sin_port = htons(PORTNO);

  bind(socket_id, (struct sockaddr * ) & serveraddress, sizeof(serveraddress));
  listen(socket_id, 5);
  int n, m, k = 0;
  int arr[100];
  while (1) {
    struct sockaddr_in clientaddress;
    int clientlength = sizeof(clientaddress);
    int new_socket_id = accept(socket_id, (struct sockaddr * ) & clientaddress, & clientlength);
    read(new_socket_id, & n, sizeof(n));
    read(new_socket_id, & m, sizeof(m)); // Read the number of elements
    read(new_socket_id, & arr, sizeof(int) * n * m);
    printf("Matrix for given data\n");
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        printf("%d ", arr[k++]);
      }
      printf("\n");
    }
  }
  close(socket_id); // Close listening socket
  return 0; // Return from the main function
}
