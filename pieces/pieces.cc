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
bool Pieces::isValidCastling(Position start, Position end, Board* board) const {
    // the start and end for the king must be a castling move
    int rankChange = end.rank - start.rank;
    int fileChange = end.file - start.file;
    // covert rankChange to ABS
    int ABSrankChange = convertToABS(rankChange);
    // convert fileChange to ABS
    int ABSfileChange = convertToABS(fileChange);
    if (ABSrankChange != 0) {
        return false;
    }
    if (ABSfileChange != 2) {
        return false;
    }
    // check that the start piece is a king
    Pieces* currPiece = board->pieceAt(start);
    int currPlayer = currPiece->getOwner();
    char currID = currPiece->getId();
    // king ID -> white (1): K, black(2): k
    if (currPlayer == 1 && currID != 'K') {
            return false;
    }
    if (currPlayer == 2 && currID != 'k') {
            return false;
    }
    // determine which direction the King is attempting to move
    int file1 = start.file;
    int file2 = end.file;
    bool moveLeft = false;
    if (file1 > file2) {
        moveLeft == true;
    }
    // king and rook must not have previously been moved in the game
    // king: we know now that the king is the start piece
    if (currPiece->getMoved() != false) {
        return false;
    }
    // rook
    Pieces* rook = nullptr;
    int kingRook = -1; // hardcoded for the next condition
    Position rookPos1{0,0};
    Position rookPos2{0,7};
    Position rookPos3{7,0};
    Position rookPos4{7,7};
    if (moveLeft == true && currPlayer == 1) {
        rook = board->pieceAt(rookPos1);
        kingRook = 1;
    } else if (moveLeft == true && currPlayer == 2) {
        rook = board->pieceAt(rookPos2);
        kingRook = 2;
    } else if (moveLeft == false && currPlayer == 1) {
        rook = board->pieceAt(rookPos3);
        kingRook = 3;
    } else { // moveLeft == false and currPlayer == 2
        rook = board->pieceAt(rookPos4);
        kingRook = 4;
    }
    if (rook->getMoved() != false) {
        return false;
    }
    // there should not be any pieces between the king and the rook
    bool placeCheck = false;
    if (kingRook == 1) {
        placeCheck = board->checkRow(start, rookPos1);
    } else if (kingRook == 2) {
        placeCheck = board->checkRow(start, rookPos2);
    } else if (kingRook == 3) {
        placeCheck = board->checkRow(start, rookPos3);
    } else {
        placeCheck = board->checkRow(start, rookPos4);
    }
    if (placeCheck == true) {
        return false;
    }
    // the king must not be in check at the starting, ending, or in between position
    // start
    if (kingSelfCheck(start, board) == true) {
        return false;
    }
    // end 
    if (kingSelfCheck(end, board) == true) {
        return false;
    }
    // in between pos
    if (moveLeft == true) {
        Position pos{start.file - 1, start.rank};
        if (kingSelfCheck(pos, board) == true) {
            return false;
        }
    } else {
        Position pos{start.file + 1, start.rank};
        if (kingSelfCheck(pos, board) == true) {
            return false;
        }
    }
    return true;
}

