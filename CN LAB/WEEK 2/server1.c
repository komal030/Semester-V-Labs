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

void sort(int arr[], int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - 1 - i; j++) {
      if (arr[j] > arr[j + 1]) {
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

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

    if (parent_id == 0) {
      close(socket_id);
      int child_id = getpid();
      int arr[256];
      read(new_socket_id, & n, sizeof(n)); // Read the number of elements
      printf("Received number of elements: %d\n", n);
      read(new_socket_id, arr, sizeof(int) * n); // Read the array elements
      printf("Unsorted array received\n");
      for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
      printf("\n");
      sort(arr, n);
      write(new_socket_id, arr, sizeof(int) * n);
      write(new_socket_id, & child_id, sizeof(child_id));
      close(new_socket_id);
      exit(0);
    } else {
      close(new_socket_id); // Close client socket in parent process
    }
  }
  close(socket_id); // Close listening socket
  return 0; // Return from the main function
}
