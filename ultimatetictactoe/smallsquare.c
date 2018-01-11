#include "smallsquare.h"

smallsquare Smallsquare(){
  smallsquare ss;
  for(int i = 0; i < 9; i++)
    ss._sttt[i] = ' ';
  ss._gameover = false;
  ss._winner = '-';
  return ss;
}

char * get_board(smallsquare * ss){
  return ss->_sttt;
}
    
char get_index(smallsquare * ss, int val){
  return ss->_sttt[val];
}

char get_winner(smallsquare * ss){
  return ss->_winner = ss->_sttt[0];
}

void populate(smallsquare * ss){
  for(int i = 0; i < 9; i++)
    if(!(ss->_sttt[i] == 'x' || ss->_sttt[i] == 'o' || ss->_sttt[i] == '-'))
      ss->_sttt[i] = (char)(i+'1');
}
void unpopulate(smallsquare * ss){
  for(int i = 0; i < 9; i++)
    if(!(ss->_sttt[i] == 'x' || ss->_sttt[i] == 'o' || ss->_sttt[i] == '-'))
      ss->_sttt[i] = ' ';
}
    
int is_over(smallsquare * ss){
  populate(ss);
  if((ss->_sttt[0] == ss->_sttt[1] && ss->_sttt[1] == ss->_sttt[2]) ||
     (ss->_sttt[0] == ss->_sttt[3] && ss->_sttt[3] == ss->_sttt[6]) ||
     (ss->_sttt[0] == ss->_sttt[4] && ss->_sttt[4] == ss->_sttt[8]))
    return set_winner(ss, ss->_sttt[0]);
  if((ss->_sttt[3] == ss->_sttt[4] && ss->_sttt[4] == ss->_sttt[5]) ||
     (ss->_sttt[1] == ss->_sttt[4] && ss->_sttt[4] == ss->_sttt[7]) ||
     (ss->_sttt[2] == ss->_sttt[4] && ss->_sttt[4] == ss->_sttt[6]))
    return set_winner(ss, ss->_sttt[4]);
  if((ss->_sttt[6] == ss->_sttt[7] && ss->_sttt[7] == ss->_sttt[8]) ||
     (ss->_sttt[2] == ss->_sttt[5] && ss->_sttt[5] == ss->_sttt[8]))
    return set_winner(ss, ss->_sttt[8]);
	
  unpopulate(ss);
  int i;
  for( i=0; i<9; i++ )
    if( ss->_sttt[i] == ' ')
      return false;
  set_winner(ss, '-');
  return ss->_gameover = true;
}

int set_winner(smallsquare * ss, char player){
  if(ss->_gameover)
    ss->_winner = player;
  for (int i = 0; i < 9; i++)
    ss->_sttt[i] = player;
  return ss->_gameover = true;
}

void set_square(smallsquare * ss, int index, char player){
  ss->_sttt[index] = player;
}

void print_board(smallsquare * ss){
  populate(ss);
  char * s1 = "             |             |            \n";
  char * s2 = " ------------+-------------+------------\n";
  printf("%s%s",s1,s1);
  printf("      %c      |      %c      |      %c      \n", ss->_sttt[0],ss->_sttt[1],ss->_sttt[2]);
  printf("%s%s%s%s%s",s1,s1,s2,s1,s1);
  printf("      %c      |      %c      |      %c      \n",ss->_sttt[3],ss->_sttt[4],ss->_sttt[5]);
  printf("%s%s%s%s%s",s1,s1,s2,s1,s1);
  printf("      %c      |      %c      |      %c      \n",ss->_sttt[6],ss->_sttt[7],ss->_sttt[8]);
  printf("%s%s",s1,s1);
  unpopulate(ss);
}
