#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define SIZE 1024
#define PORT 6969

void send_file(FILE *fp, int socketfd, struct sockaddr_in server){
  int n;
  char buffer[SIZE];

  // send data
  while(fgets(buffer, SIZE, fp) != NULL){
    printf("[CLIENT] Sending Data: %s\n", buffer);

    if (sendto(socketfd, buffer, SIZE, 0, (struct sockaddr*)&server, sizeof(server))==-1);
     {
     printf("[CLIENT] sending data to the server\n");
      exit(1);
    }
    bzero(buffer, SIZE);

  }
  
  strcpy(buffer, "END");
  sendto(socketfd, buffer, SIZE, 0, (struct sockaddr*)&server, sizeof(server));

  fclose(fp);
  return;
}

int main(){

  // define varibles
  int socketfd;
  struct sockaddr_in server; //server address
  FILE *fp;
  char *filename = "client.txt";

  // create UDP socket
  socketfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (socketfd < 0){
    printf("[CLIENT] Socket error\n");
    exit(1);
  }
  server.sin_family = AF_INET;
  server.sin_port = PORT;
  server.sin_addr.s_addr = inet_addr("192.168.56.101");

  // read text file
  fp = fopen(filename, "r");
  if (fp == NULL){
    printf("[CLIENT] Error reading File\n");
    exit(1);
  }

  // send file data to server
  send_file(fp, socketfd, server);

  printf("[CLIENT] Data transfer Successful\n");
  printf("[CLIENT] Disconnect from server.\n");

  close(socketfd);
  return 0;
}
