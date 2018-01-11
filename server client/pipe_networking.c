#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client

  Performs the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client, char * wkp) {
  int fd;
  char buffer[HANDSHAKE_BUFFER_SIZE];
  
  mkfifo(wkp, 0600);
  fd = open(wkp, O_RDONLY);
  read(fd , buffer, sizeof(buffer));
  remove(wkp);

  *to_client = open(buffer, O_WRONLY);
  printf("buffer: %s\n", buffer);
  write(*to_client, wkp, sizeof(wkp));
  printf("to_client: %d\n", *to_client);

  //client read
  read(fd , buffer, sizeof(buffer));
  printf("Received from client: %s\n", buffer);
  return fd;
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server, char * wkp) {
  int fd;
  char buffer[HANDSHAKE_BUFFER_SIZE];
  
  *to_server = open(wkp, O_WRONLY);
  printf("buffer: %s\n", wkp);

  mkfifo(PP, 0600);
  write(*to_server , PP, sizeof(PP));
  printf("to_server: %d\n", *to_server);

  fd = open(PP,O_RDONLY);//stuff
  read(fd , buffer, sizeof(buffer));
  remove(PP);

  //send ACK to server
  write(*to_server, ACK, sizeof(buffer));
  return fd;//PP's fd
}
