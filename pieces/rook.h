#ifndef _ROOK_H_
#define _ROOK_H_
#include "pieces.h"

class Rook: public Pieces {
  bool moved = false; // stores whether the rook has moved in the game yet

 public:
  //ctor
  Rook(int owner, bool captured, char id);

  //dtor
  ~Rook();

  // return whether the rook has moved
  bool getMoved() const override;

  // set whether the rook has moved
  void setMoved(bool newMoved) override;

  // checks if a move is valid for the Rook piece
  bool validMove(Position start, Position end, Board* board) const override;

  // checks if a move is fully valid, this is overridden by each derived piece -> TO IMPLEMENT STILLL!!!!
  bool validMoveFinal(Position start, Position end, Board* board) const override;

};
#endif
