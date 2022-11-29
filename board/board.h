#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include "pieces.h"
#include "subject.h"
//using namespace std;

class Board: public Subject{

  //2D vector of piece pointers to create a board
  //initalize to 8 "rows" of vectors with 8 "Columns" containing nullptrs 
  //vector<vector<Pieces*>> currBoard(8, vector<Pieces*>(8, nullptr));
  //std::vector<vector<Piece*>> currBoard;
  
  Position whiteKing;
  Position blackKing;
  Pieces* currBoard[8][8];


 public:

  //ctor
  Board();

  //dtor -> iterate over the 2D vector and delete each piece pointer it contains
  ~Board();

  void initBoard();

  //Get the state of each position on the board for rendering
  char getState(int rank, int file) const;

  //Get the whole board
  //&Board getCurrBoard();

  Pieces* pieceAt(Position pos);

  //alter the main board to reflect the move -> set old location to null, new position to the piece
  void makeMove(Pieces *p, Position posOld, Position posNew);
  
  Position getWhiteKing();

  Position getBlackKing();

  bool checkRow(Position from, Position to);

  bool checkCol(Position from, Position to);

  bool checkDiagonal(Position from, Position to);

  Piece* checkRowOpp(int owner, Position from, Position to);

  Piece* checkColOpp(int owner, Position from, Position to);

  Peice* checkDiagOpp(int owner, Position from, Position to);


  /*
  void Board();
  void Display();

  */
  

};

#endif