// checks if the move for the player's piece places the player's King in check:
// false if this move is invalid and the king can go in check
// true if the move is valid and the king can't go in check
bool Pieces::myKingInCheck(Position start, Position end, Board* board) const {
    // Pseudocode:
    // get what piece is at our current location
    // check all 8 directions for opponent players
        // if there is an opponent player, check if it is a validMove (NOT VALIDMOVEFINAL) from that player to my king
            // if there is a valid move, return false
        // else return true
    // Implememtation:
    // get what piece is at our current location
    Pieces* currPiece = board->pieceAt(start);
    int currPlayer = currPiece->getOwner();
    Position KingLoc{0,0};
    if (currPlayer == 1) {
        KingLoc = board->getWhiteKing();
    } else { //currPlayer is 2
        KingLoc = board->getBlackKing();
    }
    // check all 8 directions for opponent players
    // up column: make sure start != end to keep invariants
    Position upCol{start.file, 7};
    bool sameLocUp = checkSamePos(start, upCol);
    Position upColPiecePos;
    if (sameLocUp == false) { // make sure start != end to keep invariants
        upColPiecePos = board->checkColOpp(currPlayer, start, upCol); 
    }
    // upColPiecePos will be (-1, -1) if there is nothing in the way
    Position nullPos{-1, -1};
    if (checkSamePos(upColPiecePos, nullPos) != true) { // there is a piece in the way
        Pieces* upColPiece = board->pieceAt(upColPiecePos);
        // check whether that piece can harm our king
        // call validMove for this piece with (start position end) and (end position the King's location)
        bool potentialKill = upColPiece->validMove(upColPiecePos, KingLoc, board);
        if (potentialKill == true) {
            return false;
        }
    }
    // down column: make sure start != end to keep invariants
    Position downCol{start.file, 0};
    bool sameLocDown = checkSamePos(start, downCol);
    Position downColPiecePos;
    if (sameLocDown == false) { // make sure start != end to keep invariants
        downColPiecePos = board->checkColOpp(currPlayer, start, downCol); 
    }
    // downColPiecePos will be (-1, -1) if there is nothing in the way
    if (checkSamePos(downColPiecePos, nullPos) != true) { // there is a piece in the way
        Pieces* downColPiece = board->pieceAt(downColPiecePos);
        // check whether that piece can harm our king
        // call validMove for this piece with (start position end) and (end position the King's location)
        bool potentialKill = downColPiece->validMove(downColPiecePos, KingLoc, board);
        if (potentialKill == true) {
            return false;
        }
    }
    // check the rows of the king to make sure the opponent's pieces potentially at these places can't harm the king
    // left side row: make sure start != end to keep invariants
    Position leftRow{0, start.rank};
    bool sameLocLeft = checkSamePos(start, leftRow);
    Position leftRowPiecePos;
    if (sameLocLeft == false) { // make sure start != end to keep invariants
        leftRowPiecePos = board->checkRowOpp(currPlayer, start, leftRow); 
    }
    // leftRowPiecePos will be (-1, -1) if there is nothing in the way
    if (checkSamePos(leftRowPiecePos, nullPos) != true) { // there is a piece in the way
        Pieces* leftRowPiece = board->pieceAt(leftRowPiecePos);
        // check whether that piece can harm our king
        // call validMove for this piece with (start position end) and (end position the King's location)
        bool potentialKill = leftRowPiece->validMove(leftRowPiecePos, KingLoc, board);
        if (potentialKill == true) {
            return false;
        }
    }
    // right side row: make sure start != end to keep invariants
    Position rightRow{7, start.rank};
    bool sameLocRight = checkSamePos(start, rightRow);
    Position rightRowPiecePos;
    if (sameLocRight == false) { // make sure start != end to keep invariants
        rightRowPiecePos = board->checkRowOpp(currPlayer, start, rightRow); 
    }
    // rightRowPiecePos will be (-1, -1) if there is nothing in the way
    if (checkSamePos(rightRowPiecePos, nullPos) != true) { // there is a piece in the way
        Pieces* rightRowPiece = board->pieceAt(rightRowPiecePos);
        // check whether that piece can harm our king
        // call validMove for this piece with (start position end) and (end position the King's location)
        bool potentialKill = rightRowPiece->validMove(rightRowPiecePos, KingLoc, board);
        if (potentialKill == true) {
            return false;
        }
    }
    // check the diagonals of the king to make sure the opponent's pieces potentially at these places can't harm the king
    // 1 = left up, 2 = left down, 3 = right up, 4 = right down
    Position leftUpPiecePos = board->checkDiagOpp(currPlayer, start, 1);
    // leftUpPiecePos will be (-1, -1) if there is nothing in the way
    if (checkSamePos(leftUpPiecePos, nullPos) != true) { // there is a piece in the way
        Pieces* leftUpPiece = board->pieceAt(leftUpPiecePos);
        // check whether that piece can harm our king
        // call validMove for this piece with (start position end) and (end position the King's location)
        bool potentialKill = leftUpPiece->validMove(leftUpPiecePos, KingLoc, board);
        if (potentialKill == true) {
            return false;
        }
    }
    Position leftDownPiecePos = board->checkDiagOpp(currPlayer, start, 2);
    // leftDownPiecePos will be (-1, -1) if there is nothing in the way
    if (checkSamePos(leftDownPiecePos, nullPos) != true) { // there is a piece in the way
        Pieces* leftDownPiece = board->pieceAt(leftDownPiecePos);
        // check whether that piece can harm our king
        // call validMove for this piece with (start position end) and (end position the King's location)
        bool potentialKill = leftDownPiece->validMove(leftDownPiecePos, KingLoc, board);
        if (potentialKill == true) {
            return false;
        }
    }
    Position rightUpPiecePos = board->checkDiagOpp(currPlayer, start, 3);
    // rightUpPiecePos will be (-1, -1) if there is nothing in the way
    if (checkSamePos(rightUpPiecePos, nullPos) != true) { // there is a piece in the way
        Pieces* rightUpPiece = board->pieceAt(rightUpPiecePos);
        // check whether that piece can harm our king
        // call validMove for this piece with (start position end) and (end position the King's location)
        bool potentialKill = rightUpPiece->validMove(rightUpPiecePos, KingLoc, board);
        if (potentialKill == true) {
            return false;
        }
    }
    Position rightDownPiecePos = board->checkDiagOpp(currPlayer, start, 4);
    // rightDownPiecePos will be (-1, -1) if there is nothing in the way
    if (checkSamePos(rightDownPiecePos, nullPos) != true) { // there is a piece in the way
        Pieces* rightDownPiece = board->pieceAt(rightDownPiecePos);
        // check whether that piece can harm our king
        // call validMove for this piece with (start position end) and (end position the King's location)
        bool potentialKill = rightDownPiece->validMove(rightDownPiecePos, KingLoc, board);
        if (potentialKill == true) {
            return false;
        }
    }
    return true;
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

// return whether the king is in check
bool Pieces::getInCheck() const {}

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

// return whether the king, rook has moved
bool Pieces::getMoved() const {}

// set whether the king, rook has moved
void Pieces::setMoved(bool newMoved) {}

// set whether it is the pawn's first move: controller responsible to set this to false after the pawn's first move
void Pieces::setFirstMove(bool newMove) {}

// checks if there is a piece of the other player diagonal to the pawn
bool Pieces::potentialCapture(Position start, Position end, Board* board) const {}

// return whether castling was done
bool Pieces::getCastlingDone() const {}

// set whether castling was done
void Pieces::setCastlingDone(bool newCastling) {}

// set whether the king is in check
void Pieces::setInCheck(bool newCheck) {}

// check if king, at loc, puts itself in check
// true if it puts itself in check and false if it doesn't
bool Pieces::kingSelfCheck(Position loc, Board* board) const {
    // Pseudocode:
    // check all 8 directions for opponent players
        // if there is an opponent player, check if it is a validMove (NOT VALIDMOVEFINAL) from that player to my king
            // if there is a valid move, return false
        // else return true
    // Implememtation:
    Pieces* currPiece = board->pieceAt(loc);
    int currPlayer = currPiece->getOwner();
    // check all 8 directions for opponent players
    // up column: make sure start != end to keep invariants
    Position upCol{loc.file, 7};
    bool sameLocUp = checkSamePos(loc, upCol);
    Position upColPiecePos;
    if (sameLocUp == false) { // make sure start != end to keep invariants
        upColPiecePos = board->checkColOpp(currPlayer, loc, upCol); 
    }
    // upColPiecePos will be (-1, -1) if there is nothing in the way
    Position nullPos{-1, -1};
    if (checkSamePos(upColPiecePos, nullPos) != true) { // there is a piece in the way
        Pieces* upColPiece = board->pieceAt(upColPiecePos);
        // check whether that piece can harm our king
        // call validMove for this piece with (start position end) and (end position the King's location)
        bool potentialKill = upColPiece->validMove(upColPiecePos, loc, board);
        if (potentialKill == true) {
            return false;
        }
    }
    // down column: make sure start != end to keep invariants
    Position downCol{loc.file, 0};
    bool sameLocDown = checkSamePos(loc, downCol);
    Position downColPiecePos;
    if (sameLocDown == false) { // make sure start != end to keep invariants
        downColPiecePos = board->checkColOpp(currPlayer, loc, downCol); 
    }
    // downColPiecePos will be (-1, -1) if there is nothing in the way
    if (checkSamePos(downColPiecePos, nullPos) != true) { // there is a piece in the way
        Pieces* downColPiece = board->pieceAt(downColPiecePos);
        // check whether that piece can harm our king
        // call validMove for this piece with (start position end) and (end position the King's location)
        bool potentialKill = downColPiece->validMove(downColPiecePos, loc, board);
        if (potentialKill == true) {
            return false;
        }
    }
    // check the rows of the king to make sure the opponent's pieces potentially at these places can't harm the king
    // left side row: make sure start != end to keep invariants
    Position leftRow{0, loc.rank};
    bool sameLocLeft = checkSamePos(loc, leftRow);
    Position leftRowPiecePos;
    if (sameLocLeft == false) { // make sure start != end to keep invariants
        leftRowPiecePos = board->checkRowOpp(currPlayer, loc, leftRow); 
    }
    // leftRowPiecePos will be (-1, -1) if there is nothing in the way
    if (checkSamePos(leftRowPiecePos, nullPos) != true) { // there is a piece in the way
        Pieces* leftRowPiece = board->pieceAt(leftRowPiecePos);
        // check whether that piece can harm our king
        // call validMove for this piece with (start position end) and (end position the King's location)
        bool potentialKill = leftRowPiece->validMove(leftRowPiecePos, loc, board);
        if (potentialKill == true) {
            return false;
        }
    }
    // right side row: make sure start != end to keep invariants
    Position rightRow{7, loc.rank};
    bool sameLocRight = checkSamePos(loc, rightRow);
    Position rightRowPiecePos;
    if (sameLocRight == false) { // make sure start != end to keep invariants
        rightRowPiecePos = board->checkRowOpp(currPlayer, loc, rightRow); 
    }
    // rightRowPiecePos will be (-1, -1) if there is nothing in the way
    if (checkSamePos(rightRowPiecePos, nullPos) != true) { // there is a piece in the way
        Pieces* rightRowPiece = board->pieceAt(rightRowPiecePos);
        // check whether that piece can harm our king
        // call validMove for this piece with (start position end) and (end position the King's location)
        bool potentialKill = rightRowPiece->validMove(rightRowPiecePos, loc, board);
        if (potentialKill == true) {
            return false;
        }
    }
    // check the diagonals of the king to make sure the opponent's pieces potentially at these places can't harm the king
    // 1 = left up, 2 = left down, 3 = right up, 4 = right down
    Position leftUpPiecePos = board->checkDiagOpp(currPlayer, loc, 1);
    // leftUpPiecePos will be (-1, -1) if there is nothing in the way
    if (checkSamePos(leftUpPiecePos, nullPos) != true) { // there is a piece in the way
        Pieces* leftUpPiece = board->pieceAt(leftUpPiecePos);
        // check whether that piece can harm our king
        // call validMove for this piece with (start position end) and (end position the King's location)
        bool potentialKill = leftUpPiece->validMove(leftUpPiecePos, loc, board);
        if (potentialKill == true) {
            return false;
        }
    }
    Position leftDownPiecePos = board->checkDiagOpp(currPlayer, loc, 2);
    // leftDownPiecePos will be (-1, -1) if there is nothing in the way
    if (checkSamePos(leftDownPiecePos, nullPos) != true) { // there is a piece in the way
        Pieces* leftDownPiece = board->pieceAt(leftDownPiecePos);
        // check whether that piece can harm our king
        // call validMove for this piece with (start position end) and (end position the King's location)
        bool potentialKill = leftDownPiece->validMove(leftDownPiecePos, loc, board);
        if (potentialKill == true) {
            return false;
        }
    }
    Position rightUpPiecePos = board->checkDiagOpp(currPlayer, loc, 3);
    // rightUpPiecePos will be (-1, -1) if there is nothing in the way
    if (checkSamePos(rightUpPiecePos, nullPos) != true) { // there is a piece in the way
        Pieces* rightUpPiece = board->pieceAt(rightUpPiecePos);
        // check whether that piece can harm our king
        // call validMove for this piece with (start position end) and (end position the King's location)
        bool potentialKill = rightUpPiece->validMove(rightUpPiecePos, loc, board);
        if (potentialKill == true) {
            return false;
        }
    }
    Position rightDownPiecePos = board->checkDiagOpp(currPlayer, loc, 4);
    // rightDownPiecePos will be (-1, -1) if there is nothing in the way
    if (checkSamePos(rightDownPiecePos, nullPos) != true) { // there is a piece in the way
        Pieces* rightDownPiece = board->pieceAt(rightDownPiecePos);
        // check whether that piece can harm our king
        // call validMove for this piece with (start position end) and (end position the King's location)
        bool potentialKill = rightDownPiece->validMove(rightDownPiecePos, loc, board);
        if (potentialKill == true) {
            return false;
        }
    }
    return true;
}

// check whether the pawn did a valid capture en passant -> TO IMPLEMENT STILLL!!!!
bool Pieces::validCaptureEnPassant(Position start, Position end, Board* board) const {
    return false;
}

