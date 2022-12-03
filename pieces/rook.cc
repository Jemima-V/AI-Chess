#include "rook.h"
#include "board.h"

using namespace std;

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

bool Rook::validMove(Position start, Position end, Board* board) const {
    // start and end files must be the same OR start and end ranks must be the same
    if ((start.rank == end.rank) || (start.file == end.file)) {
        return true;
    } else {
        return false;
    }
}

// checks if a move is fully valid, this is overridden by each derived piece
bool Rook::validMoveFinal(Position start, Position end, Board* board) const {
    Pieces* currPiece = board->pieceAt(start);
    int currPlayer = currPiece->getOwner();
    if (currPiece->inBounds(start) == false) {
        return false;
    }
    if (currPiece->inBounds(end) == false) {
        return false;
    }
    // validMove == true
    if (currPiece->validMove(start, end, board) == false) {
        return false;
    }
    // can't capture piece of your own player piece: check that the same piece owner isn't at the end position
    Pieces* endPiece = board->pieceAt(end);
    if (endPiece != nullptr) {
        int endPlayer = endPiece->getOwner();
        if (currPlayer == endPlayer) {
            return false;
        }
    }
    // no other pieces are in the way: false if someone is in the way
    // check if it moves columns or rows
    if (start.rank == end.rank) { // rows
        bool piecesInTheWay = board->checkRow(start, end);
        if (piecesInTheWay == false) {
            return false;
        }
    } else { // cols
        bool piecesInTheWay = board->checkCol(start, end);
        if (piecesInTheWay == false) {
            return false;
        }
    }
    // make sure the move doesn't put the king in check
    bool checkMoveKingInCheck = currPiece->myKingInCheck(start, end, board);
    if (checkMoveKingInCheck == false) { // false = move is invalid
        return false;
    }
    return true;
}
 
Rook* Rook::makeCopy() const {
    return (new Rook(*this));
}

// generate all valid moves for each derived piece -> TO IMPLEMENT STILLL!!!!
std::vector<Position> Rook::moveGenerator(Position loc, Board* board) const {
    std::vector<Position> moveList;
    //creates a new location for the rook
    for (int i = 0; i <= 7; ++i) {
        for (int j = 0; j <= 7; ++j) {
            //new location that the rook is being moved to 
            Position newLoc{i, j};
            bool isValid = validMoveFinal(loc, newLoc, board);
            if (isValid == true) {
                moveList.push_back(newLoc);
            }
        }
    }
    return moveList;
}

