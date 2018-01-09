#include "smallsquare.h"

#define p1 'x'
#define p2 'o'
#define tie '-'

struct bigsquare{
  struct smallsquare _STTT[9];
  struct smallsquare _BTTT;
  int _isOver;
  int _AI;
  char _winner;
  int _turn;
};


