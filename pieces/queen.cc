#include "queen.h"

// ctor
Queen::Queen(Player owner, int id): Pieces(owner, id) {}

// dtor
Queen::~Queen() {}

bool Queen::validMove(Position start, Position end, const Board& board) const {
    // implementaion here
    return true;
}

