#include "rook.h"
#include "board.h"

// ctor
Rook::Rook(int owner, bool captured, char id): Pieces(owner, captured, id) {}

// dtor
Rook::~Rook() {}

// return whether the rook has moved
bool Rook::getMoved() const {
    return moved;
}

// set whether the rook has moved
void Rook::setMoved(bool newMoved) {
    moved = newMoved;
}

bool Rook::validMove(Position start, Position end, Board* board) const {
    // start and end files must be the same OR start and end ranks must be the same
    if ((start.rank == end.rank) || (start.file == end.file)) {
        return true;
    } else {
        return false;
    }
}

// checks if a move is fully valid, this is overridden by each derived piece
bool Rook::validMoveFinal(Position start, Position end, Board* board) const {
    Pieces* currPiece = board->pieceAt(start);
    int currPlayer = currPiece->getOwner();
    // validMove == true
    if (currPiece->validMove(start, end, board) == false) {
        return false;
    }
    // can't capture piece of your own player piece: check that the same piece owner isn't at the end position
    Pieces* endPiece = board->pieceAt(end);
    if (endPiece != nullptr) {
        int endPlayer = endPiece->getOwner();
        if (currPlayer == endPlayer) {
            return false;
        }
    }
    // no other pieces are in the way: false if someone is in the way
    // check if it moves columns or rows
    if (start.rank == end.rank) { // rows
        bool piecesInTheWay = board->checkRow(start, end);
        if (piecesInTheWay == false) {
            return false;
        }
    } else { // cols
        bool piecesInTheWay = board->checkCol(start, end);
        if (piecesInTheWay == false) {
            return false;
        }
    }
    // make sure the move doesn't put the king in check
    bool checkMoveKingInCheck = currPiece->myKingInCheck(start, end, board);
    if (checkMoveKingInCheck == false) { // false = move is invalid
        return false;
    }
    return true;
}
 
Rook* Rook::makeCopy() const {
    return (new Rook(*this));
}

