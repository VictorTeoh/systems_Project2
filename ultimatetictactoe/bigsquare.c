#include "bigsquare.h"

bigsquare * Bigsquare(){
  bigsquare * bs = malloc(sizeof(bigsquare));
  for(int i = 0; i < 9; i++)
    (*bs)._STTT[i] = Smallsquare();
  (*bs)._BTTT = Smallsquare();
  (*bs)._isOver = false;
  (*bs)._winner = '-';
  (*bs)._turn = 0;
  return bs;
}

smallsquare ** get_sboard(bigsquare * bs){
  return (*bs)._STTT;
}

int get_turn(bigsquare * bs){
  return (*bs)._turn;
}

char get_player(bigsquare * bs){
  (*bs)._turn++; //increments turn before returning current player
  if((*bs)._turn % 2 == 1) //since turn is incremented, p1 will be 1
    return p1;
  else //and p2 would be 0 instead of the opposite
    return p2;
}
    
smallsquare * get_bboard(bigsquare * bs){
  return (*bs)._BTTT;
}
    
int is_over(bigsquare * bs){
  return s_is_over((*bs)._BTTT);
}

char get_winner(bigsquare * bs){
  return (*bs)._winner;
}

smallsquare * get_square(bigsquare * bs, int index){
  return (*bs)._STTT[index];
}
    
void set_bboard(bigsquare * bs, int index, char win){
  set_square((*bs)._BTTT, index, win);
}

int normal_turn(bigsquare * bs, int index){
  printf("Current Board\n");
  populate((*bs)._STTT[index]);
  print_board(bs);
  unpopulate((*bs)._STTT[index]);
  int ans = pick_square((*bs)._STTT[index]);
  return ans;
}

int freebie(bigsquare * bs){
  printf("Current Board\n");
  print_board(bs);
  printf("=====================================================\n");
  printf("You have a freebie\n");
  s_print_board((*bs)._BTTT);
  int temp = pick_square((*bs)._BTTT);
  return temp;
}

int pick_square(smallsquare * ttt){
  int i;
  int unused[9]; //make list of available indices
  populate(ttt);
  for(i = 0; i < 9; i++){
    char * x = get_board(ttt);
    int tmp = x[i] - '0';
    if((tmp > 0) && (tmp < 10))
      unused[tmp-1] = tmp;
  }
  char buffer[8];
  int num = 0;
  while (!find_val(unused,num)){ //asks until player picks an available square
    printf("Please enter a numbered square!\nPick a square: "); //player picks
    while( fgets(buffer, 8, stdin) ){ //hasNextInt
      if(strlen(buffer) == 2 && ((buffer[0] - '0') <= 9 && (buffer[0] - '0') > 0))
	break;
      printf("Please enter a numbered square!\nPick a square: ");
    }
    //System.out.print("Please enter a numbered square!\nPick a square: ");
    num = buffer[0] - '0';
  }
  unpopulate(ttt);
  return num - 1; //returns index of available square
}

int find_val(int * arr, int val){
  int i;
  for(i = 0; i < 9; i++){
    int x = arr[i];
    if(x == val && x != 0)
      return true;
  }
  return false;
}

void print_board(bigsquare * bs){
  char * DIVIDER1 = " ---+---+--- | ---+---+--- | ---+---+--- \n";
  char * DIVIDER2 = "-------------+-------------+-------------\n";

  char temp[81];
  int counter = 0;
  for(int i = 0; i < 3; i++) 
    for(int j = 0; j < 3; j++) 
      for(int k = 0; k < 3; k++) 
	for(int l = 0; l < 3; l++) {
	  temp[counter] = get_index(((*bs)._STTT[i*3+k]), (j*3+l));
	  counter++;
	}
	
  printf("  %c | %c | %c  |  %c | %c | %c  |  %c | %c | %c  \n", temp[0], temp[1], temp[2], temp[3], temp[4], temp[5], temp[6], temp[7], temp[8]);
  printf("%s", DIVIDER1);
  printf("  %c | %c | %c  |  %c | %c | %c  |  %c | %c | %c  \n", temp[9], temp[10], temp[11], temp[12], temp[13], temp[14], temp[15], temp[16], temp[17]);
  printf("%s", DIVIDER1);
  printf("  %c | %c | %c  |  %c | %c | %c  |  %c | %c | %c  \n", temp[18], temp[19], temp[20], temp[21], temp[22], temp[23], temp[24], temp[25], temp[26]);
  printf("%s", DIVIDER2);
  printf("  %c | %c | %c  |  %c | %c | %c  |  %c | %c | %c  \n", temp[27], temp[28], temp[29], temp[30], temp[31], temp[32], temp[33], temp[34], temp[35]);
  printf("%s", DIVIDER1);
  printf("  %c | %c | %c  |  %c | %c | %c  |  %c | %c | %c  \n", temp[36], temp[37], temp[38], temp[39], temp[40], temp[41], temp[42], temp[43], temp[44]);
  printf("%s", DIVIDER1);
  printf("  %c | %c | %c  |  %c | %c | %c  |  %c | %c | %c  \n", temp[45], temp[46], temp[47], temp[48], temp[49], temp[50], temp[51], temp[52], temp[53]);
  printf("%s", DIVIDER2);
  printf("  %c | %c | %c  |  %c | %c | %c  |  %c | %c | %c  \n", temp[54], temp[55], temp[56], temp[57], temp[58], temp[59], temp[60], temp[61], temp[62]);
  printf("%s", DIVIDER1);
  printf("  %c | %c | %c  |  %c | %c | %c  |  %c | %c | %c  \n", temp[63], temp[64], temp[65], temp[66], temp[67], temp[68], temp[69], temp[70], temp[71]);
  printf("%s", DIVIDER1);
  printf("  %c | %c | %c  |  %c | %c | %c  |  %c | %c | %c  \n", temp[72], temp[73], temp[74], temp[75], temp[76], temp[77], temp[78], temp[79], temp[80]);
}
