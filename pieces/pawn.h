#ifndef _PAWN_H_
#define _PAWN_H_
#include "pieces.h"

class Pawn: public Pieces {
 public:
  //ctor
  Pawn(Player owner, int id);

  //dtor
  ~Pawn();

  // checks if a move is valid for the King piece
  bool validMove(Position start, Position end, const Board& board) const override;

};
#endif
