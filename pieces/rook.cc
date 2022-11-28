#include "rook.h"

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

bool Rook::validMove(Position start, Position end, const Board& board) const {
    // start and end files must be the same OR start and end ranks must be the same
    if ((start.rank == end.rank) || (start.file == end.file)) {
        return true;
    } else {
        return false;
    }
}
 