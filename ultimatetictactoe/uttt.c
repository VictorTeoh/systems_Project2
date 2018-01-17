#include "bigsquare.h"

int main(){

  while (true){
    //initializing
    bigsquare * board = Bigsquare();
    int curr_index = 0, next_index = 0;
    char player;

    //run game
    while(!is_over(board)){
      player = get_player(board); //begins at turn 1
      curr_index = next_index;
      printf("=====================================================\n");
      printf("It is Player %c's turn!\n", player);
      if( (get_turn(board) == 1) || s_is_over(get_square(board, curr_index)))
	curr_index = freebie(board);
		
      next_index = normal_turn(board, curr_index);
      set_square(get_square(board, curr_index), next_index, player);
		
      if(s_is_over(get_square(board, curr_index)) && !(get_index(get_square(board, curr_index), 0) == '-')){
	set_bboard(board, curr_index,player);
	set_winner(get_square(board, curr_index), player);
      }
      else if(s_is_over(get_square(board, curr_index)))
	set_bboard(board, curr_index,'-');
    }
    printf("=====================================================\n");
    printf("=====================================================\n");
    if(s_get_winner(get_bboard(board)) == '-')
      printf("The game is over! You tied!\n");
    else //2p game
      printf("The game is over! Player %c won the game!\n", s_get_winner(get_bboard(board)));
    print_board(board);

    /*
    //play again
    printf("Play again(y or n): ");
    ans = s.next();
    while(!(ans.equals("y") || ans.equals("n"))){
    printf"Please enter a valid answer!");
    printf("Play again(y or n): ");
    ans = s.next();
    }
    if(ans.equals("n"))
    break;
    */
  }  
}
