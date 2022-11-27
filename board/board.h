#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include "pieces.h"
#include "subject.h"

class Board: public Subject{

  //2D vector of piece pointers to create a board
  //initalize to 8 "rows" of vectors with 8 "Columns" containing nullptrs 
  //std::vector<std::vector<Piece*>> currBoard(8, std::vector<Piece*>(8, nullptr));
  //std::vector<vector<Piece*>> currBoard;

  Piece *currBoard[8][8];

 public:

  //ctor
  Board();

  //dtor -> iterate over the 2D vector and delete each piece pointer it contains
  ~Board();

  void initBoard();

  //Get the state of each position on the board for rendering
  char getState() const;

  //Get the whole board
  &Board getCurrBoard();

  //alter the main board to reflect the move -> set old location to null, new position to the piece
  void makeMove(Piece *p, Position posOld, Position posNew);
  
  /*
  void Board();
  void Display();

  */
  

};

#endif
