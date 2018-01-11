#include "smallsquare.h"

#define p1 'x'
#define p2 'o'
#define tie '-'

typedef struct{
  struct smallsquare _STTT[9];
  struct smallsquare _BTTT;
  int _isOver;
  char _winner;
  int _turn;
} bigsquare;


