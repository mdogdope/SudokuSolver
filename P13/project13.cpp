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
*   A square can only have one value, but multiple possibles.
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
#include <cmath>

using namespace std;

bool debug = true;

class Board {
private:
   struct entry {
      struct sqr {
         pair<int, int> loc;
         array<bool, 9> poss;
         int val = 0;
      };
   vector<sqr> list;
   void add(pair<int,int> l, array<bool, 9> p, int v){
      sqr temp;
      temp.loc = l;
      temp.poss = p;
      temp.val = v;
      list.push_back(temp);
   }
   };
   
   array<array<int, 9>, 9> board; //will be filled with file.
   array<array<array<bool, 9>, 9>, 9> pboard;
   vector<entry> history;
   
   void addToEntry(int row, int col){
      pair<int, int> l = {row, col};
      history.back().add(l, pboard[row][col], board[row][col]);
   }
   
public:
   
   Board(array<array<int, 9>, 9> b){
      newMove(); //Makes first entry for history.
      for(int i = 0; i < 9; i++){
         for(int ii = 0; ii < 9; ii++){
            pboard[i][ii].fill(false);
         }
      }
      board = b;
   }
   
   void newMove(){
      if(history.empty() || !history.back().list.empty()){
         entry newE;
         history.push_back(newE);
      }
   }
   
   void add(int row, int col, int val){
      addToEntry(row, col);
      if(board[row][col] != 0){
         cout << "You can not add a possible number to a filled square\n";
         return;
      }
      
      pboard[row][col][val - 1] = true;
   }
   
   void remove(int row, int col, int val){
      addToEntry(row, col);
      if(board[row][col] != 0){
         cout << "You can not remove a possible number from a filled square\n";
         return;
      }
      pboard[row][col][val - 1] = false;
   }
   
   array<bool, 10> get(int row, int col){
      array<bool, 10> temp;
      if(board[row][col] != 0){
         temp.fill(false);
         temp[board[row][col]] = true;
         temp[0] = true;
      }else{
         temp[0] = false;
         for(int i = 1; i < 10; i++){
            temp[i] = pboard[row][col][i - 1];
         }
      }
      return temp;
   }
   
   void set(int row, int col, int val){
      addToEntry(row, col);
      if(board[row][col] != 0){
         cout << "You can set a final value for a filled square\n";
         return;
      }
      board[row][col] = val;
   }
   
   void goBack(int num = 1){
      
      while(history.back().list.empty() || !history.empty()){
         history.pop_back();
      }
      
      if(num > (int)history.size()){
         cout << "The size of history is " << history.size()
               << " and you want to go back " << num
               << " ,so I will undo all changes.\n";
         num = history.size();
      }
      
      for(int i = 0; i < num; i++){
         entry curEntry = history.back();
         history.pop_back();
         for(int ii = 0; ii < (int)curEntry.list.size(); ii++){
            board[curEntry.list[ii].loc.first][curEntry.list[ii].loc.second] = curEntry.list[ii].val;
            pboard[curEntry.list[ii].loc.first][curEntry.list[ii].loc.second] = curEntry.list[ii].poss;
         }
      }
   }
};

void checkRow(Board&, int, int);
void checkCol(Board&, int, int);
void checkBox(Board&, int, int);

void checkPos(Board&, int, int);

void findSingles(Board&);

array<array<int, 9>, 9> readFile();

void preCheck(Board&, int, int);

/**********************************************************************
 * This is the entry point for the program.
 ***********************************************************************/
int main(){
   Board myBoard(readFile());
   
//   First find all possibles for each square using
//   basic searches.(checkRow, checkCol, checkSquare)
   
   int manRow = 4;
   int manCol = 4;
   
   preCheck(myBoard, manRow, manCol);
   checkRow(myBoard, manRow, manCol);
   checkCol(myBoard, manRow, manCol);
   checkBox(myBoard, manRow, manCol);
   
   
//   Testing one square
   if(true){
      int testRow = manRow;
      int testCol = manCol;
      cout << "S: " << myBoard.get(testRow, testCol)[0] << endl;;
      for(int i = 1; i < 10; i++){
         cout << i << ": " << myBoard.get(testRow, testCol)[i] << endl;;
      }
   }
	return 0;
}

/**********************************************************************
 * Basic search:
 * Checks row
 ***********************************************************************/
void checkRow(Board &board, int row, int col){
   for(int i = 0; i < 9; i++){
      for(int ii = 1; ii < 10; ii++){
         if(board.get(row, i)[ii] && (i != col) && board.get(row, i)[0]){
            board.remove(row, col, ii);
         }
      }
   }
}

/**********************************************************************
 * Basic search:
 * checks column
 ***********************************************************************/
void checkCol(Board &board, int row, int col){
   for(int i = 0; i < 9; i++){
      for(int ii = 1; ii < 10; ii++){
         if(board.get(i, col)[ii] && (i != row) && board.get(i, col)[0]){
            board.remove(row, col, ii);
         }
      }
   }
}

/**********************************************************************
 * Basic search:
 * checks box
 ***********************************************************************/
void checkBox(Board &board, int row, int col){
   
   int br = (9 % row) * 3;
   int bc = (9 % col) * 3;
   cout << br << " | " << bc << endl;
   for(int ir = br; ir < (br + 3); ir++){
      for(int ic = bc; ic < (bc + 3); ic++){
         for(int in = 1; in < 10; in++){
            if(board.get(ir, ic)[in] && ir != row && ic != col && board.get(ir, ic)[0]){
               board.remove(row, col, in);
            }
         }
      }
   }
}

/**********************************************************************
 * Advanced search:
 * Checks what other squares need to be based on what is in their box
 ***********************************************************************/
void checkPos(Board &board, int row, int col){
   for(int in = 1; in < 10; in++){
      
      
      
      
      
   }
}

/**********************************************************************
 * Find squares with only one possibility and set it.
 * Update possible values in effected row, column, and box.
 * Optional: pass location and value
 ***********************************************************************/
void setSquare(Board &board, int row = 0, int col = 0, int val = 0){
   
}

/**********************************************************************
 * Validates the whole board.
 ***********************************************************************/
void validateBoard(Board board){
   
}

/**********************************************************************
 * Undoes changes until board is valid again.
 * Supposed to be called in conjunction with validateBoard.
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

/**********************************************************************
 * Sets up square for checks
 * Checks row
 ***********************************************************************/
void preCheck(Board &board, int row, int col){
   for(int i = 1; i < 10; i++){
      board.add(row, col, i);
   }
}















