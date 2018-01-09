#include "networking.h"

void process(char *s, char *g);
void subserver(int from_client);
void  game1 (char *s);
int main() {

  int listen_socket;
  int f;
  listen_socket = server_setup();

  while (1) {

    int client_socket = server_connect(listen_socket);
    f = fork();
    if (f == 0)
      subserver(client_socket);
    else
      close(client_socket);
  }
}

void subserver(int client_socket) {
  char buffer[BUFFER_SIZE];
  char state[100];

  while (read(client_socket, buffer, sizeof(buffer))) {

    printf("[subserver %d] received: [%s]\n", getpid(), buffer);
    process(buffer, state);
    write(client_socket, buffer, sizeof(buffer));
  }//end read loop
  close(client_socket);
  exit(0);
}

//change 
void process(char * s, char * g) {
  int GAME_NO = 1;
  char * games[GAME_NO];
  games[0] = "test";
  if(strcmp(g, "g1") == 0){
    game1(s);
  }
  else if(strcmp(s, games[0]) == 0){
    strcpy(s, "entering test");
    strcpy(g, "g1");
  }
  else{
    strcpy(s, "Invalid phrase try again");
  }
  /*
  while (*s) {
    if (*s >= 'a' && *s <= 'z')
      *s = ((*s - 'a') + 13) % 26 + 'a';
    else  if (*s >= 'A' && *s <= 'Z')
      *s = ((*s - 'a') + 13) % 26 + 'a';
    s++;
  }
  */
}

void game1(char * s){
  strcpy(s, "success");
  // stuff each game needs
  // need to find a way for this to all be visible to the original server 
  // DIFFERENT files  etc. 
} 
