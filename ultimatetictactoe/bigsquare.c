#include "bigsquare.h"

bigsquare BigSquare(){
  bigsquare bs;
  bs->_STTT = SmallSquare[9];
  for(int i = 0; i < 9; i++)
    bs->_STTT[i] = new SmallSquare();
  bs->_BTTT = new SmallSquare();
  bs->_isOver = false;
  bs->_winner = '-';
  bs->_turn = 0;
}

public SmallSquare[] getSBoard(){
  return bs->_STTT;
}

public int getTurn(){
  return bs->_turn;
}
public char getPlayer(){
  bs->_turn++; //increments turn before returning current player
  if(bs->_turn % 2 == 1) //since turn is incremented, p1 will be 1
    return p1;
  else //and p2 would be 0 instead of the opposite
    return p2;
}
    
public SmallSquare getBBoard(){
  return bs->_BTTT;
}
    
public boolean isOver(){
  return bs->_BTTT.isOver();
}

public char getWinner(){
  return bs->_winner;
}

public SmallSquare getSquare(int index){
  return bs->_STTT[index];
}
    
public void setBBoard(int index, char win){
  bs->_BTTT.setSquare(index, win);
}

public int normalTurn(int index){
  System.out.println("Current Board");
  bs->_STTT[index].populate();
  printBoard();
  bs->_STTT[index].unpopulate();
  int ans = pickSquare(bs->_STTT[index]);
  return ans;
}

public int freebie(){
  System.out.println("Current Board");
  printBoard();
  System.out.println("=====================================================");
  System.out.println("You have a freebie");
  bs->_BTTT.printBoard();
  int temp = pickSquare(bs->_BTTT);
  return temp;
}

public int pickSquare(SmallSquare ttt){
  int[] unused = new int[9]; //make list of available indices
  ttt.populate();
  for(char x : ttt.getBoard()){
    int tmp = x - '0';
    if((tmp > 0) && (tmp < 10))
      unused[tmp-1] = tmp;
  }
  Scanner s = new Scanner(System.in);
  int num = 0;
  while (!findVal(unused,num)){ //asks until player picks and available square
    System.out.print("Please enter a numbered square!\nPick a square: "); //player picks
    while(!s.hasNextInt()){
      System.out.print("Please enter a numbered square!\nPick a square: ");
      s.next();
    }
    //System.out.print("Please enter a numbered square!\nPick a square: ");
    num = s.nextInt();

    ttt.unpopulate();
    return num - 1; //returns index of available square
  }

  public boolean findVal(int[] arr, int val){
    for(int x : arr)
      if(x == val && x != 0)
	return true;
    return false;
  }
    
  public void printBoard(){
    String DIVIDER1 = " ---+---+--- | ---+---+--- | ---+---+--- ";
    String DIVIDER2 = "-------------+-------------+-------------";

    String[] temp = new String[81];
    int counter = 0;
    for(int i = 0; i < 3; i++) 
      for(int j = 0; j < 3; j++) 
	for(int k = 0; k < 3; k++) 
	  for(int l = 0; l < 3; l++) {
	    temp[counter] = bs->_STTT[i*3 + k].addColor(bs->_STTT[i*3 + k].getIndex(j * 3 + l));
	    counter++;
	  }
	
    System.out.printf("  %s | %s | %s  |  %s | %s | %s  |  %s | %s | %s  \n", temp[0], temp[1], temp[2], temp[3], temp[4], temp[5], temp[6], temp[7], temp[8]);
    System.out.println(DIVIDER1);
    System.out.printf("  %s | %s | %s  |  %s | %s | %s  |  %s | %s | %s  \n", temp[9], temp[10], temp[11], temp[12], temp[13], temp[14], temp[15], temp[16], temp[17]);
    System.out.println(DIVIDER1);
    System.out.printf("  %s | %s | %s  |  %s | %s | %s  |  %s | %s | %s  \n", temp[18], temp[19], temp[20], temp[21], temp[22], temp[23], temp[24], temp[25], temp[26]);
    System.out.println(DIVIDER2);
    System.out.printf("  %s | %s | %s  |  %s | %s | %s  |  %s | %s | %s  \n", temp[27], temp[28], temp[29], temp[30], temp[31], temp[32], temp[33], temp[34], temp[35]);
    System.out.println(DIVIDER1);
    System.out.printf("  %s | %s | %s  |  %s | %s | %s  |  %s | %s | %s  \n", temp[36], temp[37], temp[38], temp[39], temp[40], temp[41], temp[42], temp[43], temp[44]);
    System.out.println(DIVIDER1);
    System.out.printf("  %s | %s | %s  |  %s | %s | %s  |  %s | %s | %s  \n", temp[45], temp[46], temp[47], temp[48], temp[49], temp[50], temp[51], temp[52], temp[53]);
    System.out.println(DIVIDER2);
    System.out.printf("  %s | %s | %s  |  %s | %s | %s  |  %s | %s | %s  \n", temp[54], temp[55], temp[56], temp[57], temp[58], temp[59], temp[60], temp[61], temp[62]);
    System.out.println(DIVIDER1);
    System.out.printf("  %s | %s | %s  |  %s | %s | %s  |  %s | %s | %s  \n", temp[63], temp[64], temp[65], temp[66], temp[67], temp[68], temp[69], temp[70], temp[71]);
    System.out.println(DIVIDER1);
    System.out.printf("  %s | %s | %s  |  %s | %s | %s  |  %s | %s | %s  \n", temp[72], temp[73], temp[74], temp[75], temp[76], temp[77], temp[78], temp[79], temp[80]);
  }
}
