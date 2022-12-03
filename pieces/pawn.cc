#include "pawn.h"
#include "board.h"

// ctor
Pawn::Pawn(int owner, bool captured, char id, bool firstMove): 
    Pieces(owner, captured, id), firstMove{firstMove} {}

// dtor
Pawn::~Pawn() {}

void Pawn::setFirstMove(bool newMove) {
    firstMove = newMove;
}

// checks if there is a piece of the other player diagonal to the pawn
bool Pawn::potentialCapture(Position start, Position end, Board* board) const {
    Pieces* pieceToKill = board->pieceAt(end);
    if (pieceToKill != nullptr && (pieceToKill->getOwner() != (board->pieceAt(start)->getOwner()))) {
        // there is another player's piece there and the pawn can now capture 
        return true;
    }
    return false;
}

bool Pawn::validMove(Position start, Position end, Board* board) const {
    Pieces* currPiece = board->pieceAt(start);
    if (owner == 1) {
        if (potentialCapture(start, end, board) == true) { // move diagonally forward only to capture
            // can be the left diagonal or the right diagonal
            // rank must be +1, file must be one of +1 or -1
            int rankChange = end.rank - start.rank;
            int fileChange = end.file - start.file;
            if (rankChange == 1 && (fileChange == 1 || fileChange == -1)) {
                return true;
            }
        } else if (firstMove == true) { // move forward 2 squares only at starting position
            // rank changes by +1 or +2, file must stay the same
            int rankChange = end.rank - start.rank;
            if ((start.file == end.file) && (rankChange == 1)) {
                return true;
            } 
            if ((start.file == end.file) && (rankChange == 2)) {
                // check that it doesn't jump over other pieces
                Position midCheck{start.file, start.rank + 1};
                if (currPiece->checkBounds(midCheck) == false) {
                    return false;
                }
                Pieces* middleCheck = board->pieceAt(midCheck);
                if (middleCheck != nullptr) {
                    return false;
                } else {
                    return true;
                }
            }
        } else { // can only move forward 1 position
            // rank changes by +1, file must stay the same
            int rankChange = end.rank - start.rank;
            if ((start.file == end.file) && (rankChange == 1)) {
                return true;
            }
        }
    } else { // owner must be 2
        if (potentialCapture(start, end, board) == true) { // move diagonally forward only to capture
            // can be the left diagonal or the right diagonal
            // rank must be -1, file must be one of +1 or -1
            int rankChange = end.rank - start.rank;
            int fileChange = end.file - start.file;
            if (rankChange == -1 && (fileChange == 1 || fileChange == -1)) {
                return true;
            }
        } else if (firstMove == true) { // move forward 2 squares only at starting position
            // rank changes by -1 or -2, file must stay the same
            int rankChange = end.rank - start.rank;
            if ((start.file == end.file) && (rankChange == -1)) {
                return true;
            }
            if ((start.file == end.file) && (rankChange == -2)) {
                // check that it doesn't jump over other pieces
                Position midCheck{start.file, start.rank - 1};
                if (currPiece->checkBounds(midCheck) == false) {
                    return false;
                }
                Pieces* middleCheck = board->pieceAt(midCheck);
                if (middleCheck != nullptr) {
                    return false;
                } else {
                    return true;
                }
            }
        } else { // can only move forward 1 position
            // rank changes by -1, file must stay the same
            int rankChange = end.rank - start.rank;
            if ((start.file == end.file) && (rankChange == -1)) {
                return true;
            }
        }
    }
    return false;
}

// checks if a move is fully valid, this is overridden by each derived piece
bool Pawn::validMoveFinal(Position start, Position end, Board* board) const {
    Pieces* currPiece = board->pieceAt(start);
    int currPlayer = currPiece->getOwner();
    if (currPiece->checkBounds(start) == false) {
        return false;
    }
    if (currPiece->checkBounds(end) == false) {
        return false;
    }
    // validMove == true: no other piece should be in the way is already checked in here
    if (currPiece->validMove(start, end, board) == false) {
        return false;
    }
    // can't capture your own piece: check that the same piece owner isn't at the end position
    Pieces* endPiece = board->pieceAt(end);
    if (endPiece != nullptr) {
        int endPlayer = endPiece->getOwner();
        if (currPlayer == endPlayer) {
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

Pawn* Pawn::makeCopy() const {
    return (new Pawn(*this));
}

// generate all valid moves for each derived piece -> TO IMPLEMENT STILLL!!!!
std::vector<Position> Pawn::moveGenerator(Position loc, Board* board) const {
    std::vector<Position> moveList;
    //creates a new location for the pawn
    for (int i = 0; i <= 7; ++i) {
        for (int j = 0; j <= 7; ++j) {
            //new location that the pawn is being moved to 
            Position newLoc{i, j};
            if (((loc.rank != newLoc.rank) && (loc.file != newLoc.file)) || 
                ((loc.rank != newLoc.rank) && (loc.file == newLoc.file)) ||
                ((loc.rank == newLoc.rank) && (loc.file != newLoc.file))) {
                    bool isValid = validMoveFinal(loc, newLoc, board);
                    if (isValid == true) {
                        moveList.push_back(newLoc);
                    }
                }
        }
    }
    return moveList;
}

