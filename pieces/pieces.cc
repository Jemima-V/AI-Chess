#include "pieces.h"
#include "board.h"

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

int Pieces::convertToABS(int toConvert) const { // helper
    if (toConvert < 0) {
        return (-1 * toConvert);
    } else {
        return toConvert;
    }
}

// helper to check if the positions are the same
bool checkSamePos(Position pos1, Position pos2) {
    if (pos1.rank == pos2.rank && pos1.file == pos2.file) {
        return true;
    } else {
        return false;
    }
}

bool Pieces::samePieceCheck(Position start, Position end, Board* board) const {
    if (board->pieceAt(start) == board->pieceAt(end)) {
        return true;
    } else {
        return false;
    }
}

// checks if castling is allowed for the King
bool Pieces::isValidCastling(Position start, Position end, Board* board, Pieces* p) const {
    // king and rook must not have previously been moved in the game
    // there should not be any pieces between the king and the rook
    // the king must not be in check at the starting, ending, or in between positions
    // the start and end for the king must be a castling move
}

// checks if the move for the player's piece places the player's King in check
bool Pieces::myKingInCheck(Position start, Position end, Board* board) const {
    // get what piece is at our current location
    Pieces* currPiece = board->pieceAt(start);
    int currPlayer = currPiece->getOwner();
    Position KingLoc{0,0};
    if (currPlayer == 1) {
        KingLoc = board->getWhiteKing();
    } else { //currPlayer is 2
        KingLoc = board->getBlackKing();
    }
    // check the columns of the king to make sure the opponent's pieces potentially at these places can't harm the king
    // up column: make sure start != end to keep invariants
    Position upCol{KingLoc.file, 7};
    bool sameLocUp = checkSamePos(KingLoc, upCol);
    Position upColPiecePos;
    if (sameLocUp == false) { // make sure start != end to keep invariants
        upColPiecePos = board->checkColOpp(currPlayer, KingLoc, upCol); 
    }
    // upColPiecePos will be (-1, -1) if there is nothing in the way
    Position nullPos{-1, -1};
    if (checkSamePos(upColPiecePos, nullPos) != true) { // there is a piece in the way
        Pieces* upColPiece = board->pieceAt(upColPiecePos);
        // check whether that piece can harm our king
        // call validMove for this piece with (start position end) and (end position the King's location)
        bool potentialKill = upColPiece->validMove(upColPiecePos, KingLoc, board);
        if (potentialKill == true) {
            return potentialKill;
        }
    }
    // down column: make sure start != end to keep invariants
    Position downCol{KingLoc.file, 0};
    bool sameLocDown = checkSamePos(KingLoc, downCol);
    Position downColPiecePos;
    if (sameLocDown == false) { // make sure start != end to keep invariants
        downColPiecePos = board->checkColOpp(currPlayer, KingLoc, downCol); 
    }
    // downColPiecePos will be (-1, -1) if there is nothing in the way
    Position nullPos{-1, -1};
    if (checkSamePos(downColPiecePos, nullPos) != true) { // there is a piece in the way
        Pieces* downColPiece = board->pieceAt(downColPiecePos);
        // check whether that piece can harm our king
        // call validMove for this piece with (start position end) and (end position the King's location)
        bool potentialKill = downColPiece->validMove(downColPiecePos, KingLoc, board);
        if (potentialKill == true) {
            return potentialKill;
        }
    }
    // check the rows of the king to make sure the opponent's pieces potentially at these places can't harm the king
    // left side row: make sure start != end to keep invariants
    Position leftRow{0, KingLoc.rank};
    bool sameLocLeft = checkSamePos(KingLoc, leftRow);
    Position leftRowPiecePos;
    if (sameLocLeft == false) { // make sure start != end to keep invariants
        leftRowPiecePos = board->checkRowOpp(currPlayer, KingLoc, leftRow); 
    }
    // leftRowPiecePos will be (-1, -1) if there is nothing in the way
    Position nullPos{-1, -1};
    if (checkSamePos(leftRowPiecePos, nullPos) != true) { // there is a piece in the way
        Pieces* leftRowPiece = board->pieceAt(leftRowPiecePos);
        // check whether that piece can harm our king
        // call validMove for this piece with (start position end) and (end position the King's location)
        bool potentialKill = leftRowPiece->validMove(leftRowPiecePos, KingLoc, board);
        if (potentialKill == true) {
            return potentialKill;
        }
    }
    // right side row: make sure start != end to keep invariants
    Position rightRow{7, KingLoc.rank};
    bool sameLocRight = checkSamePos(KingLoc, rightRow);
    Position rightRowPiecePos;
    if (sameLocRight == false) { // make sure start != end to keep invariants
        rightRowPiecePos = board->checkRowOpp(currPlayer, KingLoc, rightRow); 
    }
    // rightRowPiecePos will be (-1, -1) if there is nothing in the way
    Position nullPos{-1, -1};
    if (checkSamePos(rightRowPiecePos, nullPos) != true) { // there is a piece in the way
        Pieces* rightRowPiece = board->pieceAt(rightRowPiecePos);
        // check whether that piece can harm our king
        // call validMove for this piece with (start position end) and (end position the King's location)
        bool potentialKill = rightRowPiece->validMove(rightRowPiecePos, KingLoc, board);
        if (potentialKill == true) {
            return potentialKill;
        }
    }
    // check the diagonals of the king to make sure the opponent's pieces potentially at these places can't harm the king
    // up left must have file = 0
    // up right must have file = 7
    // down left must have file = 0
    // down right must have file = 7
}

