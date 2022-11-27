#ifndef _KNIGHT_H_
#define _KNIGHT_H_
#include "pieces.h"

class Knight: public Pieces {
 public:
  //ctor
  Knight(int owner, bool gotCaptured);

  //dtor
  ~Knight();

  // checks if a move is valid for the King piece
  bool validMove(Position start, Position end) const override;

};
#endif
