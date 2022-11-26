#ifndef _BISHOP_H_
#define _BISHOP_H_
#include "pieces.h"

class Bishop: public Pieces {
 public:
  //ctor
  Bishop(Player owner, int id);

  //dtor
  ~Bishop();

  // checks if a move is valid for the King piece
  bool validMove(Position start, Position end, const Board& board) const override;

};
#endif
