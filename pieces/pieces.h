#ifndef _PIECES_H_
#define _PIECES_H_
//forward declaration (only if we have ptrs) so we know that Board and Player exist OR include board and player class directly


// to discuss - having a position struct that stores the rank and file of each piece 
struct Position {
  // e.g h5 -> file = h(8) and rank = 5
  int file; // cols
  int rank; // rows
};

class Pieces {
 protected:
  // change this to Player owner once Malvika makes the Player class!!
  int owner; // 1 for player 1 (moves up the board) and 2 for player 2 (moves down the board)
  bool gotCaptured;

 public:
  //ctor
  Pieces(int owner, bool gotCaptured);

  //dtor
  virtual ~Pieces();

  // return the owner of the specfied piece
  int getowner() const;

  // checks if a move is valid, this is overridden by each derived piece
  virtual bool validMove(Position start, Position end) const = 0;

  // checks if a potential move is blocked by other pieces in the way
  // potential change to checkRow, checkPos, and checkCol?
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
