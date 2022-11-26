#include "pawn.h"

// ctor
Pawn::Pawn(int owner, int id, bool firstMove, bool capture): 
    Pieces(owner, id), firstMove{firstMove}, capture{capture} {}

// dtor
Pawn::~Pawn() {}

bool Pawn::validMove(Position start, Position end, const Board& board) const {
    if (checkBlock(start, end, board) == false) { // there are no other pieces in the way of the move
        if (owner == 1) {
            if (firstMove == true) { // move forward 2 squares only at starting position
                // rank changes by +1 or +2, file must stay the same
                int rankChange = end.rank - start.rank;
                if ((start.file == end.file) && ((rankChange == 1) || (rankChange == 2))) {
                    return true;
                } else {
                    return false;
                }
            } else if (capture == true) { // move diagonally forward only to capture
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
            } else if (capture == true) { // move diagonally forward only to capture
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
    } else {
        return false;
    }
}
