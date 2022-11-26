#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
//#include "pieces"
//#include "subject.h"

class Board{
  //int row = 10, cols = 10;

  //2D vector of piece pointers to create a board
  std::vector<vector<Piece*>> boards(8, vector<Piece*>(8, nullptr)); //initalize to 8 "rows" of vectors with 8 "Columns"
 
  Board *currBoard; //NOT TOO SURE ABOUT THIS - REFER TO ASCII ART EXAMPLE 

 public:

  explicit Board();
  void Board(); //what was the purpose of this?
  &Board getCurrBoard();
  void initBoard();
  bool checkRow(*Piece from, *Piece to);
  bool checkCol(*Piece from, *Piece to);
  bool checkDiagonal(*Piece from, *Piece to);
  void display();
  
  /*
  void attach(Observer *o);
  void detach(Observer *o);
  void notifyObservers();
  */
  ~Board();

  &Piece getState(int row, int col) const; //DO WE WANT IT TO RETURN THE PEICE AT THE COORD? OR THE WHOLE BOARD

};

#endif
