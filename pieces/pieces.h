#ifndef _PIECES_H_
#define _PIECES_H_
#include <vector>

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

  // for the board copy ctor
  virtual Pieces* makeCopy() const = 0;

  // checks if a move is base valid (i.e the piece is allowed to move from start to end), 
  //  this is overridden by each derived piece
  virtual bool validMove(Position start, Position end, Board* board) const = 0;

  // checks if a move is fully valid, this is overridden by each derived piece
  virtual bool validMoveFinal(Position start, Position end, Board* board) const = 0;

  // generate all valid moves for each derived piece -> TO IMPLEMENT STILLL!!!!
  virtual std::vector<Position> moveGenerator(Position loc, Board* board) const = 0;

  // returns true if there is a piece of the same colour at the end position
  bool samePieceCheck(Position start, Position end, Board* board) const;

  // checks if castling is allowed for the King
  bool isValidCastling(Position start, Position end, Board* board) const;

  // checks if the king is in check on the board -> TO IMPLEMENT STILLL!!!!
  bool inCheck(int owner, Board* board) const;

  // checks if the move for the player's piece places the player's King in check -> TO IMPLEMENT STILLL!!!!
  bool myKingInCheck(Position start, Position end, Board* board) const;

  // check if king, making move from start to end, puts itself in check -> TO IMPLEMENT STILLL!!!!
  // true if it puts itself in check and false if it doesn't
  bool kingSelfCheck(Position start, Position end, Board* board) const;

  // checks if the move for the player's piece places the Opponent's King in check
  bool opponentKingInCheck(Position start, Position end, Board* board) const;

  // checks if the move for the player's piece places the Opponent's King in checkmate -> TO IMPLEMENT STILLL!!!!
  bool opponentKingCheckmate(Position start, Position end, Board* board) const;

  // specific methods for pieces that are set to empty and get overridden
  // return whether the king, rook has moved
  virtual bool getMoved() const;

  // set whether the king, rook has moved
  virtual void setMoved(bool newMoved);

  // set whether it is the pawn's first move: controller responsible to set this to false after the pawn's first move
  virtual void setFirstMove(bool newMove);

  // checks if there is a piece of the other player diagonal to the pawn
  virtual bool potentialCapture(Position start, Position end, Board* board) const;

  // return whether castling was done
  virtual bool getCastlingDone() const;

  // set whether castling was done
  virtual void setCastlingDone(bool newCastling);

  // return whether the king is in check
  virtual bool getInCheck() const;

  // set whether the king is in check
  virtual void setInCheck(bool newCheck);

  // check whether the pawn did a valid capture en passant -> TO IMPLEMENT STILLL!!!!
  bool validCaptureEnPassant(Position start, Position end, Board* board) const;

  bool checkBounds(Position pos);

};
#endif
