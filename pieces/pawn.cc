#include "pawn.h"

// ctor
Pawn::Pawn(Player owner, int id): Pieces(owner, id) {}

// dtor
Pawn::~Pawn() {}

bool Pawn::validMove(Position start, Position end, const Board& board) const {
    // implementaion here
    return true;
}
