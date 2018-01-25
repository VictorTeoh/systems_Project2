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

char set_winner(connect4 * cf, char player){
  return (*cf)._winner = player;
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
  int row;
  while ( !((row = strchr((*cf)._board[col], blank)-(*cf)._board[col]) < 6) ){
    printf("Please enter an unfilled column!\nPick a column: ");
    while( fgets(buffer, 8, stdin) ){
      if(strlen(buffer) == 2 && ((buffer[0] - '0') <= 7 && (buffer[0] - '0') > 0))
	break;
      printf("Please enter an unfilled column!\nPick a column: ");
    }
    col = buffer[0] - '0' - 1;
  }
  set(cf, col, row, player);
  if( set_winner(cf, check_win(cf, col, row, player)) != blank )
    (*cf)._isover = true;
  return player;
}

char check_win(connect4 * cf, int col, int row, char player){
  int i, j;
  // horizontal check 
  for (j = 0; j<6 ; j++)
    for (i = 0; i<7; i++)
      if ((*cf)._board[i][j] == (*cf)._board[i][j+1] && (*cf)._board[i][j+2] == (*cf)._board[i][j+3] && (*cf)._board[i][j] == player && (*cf)._board[i][j] == (*cf)._board[i][j+3])
	return player;
  // vertical check
  for (i = 0; i<4 ; i++)
    for (j = 0; j<6; j++)
      if ((*cf)._board[i][j] == (*cf)._board[i+1][j] && (*cf)._board[i+2][j] == (*cf)._board[i+3][j] && (*cf)._board[i][j] == player && (*cf)._board[i][j] == (*cf)._board[i+3][j])
	return player;
  // ascending diagonal check 
  for (i = 3; i<7; i++)
    for (j = 0; j<6; j++)
      if ((*cf)._board[i][j] == (*cf)._board[i-1][j+1] && (*cf)._board[i-2][j+2] == (*cf)._board[i-3][j+3] && (*cf)._board[i][j] == player && (*cf)._board[i][j] == (*cf)._board[i-3][j+3])
	return player;
  // descending diagonal check
  for (i = 3; i<7; i++)
    for (j = 3; j<6; j++)
      if ((*cf)._board[i][j] == (*cf)._board[i-1][j-1] && (*cf)._board[i-2][j-2] == (*cf)._board[i-3][j-3] && (*cf)._board[i][j] == player && (*cf)._board[i][j] == (*cf)._board[i-3][j-3])
	return player;
  return blank;
}

void print_board(connect4 * cf){
  int i, j;
  char ans[1024] = {"|"};
  char open[256] = {""};
  for(i = 5; i >= 0; i--){
    for(j = 0; j < 7; j++){
      if((*cf)._board[j][i] == p1)
	sprintf(ans, "%s %s |", ans, RED "o" RESET);
      else if((*cf)._board[j][i] == p2)
	sprintf(ans, "%s %s |", ans, YEL "o" RESET);
      else
	sprintf(ans, "%s   |", ans);
    }
    sprintf(ans, "%s\n-----------------------------\n|", ans);
  }
  for(i = 0; i < 7; i++)
    if((*cf)._board[i][5] == blank)
      sprintf(open, "%s" BLU " %d " RESET "|" , open, i+1);
    else
      sprintf(open, "%s   |", open);
  
  printf("%s%s\n",ans,open);
}
