#ifndef _QUEEN_H_
#define _QUEEN_H_
#include "pieces.h"

class Queen: public Pieces {
 public:
  //ctor
  Queen(int owner, bool captured, char id);

  //dtor
  ~Queen();

  // checks if a move is valid for the King piece
  bool validMove(Position start, Position end) const override;

};
#endif

