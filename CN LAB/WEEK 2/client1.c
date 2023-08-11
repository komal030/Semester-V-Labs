#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define PORTNO 10200

int main() {
  int socket_id = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = inet_addr("172.16.57.199"); // Connect to localhost
  address.sin_port = htons(PORTNO);

  int result = connect(socket_id, (struct sockaddr * ) & address, sizeof(address));

  if (result == -1) {
    printf("\nClient Error");
    exit(1); // Change exit(0) to exit(1) to indicate an error
  }

  int n, id;
  int arr[256], buff[256];
  printf("\nEnter size of array: ");
  scanf("%d", & n);
  printf("\nEnter array elements:\n");
  for (int i = 0; i < n; i++) {
    scanf("%d", & arr[i]);
  }
  write(socket_id, & n, sizeof(n)); // Send the number of elements
  write(socket_id, arr, sizeof(int) * n); // Send the array elements
  printf("Sorted array from the server process:\n");
  read(socket_id, buff, sizeof(int) * n); // Read the sorted array
  for (int i = 0; i < n; i++)
    printf("%d ", buff[i]);
  read(socket_id, & id, sizeof(id));
  printf("\nProcess id: %d\n", id);
  close(socket_id);
  return 0;
}