// checks if the move for the player's piece places the Opponent's King in check
bool Pieces::opponentKingInCheck(Position start, Position end, Board* board) const {
    // get what piece is at our current location
    Pieces* currPiece = board->pieceAt(start);
    int currPlayer = currPiece->getOwner();
    if (currPlayer == 1) {
        // get location of the opponent's king
        Position opponentKingLoc = board->getBlackKing(); // white's opponent is black
        // call validMove for this piece with (start position end) and (end position the King's location)
        bool potentialKill = currPiece->validMove(end, opponentKingLoc, board);
        // if validMove returns true, then the opponent king is now in check, else return false
        return potentialKill;
    } else { // currPlayer = 2
        // get location of the opponent's king
        Position opponentKingLoc = board->getWhiteKing();
        // call validMove for this piece with (start position end) and (end position the King's location)
        bool potentialKill = currPiece->validMove(end, opponentKingLoc, board);
        // if validMove returns true, then the opponent king is now in check, else return false
        return potentialKill;
    }
}

// checks if the move for the player's piece places the Opponent's King in checkmate -> TO IMPLEMENT STILLL!!!!
bool Pieces::opponentKingCheckmate(Position start, Position end, Board* board) const {
    // get what piece is at our current location
    Pieces* currPiece = board->pieceAt(start);
    int currPlayer = currPiece->getOwner();
    Position oppKingLoc{0,0};
    if (currPlayer == 1) {
        oppKingLoc = board->getBlackKing();
    } else { //currPlayer is 2
        oppKingLoc = board->getWhiteKing();
    }
    Pieces* oppKing = board->pieceAt(oppKingLoc);
    if (oppKing->getInCheck() == true) { // check if the opponent king is in check
        // return true if the opponent king has no more valid moves
        Position up{oppKingLoc.file, oppKingLoc.rank + 1};
        bool upCol = oppKing->validMove(oppKingLoc, up, board);
        Position down{oppKingLoc.file, oppKingLoc.rank - 1};
        bool downCol = oppKing->validMove(oppKingLoc, down, board);
        Position left{oppKingLoc.file - 1, oppKingLoc.rank};
        bool leftRow = oppKing->validMove(oppKingLoc, left, board);
        Position right{oppKingLoc.file + 1, oppKingLoc.rank};
        bool rightRow = oppKing->validMove(oppKingLoc, right, board);
        Position leftup{oppKingLoc.file - 1, oppKingLoc.rank + 1};
        bool leftUpDiag = oppKing->validMove(oppKingLoc, leftup, board);
        Position leftdown{oppKingLoc.file - 1, oppKingLoc.rank - 1};
        bool leftDownDiag = oppKing->validMove(oppKingLoc, leftdown, board);
        Position rightup{oppKingLoc.file + 1, oppKingLoc.rank + 1};
        bool rightUpDiag = oppKing->validMove(oppKingLoc, rightup, board);
        Position rightdown{oppKingLoc.file + 1, oppKingLoc.rank - 1};
        bool rightDownDiag = oppKing->validMove(oppKingLoc, rightdown, board);
        if (upCol == false && downCol == false && leftRow == false && rightRow == false && leftUpDiag == false
                && leftDownDiag == false && rightUpDiag == false && rightDownDiag == false) {
            return true;
        }
        return false;
    }
    return false;
}

