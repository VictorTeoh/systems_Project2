#include "connect4.h"

#define p1 'o'
#define p2 'x'
#define blank ' '

#define RED "\x1B[31m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define RESET "\x1B[0m"

typedef struct{
  char _board[7][6];
  int _isover;
  char _winner;
  int _turn;
} connect4;

connect4 * setup();
int is_over(connect4 * cf);
char get_winner(connect4 * cf);
char get_player(connect4 * cf);
char set_winner(connect4 * cf, char player);
char set(connect4 * cf, int col, int row, char player);
char turn(connect4 * cf, int col, char player);
char check_win(connect4 * cf, int col, int row, char player);
void print_board(connect4 * cf);
