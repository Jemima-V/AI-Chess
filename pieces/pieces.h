#ifndef _OBSERVER_H_
#define _OBSERVER_H_
#include <string>
//forward declaration so we know that Board, Player, and Position exist


class Pieces {
 protected:
  Player owner;
  int id() const;

 public:
  //ctor
  Pieces(Player owner, int id);

  // return the owner of the specfied piece
  Player getowner() const;

  // We can give each piece an id from 0-15 -this would be done in the Player class when we create the respective
  //   pieces for each player
  int getid() const;

  // checks if a move is valid, this is overridden by each derived piece
  virtual bool validMove(Position start, Position end, const Board& board) const = 0;

  // it would be better to implement this here instead of in the Board class since checkRow, checkPos, and checkCol 
  //   are more related to pieces than the board
  // checks if a potential move is blocked by other pieces in the way
  bool checkBlock(Position start, Position end, const Board& board) const;

  // discuss implementaion of these vs paper methods 
  /*
  virtual int getColour(); // fix to enum later!!!!!!!!!!!!!!!!!!!!!!!!
  virtual std::string getPos(); // discuss the implementation without the Square!!!!!!!!!!!!!!
  virtual void setPos(Board b, int rank, int file); // difference between setPos and moveTo???
  virtual bool onBoard();
  virtual void moveTo(int rank, int file, Player p);
  virtual void validMove(Board b, int rank, int file); // made this different from the UML - must update
  virtual void attack(int rank, int file); // different because of Square
  */
};
#endif
