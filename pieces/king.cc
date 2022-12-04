#include "king.h"
#include "board.h"

// ctor
King::King(int owner, bool captured, char id): Pieces(owner, captured, id) {}

// dtor
King::~King() {}

// return the points of the specified piece
int King::getPoints() const {
    return 0;
}

bool King::getCastlingDone() const {
    return castlingDone;
}

void King::setCastlingDone(bool newCastling) {
    castlingDone = newCastling;
}

// return whether the king has moved
bool King::getMoved() const {
    return moved;
}

// set whether the king has moved
void King::setMoved(bool newMoved) {
    moved = newMoved;
}

// return whether the king is in check
bool King::getInCheck() const {
    return inCheck;
}

// set whether the king is in check
void King::setInCheck(bool newCheck) {
    inCheck = newCheck;
}

bool King::validMove(Position start, Position end, Board* board) const {
    // moves the same as the Queen but only one block at a time
    int rankChange = end.rank - start.rank;
    int fileChange = end.file - start.file;
    // covert rankChange to ABS
    int ABSrankChange = convertToABS(rankChange);
    // convert fileChange to ABS
    int ABSfileChange = convertToABS(fileChange);
    if (ABSrankChange == 1 || ABSfileChange == 1) {
        if ((start.rank == end.rank) || (start.file == end.file)) { 
            // Rook's rules (refer to Rook.cc for implementation specific comments)
            return true;
        } else if (ABSrankChange == ABSfileChange) {
            // Bishop's rules (refer to Bishop.cc for implementation specific comments)
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

// checks if a move is fully valid, this is overridden by each derived piece
bool King::validMoveFinal(Position start, Position end, Board* board) const {
    cout << "vmf" << endl;
    Pieces* currPiece = board->pieceAt(start);
    int currPlayer = currPiece->getOwner();
    if (currPiece->checkBounds(start) == false) {
        cout << "if 1" << endl;
        return false;
    }
    if (currPiece->checkBounds(end) == false) {
        cout << "if 2" << endl;
        return false;
    }
    // validMove == true
    if (currPiece->validMove(start, end, board) == false) {
        cout << "if 3" << endl;
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
    cout << "if 4" << endl;
    if (start.rank == end.rank) { // rows
        bool piecesInTheWay = board->checkRow(start, end);
        cout << "if 5" << endl;
        if (piecesInTheWay == false) {
            return false;
        }
    } else if (start.file == end.file) { // cols
        bool piecesInTheWay = board->checkCol(start, end);
        cout << "if 6" << endl;
        if (piecesInTheWay == false) {
            return false;
        }
    } else {
        // bishop check
        bool piecesInTheWay = board->checkDiagonal(start, end); // start and end must be diagonal now
        cout << "if 7" << endl;
        if (piecesInTheWay == false) {
            return false;
        }
    }
    // make sure the move doesn't put the king in check
    cout << "check here" << endl;
    bool checkMoveKingInCheck = currPiece->kingSelfCheck(start, end, board);
    cout << "if 8" << endl;
    if (checkMoveKingInCheck == false) { // false = move is invalid
        return false;
    }
    return true;
}

King* King::makeCopy() const {
    return (new King(*this));
}

// generate all valid moves for each derived piece -> TO IMPLEMENT STILLL!!!!
std::vector<Position> King::moveGenerator(Position loc, Board* board) const {
    Pieces *p = board->pieceAt(loc);
    std::vector<Position> moveList;
    //creates a new location for the king
    for (int i = 0; i <= 7; ++i) {
        for (int j = 0; j <= 7; ++j) {
            //new location that the king is being moved to 
            Position newLoc{i, j};
            if (((loc.rank != newLoc.rank) && (loc.file != newLoc.file)) || 
                ((loc.rank != newLoc.rank) && (loc.file == newLoc.file)) ||
                ((loc.rank == newLoc.rank) && (loc.file != newLoc.file))) {
                    cout << loc.file << endl;
                    cout << loc.rank << endl;
                    cout << newLoc.file << endl;
                    cout << newLoc.rank << endl;
                    cout << p->getId() << endl;
                    cout << "here 1" << endl;
                    bool isValid = validMoveFinal(loc, newLoc, board);
                    cout << "here 2" << endl;
                    if (isValid == true) {
                        moveList.push_back(newLoc);
                    }
                }
        }
    }
    return moveList;
}

