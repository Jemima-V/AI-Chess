#ifndef _KING_H_
#define _KING_H_
#include "pieces.h"

class King: public Pieces {
   bool castlingDone = false; // castling initially set to false, a player can only do this once in a game
   bool moved = false; // stores whether the king has moved in the game yet
 
 public:
  //ctor
  King(int owner, bool captured, char id);

  //dtor
  ~King();

  // return whether castling was done
  bool getCastlingDone() const;

  // set whether castling was done
  void setCastlingDone(bool newCastling);

  // return whether the king has moved
  bool getMoved() const;

  // set whether the king has moved
  void setMoved(bool newMoved);

  // checks if a move is valid for the King piece
  bool validMove(Position start, Position end, const Board& board) const override;

  // checks if castling is allowed for the King -> TO IMPLEMENT STILLL!!!!
  bool isValidCastling(Position start, Position end, const Board& board, Pieces* p) const;

  // checks if the move for the player's piece places the player's King in check -> TO IMPLEMENT STILLL!!!!
  bool myKingInCheck(Position start, Position end, const Board& board) const;

  // checks if the move for the player's piece places the Opponent's King in check -> TO IMPLEMENT STILLL!!!!
  bool opponentKingInCheck(Position start, Position end, const Board& board) const;

};
#endif

