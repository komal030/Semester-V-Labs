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
  address.sin_addr.s_addr = inet_addr("172.16.57.84");
  address.sin_port = htons(PORTNO);

  int result = connect(socket_id, (struct sockaddr * ) & address, sizeof(address));

  if (result == -1) {
    printf("\nClient Error");
    exit(1);
  }
  int n, m;
  int k = 0;
  printf("Enter number of rows: ");
  scanf("%d", & n);
  printf("Enter number of columns: ");
  scanf("%d", & m);
  int arr[n * m];
  for (int i = 0; i < n; i++) {
    printf("Enter elements of row %d:\n", (i + 1));
    for (int j = 0; j < m; j++) {
      scanf("%d", & arr[k++]);
    }
  }
  write(socket_id, & n, sizeof(n));
  write(socket_id, & m, sizeof(m));
  write(socket_id, arr, sizeof(int) * n * m);
  printf("Input to server sent\n");
  close(socket_id);
  return 0;
}
