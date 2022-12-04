#ifndef _KING_H_
#define _KING_H_
#include "pieces.h"

class King: public Pieces {
   bool castlingDone = false; // castling initially set to false, a player can only do this once in a game
   bool moved = false; // stores whether the king has moved in the game yet
   bool inCheck = false; // stores whether the king is in check or not
 
 public:
  //ctor
  King(int owner, bool captured, char id);

  //dtor
  ~King();

  // return the points of the specified piece
  int getPoints() const override;

  King* makeCopy() const override;

  // return whether castling was done
  bool getCastlingDone() const override;

  // set whether castling was done
  void setCastlingDone(bool newCastling) override;

  // return whether the king has moved
  bool getMoved() const override;

  // set whether the king has moved
  void setMoved(bool newMoved) override;

  // return whether the king is in check
  bool getInCheck() const override;

  // set whether the king is in check
  void setInCheck(bool newCheck) override;

  // checks if a move is valid for the King piece
  bool validMove(Position start, Position end, Board* board) const override;

  // checks if a move is fully valid, this is overridden by each derived piece
  bool validMoveFinal(Position start, Position end, Board* board) const override;

  // generate all valid moves for each derived piece -> TO IMPLEMENT STILLL!!!!
  std::vector<Position> moveGenerator(Position loc, Board* board) const override;

};
#endif

