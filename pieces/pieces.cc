#include "pieces.h"

// ctor
Pieces::Pieces(int owner, bool captured, char id): owner{owner}, captured{captured}, id{id} {}

// dtor
Pieces::~Pieces() {}

int Pieces::getOwner() const {
    return owner;
}

char Pieces::getId() const {
    return id;
}

bool Pieces::getCaptured() const {
    return captured;
}

void Pieces::setCaptured(bool newCapture) {
    captured = newCapture;
}

int Pieces::convertToABS(int toConvert) const {
    if (toConvert < 0) {
        return (-1 * toConvert);
    } else {
        return toConvert;
    }
}

bool Pieces::samePieceCheck(Position start, Position end, const Board& board) const {
    if (board.pieceAt(start) == board.pieceAt(end)) {
        return true;
    } else {
        return false;
    }
}

// implement checkBlock()
// if theres smtg there, what is it and which player owns it?

// new function for Position of whats blocking!!!!

