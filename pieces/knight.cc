#include "knight.h"

// ctor
Knight::Knight(Player owner, int id): Pieces(owner, id) {}

// dtor
Knight::~Knight() {}

bool Knight::validMove(Position start, Position end, const Board& board) const {
    // implementaion here
    return true;
}
