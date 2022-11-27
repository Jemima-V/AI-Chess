#include "pieces.h"

// ctor
Pieces::Pieces(int owner, bool captured, int id): owner{owner}, captured{captured}, id{id} {}

// dtor
Pieces::~Pieces() {}

int Pieces::getOwner() const {
    return owner;
}

int Pieces::getId() const {
    return id;
}

bool Pieces::getCaptured() const {
    return captured;
}

void Pieces::setCaptured(bool newCapture) {
    captured = newCapture;
}

bool Pieces::samePieceCheck(Position start, Position end) const {
    if (pieceAt(start) == pieceAt(end)) {
        return true;
    } else {
        return false;
    }
}

// implement checkBlock()
// if theres smtg there, what is it and which player owns it?

// new function for Position of whats blocking!!!!

