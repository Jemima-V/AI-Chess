#include "rook.h"

// ctor
Rook::Rook(int owner, bool captured, int id): Pieces(owner, captured, id) {}

// dtor
Rook::~Rook() {}

bool Rook::validMove(Position start, Position end) const {
    // start and end files must be the same OR start and end ranks must be the same
    if ((start.rank == end.rank) || (start.file == end.file)) {
        return true;
    } else {
        return false;
    }
}
 