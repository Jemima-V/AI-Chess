#ifndef _PAWN_H_
#define _PAWN_H_
#include "pieces.h"

class Pawn: public Pieces {
  bool firstMove; // stores whether it is the first move for the pawn
  bool setupCaptureEnPassant = false; // stores whether this pawn can get captured via en passant

 public:
  //ctor
  Pawn(int owner, bool captured, char id, bool firstMove);

  //dtor
  ~Pawn();

  // return the points of the specified piece
  int getPoints() const override;

  Pawn* makeCopy() const override;

  // set whether it is the pawn's first move: controller responsible to set this to false after the pawn's first move
  void setFirstMove(bool newMove) override;

  // return whether it is the pawn's first move: controller responsible to set this to false after the pawn's first move
  bool getFirstMove() const override;

  // return whether this pawn can get captured via en passant
  bool getSetupCaptureEnPassant() const override;

  // set whether this pawn can get captured via en passant
  void setSetupCaptureEnPassant(bool newCheck) override;

  // checks if there is a piece of the other player diagonal to the pawn
  bool potentialCapture(Position start, Position end, Board* board) const override;

  // checks if a move is valid for the pawn piece
  bool validMove(Position start, Position end, Board* board) const override;

  // checks if a move is fully valid, this is overridden by each derived piece
  bool validMoveFinal(Position start, Position end, Board* board) const override;

  // generate all valid moves for each derived piece -> TO IMPLEMENT STILLL!!!!
  std::vector<Position> moveGenerator(Position loc, Board* board) const override;

};
#endif
