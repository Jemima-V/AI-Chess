#include "rook.h"

// ctor
Rook::Rook(Player owner, int id): Pieces(owner, id) {}

// dtor
Rook::~Rook() {}

bool Rook::validMove(Position start, Position end, const Board& board) const {
    // implementaion here
    return true;
}

