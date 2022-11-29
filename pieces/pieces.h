#ifndef _PIECES_H_
#define _PIECES_H_
// forward declare to avoid circular dependency
class Board;

// A position struct that stores the rank and file of each piece 
struct Position {
  // e.g h5 -> file = h(8) and rank = 5
  int file; // cols (goes from 0-7)
  int rank; // rows (goes from 0-7)
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
  virtual bool validMove(Position start, Position end, Board* board) const = 0;

  // returns true if there is a piece of the same colour at the end position
  bool samePieceCheck(Position start, Position end, Board* board) const;

  // checks if castling is allowed for the King -> TO IMPLEMENT STILLL!!!!
  bool isValidCastling(Position start, Position end, Board* board, Pieces* p) const;

  // checks if the move for the player's piece places the player's King in check -> TO IMPLEMENT STILLL!!!!
  bool myKingInCheck(Position start, Position end, Board* board) const;

  // checks if the move for the player's piece places the Opponent's King in check
  bool opponentKingInCheck(Position start, Position end, Board* board) const;

  // checks if the move for the player's piece places the Opponent's King in checkmate -> TO IMPLEMENT STILLL!!!!
  bool opponentKingCheckmate(Position start, Position end, Board* board) const;

};
#endif
