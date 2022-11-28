#ifndef _KING_H_
#define _KING_H_
#include "pieces.h"

class King: public Pieces {
   bool castlingDone = false; // castling initially set to false, a player can only do this once in a game
 
 public:
  //ctor
  King(int owner, bool captured, char id);

  //dtor
  ~King();

  // return whether castling was done
  bool getCastlingDone() const;

  // set whether castling was done
  void setCastlingDone(bool newCastling);

  // checks if a move is valid for the King piece
  bool validMove(Position start, Position end) const override;

};
#endif

