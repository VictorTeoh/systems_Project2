#include "networking.h"
#include "pipe_networking.h"
//shared memory for game hosting and then when done pipe between subservers
void process(int * to_p, int * from_p, char * str, char * state);
void subserver(int from_client);
void host(int * to_client, int * from_client, char * buffer, char * state );
void nothost(int * to_server, int * from_server, char * buffer, char * state );
void game1 (char *s, char *state);
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
  int * to_p;
  int * from_p;
  //work in select so then the subserver knows what to do when two people input stuff and set up the client server thing so it relays information back to the other client
  while (strcmp(state, "0") != 0 && read(client_socket, buffer, sizeof(buffer))) {

    printf("[subserver %d] received: [%s]\n", getpid(), buffer);
    process(to_p, from_p, buffer, state);
    write(client_socket, buffer, sizeof(buffer));
  }//end read loop
  write(client_socket, "Goodbye", sizeof("Goodbye"));
  close(client_socket);
  exit(0);
}

//change 
void process(int * to_p, int * from_p, char * str, char * state) {
  
  if(strcmp(str, "quit") == 0){
    strcpy(str,"Goodbye");
    strcpy(state, "0");
  }
  else if(strcmp(str, "exit") == 0){
    strcpy(str, "Back to menu");
    strcpy(state, "");
    
  }
  else if(strcmp(state, "hosting") == 0){
    //host(to_p, from_p, str, state);
  }
  else if(strcmp(state, "g1") == 0){
    game1(str, state);
  }
  else if(strcmp(str, "test") == 0){
    strcpy(str, "entering test");
    strcpy(state, "g1");
  }
  else if(strcmp(str, "host g1") == 0){
    strcpy(str, "hosting");
    strcpy(state, "hosting");
  }
  else if(strncmp(str, "join ", 5) == 0){
    strcpy(str, "sdsar"); // ????
    sscanf(str, "%d", to_p);
    printf("%d\n",*to_p);
     printf("%d\n",*to_p); 
    sprintf(str, "fs %d", *to_p);
  }
  else{
    strcpy(str, "Invalid phrase try again");
  }
}

void host(int * to_client, int * from_client, char * buffer, char * state ){
  //shared memory and host list stuff goes here use state to see what you have to do

  char wkp[25];
  sprintf(wkp, "%d", getpid());
  //no while loop here 
   *from_client =  server_handshake(to_client , wkp);
  //change later
  read(*from_client, buffer, sizeof(buffer));
  write(*to_client, buffer, sizeof(buffer));
  printf("buffer: %s\n", buffer);
  
  
}

void nothost(int * to_server, int * from_server, char * buffer, char * state ){
  *from_server = client_handshake( to_server, buffer);

  

  write(*to_server, buffer, sizeof(buffer));
  read(*from_server, buffer, sizeof(buffer));
  printf("buffer: %s\n", buffer);

}


void game1(char * s, char * state){
  strcpy(s, "success");
  // stuff each game needs
  // need to find a way for this to all be visible to the original server 
  // DIFFERENT files  etc. 
} 
