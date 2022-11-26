#include "bishop.h"

// ctor
Bishop::Bishop(int owner, int id): Pieces(owner, id) {}

// dtor
Bishop::~Bishop() {}

bool Bishop::validMove(Position start, Position end, const Board& board) const {
    // implementaion here
    return true;
}

