#ifndef _PAWN_H_
#define _PAWN_H_
#include "pieces.h"

class Pawn: public Pieces {
  bool firstMove; // stores whether it is the first move for the pawn
  bool possibleCapture; // stores whether the pawn wants to capture another piece

 public:
  //ctor
  Pawn(int owner, bool captured, int id, bool firstMove, bool possibleCapture);

  //dtor
  ~Pawn();

  // return whether the pawn wants to capture another piece
  bool getPossibleCapture() const;

  // set whether the pawn wants to capture another piece
  void setPossibleCapture(bool newCapture);

  // set whether it is the pawn's first move: controller responsible to set this to false after the pawn's first move
  void setFirstMove(bool newMove);

  // checks if a move is valid for the King piece
  bool validMove(Position start, Position end) const override;

};
#endif
