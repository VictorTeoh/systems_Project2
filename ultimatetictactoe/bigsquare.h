#include "smallsquare.h"

#define p1 'x'
#define p2 'o'
#define tie '-'

typedef struct{
  smallsquare * _STTT[9];
  smallsquare * _BTTT;
  int _isOver;
  char _winner;
  int _turn;
} bigsquare;

bigsquare * Bigsquare();
smallsquare ** get_sboard(bigsquare * bs);
int get_turn(bigsquare * bs);
char get_player(bigsquare * bs);
smallsquare * get_bboard(bigsquare * bs);
int is_over(bigsquare * bs);
char get_winner(bigsquare * bs);
smallsquare * get_square(bigsquare * bs, int index);
void set_bboard(bigsquare * bs, int index, char win);
int normal_turn(bigsquare * bs, int index);
int freebie(bigsquare * bs);
int pick_square(smallsquare * ttt);
int find_val(int * arr, int val);
void print_board(bigsquare * bs);
