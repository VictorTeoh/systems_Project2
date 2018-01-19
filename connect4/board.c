#include "board.h"

connect4 * setup(){
  connect4 * cf = malloc(sizeof(connect4));
  for(int i = 0; i < 6; i++)
    for(int j = 0; j < 7; j++)
      (*cf)._board[i][j] = blank;
  (*cf)._turn = 0;
  (*cf)._isover = false;
  (*cf)._winner = blank;
  return cf;
}

char *** get_board(connect4 * cf){
  return (*cf)._board;
}

char get_player(connect4 * cf){
  (*cf)._turn++; //increments turn before returning current player
  if((*cf)._turn % 2 == 1) //since turn is incremented, p1 will be 1
    return p1;
  else //and p2 would be 0 instead of the opposite
    return p2;
}

char set(int col, int row, char player){
  return (*cf)._board[col][row] = player;
}

char turn(connect4 * cf, int col, char player){
  printf("Current Board\n");
  print_board(cf);
  char buffer[8];
  char row;
  while ((row = strchr((*cf)._board[col], blank)) == -1){
    printf("Please enter an unfilled column!\nPick a column: ");
    while( fgets(buffer, 8, stdin) ){
      if(strlen(buffer) == 2 && ((buffer[0] - '0') <= 7 && (buffer[0] - '0') > 0))
	break;
      printf("Please enter an unfilled column!\nPick a column: ");
    }
    col = buffer[0] - '0';
  }
  return set(col, row, player);
}

void print_board(connect4 * cf){
  char ans[512] = {"|"};
  char open[16] = {" "};
  for(int i = 0; i < 6; i++){
    for(int j = 0; j < 7; j++)
      sprintf(ans, "%s%s|", ans, (*cf)._board[i][j]);
    sprintf(ans, "%s\n_______________\n", ans);
    if(strchr((*cf)._board[i], blank) == -1)
      sprintf(open, "%s%d ", ans, i);
    else
      sprintf(open, "%s  ", ans);
  }
  printf("%s\n",ans);
}
