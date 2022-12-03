#include "queen.h"
#include "board.h"

// ctor
Queen::Queen(int owner, bool captured, char id): Pieces(owner, captured, id) {}

// dtor
Queen::~Queen() {}

bool Queen::validMove(Position start, Position end, Board* board) const {
    // combination of Rook's and Bishop's rules
    int rankChange = end.rank - start.rank;
    int fileChange = end.file - start.file;
    // covert rankChange to ABS
    int ABSrankChange = convertToABS(rankChange);
    // convert fileChange to ABS
    int ABSfileChange = convertToABS(fileChange);
    // Rook's rules: start and end files must be the same OR start and end ranks must be the same
    if ((start.rank == end.rank) || (start.file == end.file)) {
        return true;
    } else if (ABSrankChange == ABSfileChange) { 
        // Bishop's rules: a move is only diagonal if the ABSOLUTE change in rank is equal to the ABSOLUTE change in file
        return true;
    } else {
        return false;
    }
}

// checks if a move is fully valid, this is overridden by each derived piece
bool Queen::validMoveFinal(Position start, Position end, Board* board) const {
    Pieces* currPiece = board->pieceAt(start);
    int currPlayer = currPiece->getOwner();
    if (currPiece->checkBounds(start) == false) {
        return false;
    }
    if (currPiece->checkBounds(end) == false) {
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
    // rook check
    // check if it moves columns or rows
    if (start.rank == end.rank) { // rows
        bool piecesInTheWay = board->checkRow(start, end);
        if (piecesInTheWay == false) {
            return false;
        }
    } else if (start.file == end.file) { // cols
        bool piecesInTheWay = board->checkCol(start, end);
        if (piecesInTheWay == false) {
            return false;
        }
    } else {
        // bishop check
        bool piecesInTheWay = board->checkDiagonal(start, end); // start and end must be diagonal now
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

Queen* Queen::makeCopy() const {
    return (new Queen(*this));
}

// generate all valid moves for each derived piece -> TO IMPLEMENT STILLL!!!!
std::vector<Position> Queen::moveGenerator(Position loc, Board* board) const {
    std::vector<Position> moveList;
    //creates a new location for the queen
    for (int i = 0; i <= 7; ++i) {
        for (int j = 0; j <= 7; ++j) {
            //new location that the queen is being moved to 
            Position newLoc{i, j};
            if (((loc.rank != newLoc.rank) && (loc.file != newLoc.file)) || 
                ((loc.rank != newLoc.rank) && (loc.file == newLoc.file)) ||
                ((loc.rank == newLoc.rank) && (loc.file != newLoc.file))) {
                    bool isValid = validMoveFinal(loc, newLoc, board);
                    if (isValid == true) {
                        moveList.push_back(newLoc);
                    }
                }
        }
    }
    return moveList;
}

   