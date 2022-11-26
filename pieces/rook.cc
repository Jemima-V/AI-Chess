#include "rook.h"

// ctor
Rook::Rook(int owner, int id): Pieces(owner, id) {}

// dtor
Rook::~Rook() {}

bool Rook::validMove(Position start, Position end, const Board& board) const {
    if (checkBlock(start, end, board) == false) { // there are no other pieces in the way of the move
        // start and end files must be the same OR start and end ranks must be the same
        if ((start.rank == end.rank) || (start.file == end.file)) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}
 