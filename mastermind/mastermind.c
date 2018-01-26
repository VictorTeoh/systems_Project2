#include "mastermind.h"

int main(){
  int red_peg, white_peg, turn;
  char mastercode[GUESSES], codebreaker[GUESSES];
  char player;
  while(1){
    for(turn=0; turn<MAX_GUESS; turn++){
      get_player(turn, &player);
      if(player == p1 && turn == 0)
	make_code(mastercode);
      else if(player == p1)
	change_code(mastercode, codebreaker);
      make_code(codebreaker);
      check(mastercode, codebreaker, &red_peg, &white_peg);
      print(codebreaker, red_peg, white_peg);
      if(red_peg == GUESSES){
	printf("The Code Breaker won!\n");
	break;
      }
    }
    if(turn == MAX_GUESS){
      printf("\nThe Code Maker won!\nMaster Code: ");
      for(int i=0; i<GUESSES; i++) 
	printf("%s ", add_color(find_col(mastercode[i])));
    }
    exit(1);
  }
}

//--------------------------------------------------------------
void get_player(int turn, char * player){
  if(turn % 5 == 0)
    *player = p1;
  else
    *player = p2;
}

void make_code(char code[GUESSES]){
  int i;
  for(i=0; i<GUESSES; i++){
    printf("Pin #%d color:\n", i+1); 
    guess(&code[i]);
  }
}

void change_code(char mastercode[GUESSES], char codebreaker[GUESSES]){
  int i;
  char buffer[STRING] = {0};
  printf("Current Code: ");
  for(i=0; i<GUESSES; i++)
    printf("%s ", add_color(find_col(mastercode[i]))); 
  printf("\nLast Guess: ");
  for(i=0; i<GUESSES; i++)
    printf("%s ", add_color(find_col(codebreaker[i])));
  while( strlen(buffer) != 2 || !(buffer[0]-'0' > 0 && buffer[0]-'0' < 5) ){
    printf("\nPick one of the four pins to change: ");
    fgets(buffer, STRING, stdin);
  }
  i = buffer[0]-'0';
  printf("i: %d\n", i);
  guess(&mastercode[i-1]);
}
      
void guess(char * pin){
  char buffer[STRING] = {0};
  printf("Red(r) | Green(g) | Yellow(y) | Blue(b) | Purple(p) | White(w)\n");
  while( strlen(buffer) != 2 || (find_col(buffer[0]) == 0) ){
    printf("Pick a color: ");
    fgets(buffer, STRING, stdin);
  }
  *pin = buffer[0];
}

int find_col(char guess){
  if(guess == red)       return 1;
  if(guess == green)     return 2;
  if(guess == yellow)    return 3;
  if(guess == blue)      return 4;
  if(guess == purple)    return 5;
  if(guess == white)     return 6;
  return 0;
}

char * add_color(int guess){
  char * tmp = (char *)malloc(20*sizeof(char));
  if(guess == 1)     sprintf(tmp, RED "red" RST);
  if(guess == 2)     sprintf(tmp, GRN "green" RST);
  if(guess == 3)     sprintf(tmp, YEL "yellow" RST);
  if(guess == 4)     sprintf(tmp, BLU "blue" RST);
  if(guess == 5)     sprintf(tmp, PUR "purple" RST);
  if(guess == 6)     sprintf(tmp, WHT "white" RST);
  return tmp;
}

void check(char mastercode[GUESSES], char codebreaker[GUESSES], int * red_peg, int * white_peg){
  int i, j;
  int master[GUESSES] = {1,1,1,1};
  int breaker[GUESSES] = {1,1,1,1};
  *red_peg = *white_peg = 0;

  for(i=0; i<GUESSES; i++)
    if(strncmp(codebreaker+i, mastercode+i, 1) == 0){
      ++*red_peg;
      master[i] = breaker[i] = 0;
    }            
  
  for(i=0; i<GUESSES; i++)
    for(j=0; j<GUESSES; j++)       
      if(strncmp(mastercode+i,codebreaker+j, 1) == 0 && breaker[i] && master[j] && i != j){
	++*white_peg;
	master[j] = breaker[i] = 0;
      }
}

void print(char codebreaker[GUESSES], int red_peg, int white_peg){   
  int i;
  printf("Your Guess: ");   
  for(i=0; i<GUESSES; i++) 
    printf("%s ", add_color(find_col(codebreaker[i])));
  printf("\n\nYou have %d correctly colored and positioned pins!", red_peg);
  printf("\nYou have %d correctly colored but misplaced pins!\n", white_peg);       
  printf("==========================================================\n");
}
