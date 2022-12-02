#ifndef _QUEEN_H_
#define _QUEEN_H_
#include "pieces.h"

class Queen: public Pieces {
 public:
  //ctor
  Queen(int owner, bool captured, char id);

  //dtor
  ~Queen();

  Queen* makeCopy() const override;

  // checks if a move is valid for the Queen piece
  bool validMove(Position start, Position end, Board* board) const override;

  // checks if a move is fully valid, this is overridden by each derived piece
  bool validMoveFinal(Position start, Position end, Board* board) const override;

  // checks if a move is fully valid, this is overridden by each derived piece -> TO IMPLEMENT STILLL!!!!
  //std::vector<Position> moveGenerator(Position loc) const override;

};
#endif

