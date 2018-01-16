#include "headers.h"

typedef struct{
  char _sttt[9];
  char _winner;
  int _gameover;
} smallsquare;

smallsquare * Smallsquare();
char * get_board(smallsquare * ss);
char get_index(smallsquare * ss, int val);
char s_get_winner(smallsquare * ss);
void populate(smallsquare * ss);
void unpopulate(smallsquare * ss);
int s_is_over(smallsquare * ss);
int set_winner(smallsquare * ss, char player);
void set_square(smallsquare * ss, int index, char player);
void s_print_board(smallsquare * ss);
