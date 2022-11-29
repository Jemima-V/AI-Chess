#include "pieces.h"

// ctor
Pieces::Pieces(int owner, bool captured, char id): owner{owner}, captured{captured}, id{id} {}

// dtor
Pieces::~Pieces() {}

int Pieces::getOwner() const {
    return owner;
}

char Pieces::getId() const {
    return id;
}

bool Pieces::getCaptured() const {
    return captured;
}

void Pieces::setCaptured(bool newCapture) {
    captured = newCapture;
}

int Pieces::convertToABS(int toConvert) const {
    if (toConvert < 0) {
        return (-1 * toConvert);
    } else {
        return toConvert;
    }
}

bool Pieces::samePieceCheck(Position start, Position end, const Board& board) const {
    if (board.pieceAt(start) == board.pieceAt(end)) {
        return true;
    } else {
        return false;
    }
}

// checks if castling is allowed for the King
bool Pieces::isValidCastling(Position start, Position end, const Board& board, Pieces* p) const {
    // king and rook must not have previously been moved in the game
    // there should not be any pieces between the king and the rook
    // the king must not be in check at the starting, ending, or in between positions
    // the start and end for the king must be a castling move
}

// checks if the move for the player's piece places the player's King in check
bool Pieces::myKingInCheck(Position start, Position end, const Board& board) const {
    // create a new board with the player at their end position
    // check the columns of the king to make sure the opponent's pieces potentially at these places can't harm the king
    // check the rows of the king to make sure the opponent's pieces potentially at these places can't harm the king
    // check the diagonals of the king to make sure the opponent's pieces potentially at these places can't harm the king
}

// checks if the move for the player's piece places the Opponent's King in check
bool Pieces::opponentKingInCheck(Position start, Position end, const Board& board) const {
    // get what piece is at our current location
    Pieces* currPiece = board.pieceAt(end);
    int currPlayer = currPiece->getOwner();
    if (currPlayer == 1) {
        // get location of the opponent's king
        Position opponentKingLoc = board.getBlackKing(); // white's opponent is black
        // call validMove for this piece with (start position end) and (end position the King's location)
        bool potentialKill = currPiece->validMove(end, opponentKingLoc, board);
        // if validMove returns true, then the opponent king is now in check, else return false
        return potentialKill;
    } else { // currPlayer = 2
        // get location of the opponent's king
        Position opponentKingLoc = board.getWhiteKing();
        // call validMove for this piece with (start position end) and (end position the King's location)
        bool potentialKill = currPiece->validMove(end, opponentKingLoc, board);
        // if validMove returns true, then the opponent king is now in check, else return false
        return potentialKill;
    }
}

// checks if the move for the player's piece places the Opponent's King in checkmate -> TO IMPLEMENT STILLL!!!!
bool Pieces::opponentKingCheckmate(Position start, Position end, const Board& board) const {
    // 
}

