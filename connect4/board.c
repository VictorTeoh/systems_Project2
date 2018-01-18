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
  return cf._board;
}

char get_player(connect4 * cf){
  (*cf)._turn++; //increments turn before returning current player
  if((*cf)._turn % 2 == 1) //since turn is incremented, p1 will be 1
    return p1;
  else //and p2 would be 0 instead of the opposite
    return p2;
}

char turn(connect4 * cf){


}

