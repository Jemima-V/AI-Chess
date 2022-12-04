#ifndef _QUEEN_H_
#define _QUEEN_H_
#include "pieces.h"

class Queen: public Pieces {
 public:
  //ctor
  Queen(int owner, bool captured, char id);

  //dtor
  ~Queen();

  // return the points of the specified piece
  int getPoints() const override;

  Queen* makeCopy() const override;

  // checks if a move is valid for the Queen piece
  bool validMove(Position start, Position end, Board* board) const override;

  // checks if a move is fully valid, this is overridden by each derived piece
  bool validMoveFinal(Position start, Position end, Board* board) const override;

  // generate all valid moves for each derived piece -> TO IMPLEMENT STILLL!!!!
  std::vector<Position> moveGenerator(Position loc, Board* board) const override;

};
#endif

