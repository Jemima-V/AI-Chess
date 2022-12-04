#ifndef _BISHOP_H_
#define _BISHOP_H_
#include "pieces.h"

class Bishop: public Pieces {
 public:
  //ctor
  Bishop(int owner, bool captured, char id);

  //dtor
  ~Bishop();

  // return the points of the specified piece
  int getPoints() const override;

  Bishop* makeCopy() const override;

  // checks if a move is valid for the Bishop piece
  bool validMove(Position start, Position end, Board* board) const override;

  // checks if a move is fully valid, this is overridden by each derived piece
  bool validMoveFinal(Position start, Position end, Board* board) const override;

  // generate all valid moves for each derived piece -> TO IMPLEMENT STILLL!!!!
  std::vector<Position> moveGenerator(Position loc, Board* board) const override;

};
#endif
