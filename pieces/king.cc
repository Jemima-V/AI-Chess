#include "king.h"

// ctor
King::King(Player owner, int id): owner{owner}, id{id} {}

// dtor
King::~King() {}

bool validMove(Position start, Position end, const Board& board) const {
    // implementaion here
}

