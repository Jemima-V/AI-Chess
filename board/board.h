#ifndef BOARD_H
#define BOARD_H
#include "pieces.h"
#include "subject.h"

#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Board: public Subject{

  //2D vector of piece pointers to create a board
  //initalize to 8 "rows" of vectors with 8 "Columns" containing nullptrs 
  //vector<vector<Pieces*>> currBoard(8, vector<Pieces*>(8, nullptr));
  vector<vector<Pieces*>> currBoard;
  //vector<vector<unique_ptr<Pieces>>> currBoard;
  
  Position whiteKing;
  Position blackKing;
  //Pieces* currBoard[8][8];

  bool isOppKnightAt(Position tempPos, int curOwner);


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

  Position checkRowOpp(int owner, Position from, Position to);

  Position checkColOpp(int owner, Position from, Position to);

  Position checkDiagOpp(int owner, Position from, int direction);

  //need to be carefull with this --> what is the difference btwn this and make move
  void place(Pieces* addPiece, Position pos);
  
  void removePiece(Position pos);

  void render();
  void renderMove(int x1, int x2, int y1, int y2);

  bool inBounds(Position pos);

  //Board copy ctor
  Board( const Board &other);

  bool checkL(Position start);
  
  vector<Position> getPiecePositions(int owner);

};

#endif
