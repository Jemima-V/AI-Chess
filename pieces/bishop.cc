#include "bishop.h"
#include "board.h"

// ctor
Bishop::Bishop(int owner, bool captured, char id): Pieces(owner, captured, id) {}

// dtor
Bishop::~Bishop() {}

bool Bishop::validMove(Position start, Position end, Board* board) const {
    // a move is only diagonal if the ABSOLUTE change in rank is equal to the ABSOLUTE change in file
    int rankChange = end.rank - start.rank;
    int fileChange = end.file - start.file;
    // covert rankChange to ABS
    int ABSrankChange = convertToABS(rankChange);
    // convert fileChange to ABS
    int ABSfileChange = convertToABS(fileChange);
    // compare both ABSrankChange and ABSfileChange
    if (ABSrankChange == ABSfileChange) {
        return true;
    } else {
        return false;
    }
}

// checks if a move is fully valid, this is overridden by each derived piece
bool Bishop::validMoveFinal(Position start, Position end, Board* board) const {
    Pieces* currPiece = board->pieceAt(start);
    int currPlayer = currPiece->getOwner();
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
    bool piecesInTheWay = board->checkDiagonal(start, end);
    if (piecesInTheWay == false) {
        return false;
    }
    // make sure the move doesn't put the king in check
    bool checkMoveKingInCheck = currPiece->myKingInCheck(start, end, board);
    if (checkMoveKingInCheck == false) { // false = move is invalid
        return false;
    }
    return true;
}

Bishop* Bishop::makeCopy() const {
    return (new Bishop(*this));
}

// generate all valid moves for each derived piece -> TO IMPLEMENT STILLL!!!!
std::vector<Position> Bishop::moveGenerator(Position loc) const {
    std::vector<Position> moveList;
    return moveList;
}
