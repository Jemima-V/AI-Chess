#include "king.h"
#include "board.h"

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

// return whether the king is in check
bool King::getInCheck() const {
    return inCheck;
}

// set whether the king is in check
void King::setInCheck(bool newCheck) {
    inCheck = newCheck;
}

bool King::validMove(Position start, Position end, Board* board) const {
    // moves the same as the Queen but only one block at a time
    int rankChange = end.rank - start.rank;
    int fileChange = end.file - start.file;
    // covert rankChange to ABS
    int ABSrankChange = convertToABS(rankChange);
    // convert fileChange to ABS
    int ABSfileChange = convertToABS(fileChange);
    if (ABSrankChange == 1 || ABSfileChange == 1) {
        if ((start.rank == end.rank) || (start.file == end.file)) { 
            // Rook's rules (refer to Rook.cc for implementation specific comments)
            return true;
        } else if (ABSrankChange == ABSfileChange) {
            // Bishop's rules (refer to Bishop.cc for implementation specific comments)
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

// checks if a move is fully valid, this is overridden by each derived piece
bool King::validMoveFinal(Position start, Position end, Board* board) const {
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
    // rook check
    // check if it moves columns or rows
    if (start.rank == end.rank) { // rows
        bool piecesInTheWay = board->checkRow(start, end);
        if (piecesInTheWay == false) {
            return false;
        }
    } else if (start.file == end.file) { // cols
        bool piecesInTheWay = board->checkCol(start, end);
        if (piecesInTheWay == false) {
            return false;
        }
    } else {
        // bishop check
        bool piecesInTheWay = board->checkDiagonal(start, end); // start and end must be diagonal now
        if (piecesInTheWay == false) {
            return false;
        }
    }
    // make sure the move doesn't put the king in check
    bool checkMoveKingInCheck = currPiece->kingSelfCheck(start, end, board);
    if (checkMoveKingInCheck == false) { // false = move is invalid
        return false;
    }
    return true;
}

King* King::makeCopy() const {
    return (new King(*this));
}

// generate all valid moves for each derived piece -> TO IMPLEMENT STILLL!!!!
std::vector<Position> King::moveGenerator(Position loc, Board* board) const {
    std::vector<Position> moveList;
    return moveList;
}

