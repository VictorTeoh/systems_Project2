#include "networking.h"
#include "pipe_networking.h"
//shared memory for game hosting and then when done pipe between subservers
void process(char *s, char *g);
void subserver(int from_client);
void  game1 (char *s);
int main() {

  int listen_socket;
  int f;
  int wkp; //the name of the pipe that you are trying to connect to
  //which is also that subserver's pid
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
  //work in select so then the subserver knows what to do when two people input stuff and set up the client server thing so it relays information back to the other client
  while (strcmp(state, "0") != 0 && read(client_socket, buffer, sizeof(buffer))) {

    printf("[subserver %d] received: [%s]\n", getpid(), buffer);
    process(buffer, state);
    write(client_socket, buffer, sizeof(buffer));
  }//end read loop
  close(client_socket);
  exit(0);
}

//change 
void process(char * s, char * g) {
  
  if(strcmp(s, "quit") == 0){
    strcpy(s,"Goodbye");
    strcpy(g, "0");
  }
  else if(strcmp(s, "exit") == 0){
    strcpy(g, ""); 
  }
  else if(strcmp(g, "hosting") == 0){
    //host();
  }
  else if(strcmp(g, "g1") == 0){
    game1(s);
  }
  else if(strcmp(s, "test") == 0){
    strcpy(s, "entering test");
    strcpy(g, "g1");
  }
  else if(strcmp(s, "host g1") == 0){
    strcpy(s, "hosting");
    strcpy(g, "hosting");
  }
  else if(strcmp(s, "join ") == 0){
    sscanf(s, "%d", &wkp);
  }
  else{
    strcpy(s, "Invalid phrase try again");
  }
}

void host(int to_client, int from_client, char * buffer ){
  //shared memory and host list stuff goes here

  /*
  int to_client;
  int from_client;
  char buffer[BUFFER_SIZE];
  */
  //no while loop here 
  from_client = server_handshake( &to_client , getpid());
  while(read(from_client, buffer, sizeof(buffer))){
    write(to_client, buffer, sizeof(buffer));
    printf("buffer: %s\n", buffer);
  }
}


void game1(char * s){
  strcpy(s, "success");
  // stuff each game needs
  // need to find a way for this to all be visible to the original server 
  // DIFFERENT files  etc. 
} 
