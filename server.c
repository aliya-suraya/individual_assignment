#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define SIZE 1024
#define PORT 6969

void write_file(int socketfd, struct sockaddr_in server){
  FILE *fp;
  char *filename = "server.txt";
  int x;
  char buffer[SIZE];
  socklen_t addr_size;

  // create file
  fp = fopen(filename, "w");

  // receive data into file
  while(1){

    addr_size = sizeof(server);
    x = recvfrom(socketfd, buffer, SIZE, 0, (struct sockaddr*)&server, &addr_size);

    if (strcmp(buffer, "END") == 0){
      break; return;
    }

    printf("[SERVER] Receiving Data: %s", buffer);
    fprintf(fp, "%s", buffer);
    bzero(buffer, SIZE);
  }

  fclose(fp);
  return;
}

int main(){

  // define varibles
  int socketfd;
  struct sockaddr_in server, client;
  char buffer[SIZE];
  int e;

  // create UDP socket
  socketfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (socketfd < 0){
    printf("[CLIENT] Socket error\n");
    exit(1);
  }
  server.sin_family = AF_INET;
  server.sin_port = PORT;
  server.sin_addr.s_addr = inet_addr(ip);

  if (bind(socketfd, (struct sockaddr*)&server, sizeof(server)));
 {
    printf("[SERVER] Bind error\	n");
    exit(1);
  }

  printf("[SERVER] UDP File Server Started\n");
  write_file(socketfd, client);

  printf("[SERVER] Data transfer is Success\n");
  printf("[SERVER] Closing....\n");

  close(socketfd);

  return 0;
}
