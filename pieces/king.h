#ifndef _KING_H_
#define _KING_H_
#include "pieces.h"

class King: public Pieces {
 public:
  //ctor
  King(Player owner, int id);

  //dtor
  ~King();

  // checks if a move is valid for the King piece
  bool validMove(Position start, Position end, const Board& board) const override;

};
#endif

