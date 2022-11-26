#ifndef _ROOK_H_
#define _ROOK_H_
#include "pieces.h"

class Rook: public Pieces {
 public:
  //ctor
  Rook(Player owner, int id);

  //dtor
  ~Rook();

  // checks if a move is valid for the King piece
  bool validMove(Position start, Position end, const Board& board) const override;

};
#endif
