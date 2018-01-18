#include "connect4.h"

#define p1 'o'
#define p2 'x'
#define blank ' '

typedef struct{
  char * _board[6][7];
  int _isover;
  char _winner;
  int _turn;
} connect4;
