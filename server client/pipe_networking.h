#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

#ifndef NETWORKING_H
#define NETWORKING_H
#define ACK "HOLA"
#endif
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1000
#endif
#define HANDSHAKE_BUFFER_SIZE 10

#define PP "PP"

int server_handshake(int *to_client, char * wkp);

int client_handshake(int *to_server, char * wkp);

