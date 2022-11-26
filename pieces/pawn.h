#ifndef _PAWN_H_
#define _PAWN_H_
#include "pieces.h"

class Pawn: public Pieces {
  bool firstMove; // stores whether it is the first move for the pawn
  bool capture; // stores whether the pawn wants to capture another piece
 public:
  //ctor
  Pawn(int owner, int id, bool firstMove, bool capture);

  //dtor
  ~Pawn();

  // checks if a move is valid for the King piece
  bool validMove(Position start, Position end, const Board& board) const override;

};
#endif
