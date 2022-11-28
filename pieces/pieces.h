#ifndef _PIECES_H_
#define _PIECES_H_
#include "board.h"

// A position struct that stores the rank and file of each piece 
struct Position {
  // e.g h5 -> file = h(8) and rank = 5
  int file; // cols
  int rank; // rows
};

class Pieces {
 protected:
  // change this to Player owner once Malvika makes the Player class!!
  int owner; // 1 for player 1 (white) (moves up the board) and 2 for player 2 (black) (moves down the board)
  bool captured; // has this piece been captured
  char id; // up to board init to set these values to distinguish the pieces
  int convertToABS(int toConvert) const; // helper function for the pieces arithmetic

 public:
  //ctor
  Pieces(int owner, bool captured, char id);

  //dtor
  virtual ~Pieces();

  // return the owner of the specified piece
  int getOwner() const;

  // return the id of the specified piece
  char getId() const;

  // return whether the specific piece is captured or not
  bool getCaptured() const;

  // set whether the specific piece is captured or not
  void setCaptured(bool newCapture);

  // checks if a move is valid, this is overridden by each derived piece
  virtual bool validMove(Position start, Position end) const = 0;

  // returns true if there is a piece of the same colour at the end position
  bool samePieceCheck(Position start, Position end, const Board& board) const;

  // checks if a potential move is blocked by other pieces in the way
  // potential change to checkRow, checkPos, and checkCol? -> TO IMPLEMENT STILLL!!!!
  bool checkBlock(Position start, Position end, const Board& board) const;

  // discuss implementaion of these vs paper methods 
  /*
  virtual int getColour(); // this should be up to the player class
  virtual std::string getPos(); // this should kept track of by the player class
  virtual void setPos(Board b, int rank, int file); // difference between setPos and moveTo??? - shd be done by the board class
  virtual bool onBoard(); // boad class
  virtual void moveTo(int rank, int file, Player p); // board class
  virtual void validMove(Board b, int rank, int file); // made this different from the UML - must update
  virtual void attack(int rank, int file); // board class
  */
};
#endif
