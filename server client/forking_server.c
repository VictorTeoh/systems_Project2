#include "networking.h"
#include "pipe_networking.h"
//shared memory for game hosting and then when done pipe between subservers
//some bug with blocking
void process(int * to_p, int * from_p, char * str, char * state, int client_socket);
void subserver(int from_client, int * from_p);
void host(int * to_client, int * from_client, char * buffer, char * state );
void nothost(int * to_server, int * from_server, char * buffer, char * state, int client_socket );
void game1 (char *s, char *state);
int main() {

  int listen_socket;
  int f;
  int * place;
  int i;
  i = -1;
  place = &i;
  listen_socket = server_setup();

  while (1) {

    int client_socket = server_connect(listen_socket);
    f = fork();
    if (f == 0){
      subserver(client_socket, place);
    }
    else
      close(client_socket);
  }
}

void subserver(int client_socket, int * from_p) {
  char buffer[BUFFER_SIZE];
  char state[100];
  char handle[32];
  int * to_p;
  fd_set read_fds;
  //work in select so then the subserver knows what to do when two people input stuff and set up the client server thing so it relays information back to the other client
  /* maybe later
  read(client_socket, buffer, sizeof(buffer));
  strcat(handle, buffer);
  printf("%s\n", handle);
  write(client_socket, "name saved for this session", sizeof("name saved for this session")); 
  */
  while (strcmp(state, "0") != 0) {
    
    FD_ZERO(&read_fds);
    FD_SET(*from_p, &read_fds); //add reading pipe to fd set
    FD_SET(client_socket, &read_fds); //add socket to fd set

    if(client_socket > *from_p){
      select(client_socket + 1, &read_fds, NULL, NULL, NULL);
    }
    if(*from_p > client_socket){
      select(*from_p + 1, &read_fds, NULL, NULL, NULL);
    }
    
    if (FD_ISSET(client_socket, &read_fds)) {
       read(client_socket, buffer, sizeof(buffer));
       printf("[subserver %d] received: [%s]\n", getpid(), buffer);
       process(to_p, from_p, buffer, state, client_socket);
       write(client_socket, buffer, sizeof(buffer));
     }
    if (FD_ISSET(*from_p, &read_fds)) {//this is for host only?
       read(*from_p, buffer, sizeof(buffer));
       printf("[subserver %d] received: [%s] from another subserver\n", getpid(), buffer);
       printf("[subserver %d] state: %s \n", getpid(), state);
       strcat(state, "opponent");
       process(to_p, from_p, buffer, state, client_socket);//obviously change
       state[strlen(state) - 8] = '\0';
       write(*to_p, buffer, sizeof(buffer));
     }
  }//end read loop
  write(client_socket, "Goodbye", sizeof("Goodbye"));
  close(client_socket);
  write(*from_p, "User has disconnected", sizeof("User has disconnected"));
  close(*from_p);
  exit(0);
}

//change 
void process(int * to_p, int * from_p, char * str, char * state, int client_socket) {
  
  if(strcmp(str, "quit") == 0){
    strcpy(str,"Goodbye");
    strcpy(state, "0");
  }
  else if(strcmp(str, "exit") == 0){
    strcpy(str, "Back to menu");
    strcpy(state, "");
  }
  else if(strcmp(state, "in game") == 0){
    nothost(to_p, from_p, str, state, client_socket);
  }
  else if(strncmp(state, "hosting ", 8) == 0){
    host(to_p, from_p, str, state);
    
  }
  else if(strncmp(state, "g1", 2) == 0){
    game1(str, state);
  }
  else if(strcmp(str, "test") == 0){
    strcpy(str, state);
  }
  else if(strcmp(str, "set") == 0){
    strcpy(state, str);
  }
  else if(strcmp(str, "thing") == 0){
    strcat(state, "opponent");
    state[strlen(state) - 8] = '\0';
  }
  else if(strcmp(str, "host g1") == 0){
    strcpy(str, "hosting, type anything to procede");
    strcpy(state, "hosting g1");
  }
  else if(strncmp(str, "join ", 5) == 0){
    nothost(to_p, from_p, str, state, client_socket);
  }
  else{
    strcpy(str, "Invalid phrase try again");
  }
}

void host(int * to_client, int * from_client, char * buffer, char * state ){
    //shared memory and host list stuff goes here use state to see what you have to do
    
  char wkp[25];
  sprintf(wkp, "%d", getpid()); 
  *from_client = server_handshake(to_client , wkp); //note blocks here
  strcpy(buffer, "Game established");
  strcpy(state, state + 8);
  
}

void nothost(int * to_server, int * from_server, char * buffer, char * state, int client_socket ){
  if(strcmp(state, "in game") != 0){
  //check the buffer against the host

  //chance for bug if two people try to join at the same time(probably do
  //something with how much you down the sempaphore for reading in this specific
  // case
    buffer += 5;
    *from_server = client_handshake( to_server, buffer);
    strcpy(state, "in game");
    buffer -= 5;
    strcpy(buffer, "Sucessfuly joined game");
  }
  else{
    write(*to_server, buffer, sizeof(buffer));
    read(*from_server, buffer, sizeof(buffer));
  }
  
}


void game1(char * s, char * state){
  if(strcmp(state, "g1opponent") == 0){
    strcpy(s, "not yo turn");
  }
  else{
    strcpy(s, "success");
  }
  // stuff each game needs
  // need to find a way for this to all be visible to the original server 
  // DIFFERENT files  etc. 
} 
