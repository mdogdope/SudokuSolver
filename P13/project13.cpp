/***********************************************************************
* Program:
*    Project Final, Sudoku Solver
*    Brother Schwieder, CS124
* Author:
*    Mike Heston
* Summary:
*
* 	 Solves sudoku puzzles.
*   Terms:
*   A board is a 3x3 grid of boxes.
*   A box is a 3x3 of squares.
*   A square can only have one value, but multiple possables.
*
*    Estimated:  4.0hrs
*    Actual:     4.0hrs
*
*    Hardest Part: deciding what to do when a fork happens.
************************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <utility>
#include <array>

using namespace std;

bool debug = true;

class Board {

};

array<array<int, 9>, 9> readFile();

void checkRow(Board&, pair<int,int>);
void checkCol(Board&, pair<int,int>);
void checkBoc(Board&, pair<int,int>);

void checkPos(Board&, pair<int,int>);

void findSingles(Board&);

/**********************************************************************
 * This is the entry point for the program.
 ***********************************************************************/
int main(){
   
   
   //First find all possables for each square using
   //basic searches.(checkRow, checkCol, checkSquare)
   
   
   
   
	return 0;
}

/**********************************************************************
 * Basic search:
 * Checks row
 ***********************************************************************/
void checkRow(Board &board, pair<int,int> loc){
   
}

/**********************************************************************
 * Basic search:
 * checks col
 ***********************************************************************/
void checkCol(Board &board, pair<int,int> loc){
   
}

/**********************************************************************
 * Basic search:
 * checks box
 ***********************************************************************/
void checkBox(Board &board, pair<int,int> loc){
   
}

/**********************************************************************
 * Advanced search:
 * Checks what other squares need to be based on what is in their box
 ***********************************************************************/
void checkPos(Board &board, pair<int,int> loc){
   
}

/**********************************************************************
 * Find squares with only one possability and set it.
 * Update possable vals in effected row, col, and box.
 * Optional: pass location and value
 ***********************************************************************/
void setSquare(Board &board, pair<int,int> loc = {0,0}, int val = 0){
   
}

/**********************************************************************
 * Validates the whole board.
 ***********************************************************************/
void validateBoard(Board board){
   
}

/**********************************************************************
 * Undoes changes until board is valid again.
 * Supposed to be called in conjuction with validateBoard.
 ***********************************************************************/
void undo(Board &board){
   
}

/**********************************************************************
 * reads the file into the board.
 ***********************************************************************/
array<array<int, 9>, 9> readFile(){
   string fname = "prjFinal100.txt";
   array<array<int, 9>, 9> board;
   if(!debug){
      cout << "Enter file name of board: ";
      getline(cin, fname);
   }
   
   ifstream fin(fname);
   
   for(int i = 0; i < 9; i++){
      for(int ii = 0; ii < 9; ii++){
         fin >> board[i][ii];
      }
   }
   fin.close();
   
   return board;
}


















