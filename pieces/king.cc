#include "king.h"

// ctor
King::King(int owner, bool captured, char id): Pieces(owner, captured, id) {}

// dtor
King::~King() {}

bool King::getCastlingDone() const {
    return castlingDone;
}

void King::setCastlingDone(bool newCastling) {
    castlingDone = newCastling;
}

// return whether the king has moved
bool King::getMoved() const {
    return moved;
}

// set whether the king has moved
void King::setMoved(bool newMoved) {
    moved = newMoved;
}

bool King::validMove(Position start, Position end, const Board& board) const {
    // moves the same as the Queen but only one block at a time
    int rankChange = end.rank - start.rank;
    int fileChange = end.file - start.file;
    // covert rankChange to ABS
    int ABSrankChange = convertToABS(rankChange);
    // convert fileChange to ABS
    int ABSfileChange = convertToABS(fileChange);
    if (rankChange != 1 || rankChange != -1 || fileChange != 1 || fileChange != -1) {
        return false;
    } else if ((start.rank == end.rank) || (start.file == end.file)) { 
        // Rook's rules (refer to Rook.cc for implementation specific comments)
        return true;
    } else if (ABSrankChange == ABSfileChange) {
        // Bishop's rules (refer to Bishop.cc for implementation specific comments)
        return true;
    } else {
        return false;
    }
}

// checks if castling is allowed for the King
bool King::isValidCastling(Position start, Position end, const Board& board, Pieces* p) const {
    // king and rook must not have previously been moved in the game
    // there should not be any pieces between the king and the rook
    // the king must not be in check at the starting, ending, or in between positions
    // the start and end for the king must be a castling move
}

// checks if the move for the player's piece places the player's King in check
bool King::myKingInCheck(Position start, Position end, const Board& board) const {
    // create a new board with the player at their end position
    // check the columns of the king to make sure the opponent's pieces potentially at these places can't harm the king
    // check the rows of the king to make sure the opponent's pieces potentially at these places can't harm the king
    // check the diagonals of the king to make sure the opponent's pieces potentially at these places can't harm the king
}

// checks if the move for the player's piece places the Opponent's King in check
bool King::opponentKingInCheck(Position start, Position end, const Board& board) const {
    // get location of the opponent's king
    // get what piece is at our current location 
    // call validMove for this piece with start position start and end position the Kings location
        // if validMove returns true, then the opponent king is now in check
        // else return false
}
