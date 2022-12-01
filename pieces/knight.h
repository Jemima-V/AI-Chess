#ifndef _KNIGHT_H_
#define _KNIGHT_H_
#include "pieces.h"

class Knight: public Pieces {
 public:
  //ctor
  Knight(int owner, bool captured, char id);

  //dtor
  ~Knight();

  Knight* makeCopy() const override;

  // checks if a move is valid for the Knight piece
  bool validMove(Position start, Position end, Board* board) const override;

  // checks if a move is fully valid, this is overridden by each derived piece
  bool validMoveFinal(Position start, Position end, Board* board) const override;

};
#endif
