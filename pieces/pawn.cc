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
    if (owner == 1) {
        if (firstMove == true) { // move forward 2 squares only at starting position
            // rank changes by +1 or +2, file must stay the same
            int rankChange = end.rank - start.rank;
            if ((start.file == end.file) && ((rankChange == 1) || (rankChange == 2))) {
                return true;
            } else {
                return false;
            }
        } else if (potentialCapture(start, end, board) == true) { // move diagonally forward only to capture
            // can be the left diagonal or the right diagonal
            // rank must be +1, file must be one of +1 or -1
            int rankChange = end.rank - start.rank;
            int fileChange = end.file - start.file;
            if (rankChange == 1 && (fileChange == 1 || fileChange == -1)) {
                return true;
            } else {
                return false;
            }
        } else { // can only move forward 1 position
            // rank changes by +1, file must stay the same
            int rankChange = end.rank - start.rank;
            if ((start.file == end.file) && (rankChange == 1)) {
                return true;
            } else {
                return false;
            }
        }
    } else { // owner must be 2
        if (firstMove == true) { // move forward 2 squares only at starting position
            // rank changes by -1 or -2, file must stay the same
            int rankChange = end.rank - start.rank;
            if ((start.file == end.file) && ((rankChange == -1) || (rankChange == -2))) {
                return true;
            } else {
                return false;
            }
        } else if (potentialCapture(start, end, board) == true) { // move diagonally forward only to capture
            // can be the left diagonal or the right diagonal
            // rank must be -1, file must be one of +1 or -1
            int rankChange = end.rank - start.rank;
            int fileChange = end.file - start.file;
            if (rankChange == -1 && (fileChange == 1 || fileChange == -1)) {
                return true;
            } else {
                return false;
            }
        } else { // can only move forward 1 position
            // rank changes by -1, file must stay the same
            int rankChange = end.rank - start.rank;
            if ((start.file == end.file) && (rankChange == -1)) {
                return true;
            } else {
                return false;
            }
        }
    }
}

// checks if a move is fully valid, this is overridden by each derived piece -> TO IMPLEMENT STILLL!!!!
bool Pawn::validMoveFinal(Position start, Position end, Board* board) const {
    return false;
}
