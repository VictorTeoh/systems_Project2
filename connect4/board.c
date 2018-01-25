#include "board.h"

connect4 * setup(){
  connect4 * cf = malloc(sizeof(connect4));
  for(int i = 0; i < 7; i++)
    for(int j = 0; j < 6; j++)
      (*cf)._board[i][j] = blank;
  (*cf)._turn = 0;
  (*cf)._isover = false;
  (*cf)._winner = blank;
  return cf;
}

int is_over(connect4 * cf){
  return (*cf)._isover;
}

char get_winner(connect4 * cf){
  return (*cf)._winner;
}

char get_player(connect4 * cf){
  (*cf)._turn++; //increments turn before returning current player
  if((*cf)._turn % 2 == 1) //since turn is incremented, p1 will be 1
    return p1;
  else //and p2 would be 0 instead of the opposite
    return p2;
}

char set(connect4 * cf, int col, int row, char player){
  return (*cf)._board[col][row] = player;
}

char turn(connect4 * cf, int col, char player){
  char buffer[8];
  char * row;
  while ((row = strchr((*cf)._board[col], blank)) == NULL){
    printf("Please enter an unfilled column!\nPick a column: ");
    while( fgets(buffer, 8, stdin) ){
      if(strlen(buffer) == 2 && ((buffer[0] - '0') <= 7 && (buffer[0] - '0') > 0))
	break;
      printf("Please enter an unfilled column!\nPick a column: ");
    }
    col = buffer[0] - '0';
  }
  if(check_win(cf, col, row-(*cf)._board[col], player))
    (*cf)._isover = true;
  return set(cf, col, row-(*cf)._board[col], player);
}

int check_win(connect4 * cf, int col, int row, char player){
  int i;
  for(i = 0; i < 4; i++){
    if((*cf)._board[col-i][row] == (*cf)._board[col+1-i][row] == (*cf)._board[col+2-i][row] == (*cf)._board[col+3-i][row]) //check horizontally
      return (*cf)._winner = player;
    if((*cf)._board[col][row-i] == (*cf)._board[col][row+1-i] == (*cf)._board[col][row+2-i] == (*cf)._board[col][row+3-i]) //check vertically
      return (*cf)._winner = player; 
    if((*cf)._board[col-i][row-i] == (*cf)._board[col+1-i][row+1-i] == (*cf)._board[col+2-i][row+2-i] == (*cf)._board[col+3-i][row+3-i]) //check a diagonal
      return (*cf)._winner = player;
    if((*cf)._board[col-i][row-i] == (*cf)._board[col-1-i][row-1-i] == (*cf)._board[col-2-i][row-2-i] == (*cf)._board[col-3-i][row-3-i]) //check other diagonal
      return (*cf)._winner = player;
  }
  for( i=0; i<7; i++ )
    if( strchr((*cf)._board[i], blank) )
      return false;
  return (*cf)._isover = true;
}

void print_board(connect4 * cf){
  char ans[512] = {"|"};
  char open[32] = {""};
  for(int i = 6; i > 0; i--){
    for(int j = 7; j > 0; j--)
      sprintf(ans, "%s %c |", ans, (*cf)._board[j][i]);
    sprintf(ans, "%s\n-----------------------------\n|", ans);
  }
  for(int i = 0; i < 7; i++){
    if(strchr((*cf)._board[i], blank))
      sprintf(open, "%s %d |", open, i+1);
    else
    sprintf(open, "%s   |", open);
  }
  printf("%s%s\n",ans,open);
}
