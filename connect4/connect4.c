#include "board.h"

int main(){
  while (true){
    //initializing
    connect4 * board = setup();
    char player;
    char buffer[8];

    //run game
    while(!is_over(board)){
      player = get_player(board); //begins at turn 1
      printf("=====================================================\n");
      printf("It is Player %c's turn!\n", player);
      printf("Current Board\n");
      print_board(board);
      printf("Please pick a column: ");
      while( fgets(buffer, 8, stdin) ){
	if(strlen(buffer) == 2 && ((buffer[0] - '0') <= 7 && (buffer[0] - '0') > 0))
	  break;
	printf("Please enter an unfilled column!\nPick a column: ");
      }
      turn(board, buffer[0] - '0' - 1, player);
    }
    printf("=====================================================\n");
    printf("=====================================================\n");
    if(get_player(board) == ' ')
      printf("The game is over! You tied!\n");
    else //2p game
      printf("The game is over! Player %c won the game!\n", get_player(board));
    print_board(board);
    //play again
    printf("Play again(y or n): ");
    fgets(buffer, 8, stdin);
    while(!(strlen(buffer) == 2 && (!strncmp(buffer,"y",1) || !strncmp(buffer,"n",1)))){
      printf("Please enter a valid answer!");
      printf("Play again(y or n): ");
      fgets(buffer, 8, stdin);
    }
    if(!strncmp(buffer,"n",1))
      break;
  }  

}
