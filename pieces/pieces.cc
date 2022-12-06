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

bool Pieces::checkBounds(Position pos) {
    if(pos.file > 7 || pos.file < 0 || pos.rank > 7 || pos.rank < 0) {
        return false;
    } else {
        return true;
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
        moveLeft = true;
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
    if (rook == nullptr) {
        return false;
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
    if (placeCheck == false) {
        return false;
    }
    // the king must not be in check at the starting, ending, or in between position
    // start: call inCheck rn
    Position p{0,0};
    if (inCheck(false, p, currPlayer, board) == false) {
        return false;
    }
    // end 
    if (kingSelfCheck(start, end, board) == true) {
        return false;
    }
    // in between pos
    if (moveLeft == true) {
        Position pos{start.file - 1, start.rank};
        if (kingSelfCheck(start, pos, board) == true) {
            return false;
        }
    } else {
        Position pos{start.file + 1, start.rank};
        if (kingSelfCheck(start, pos, board) == true) {
            return false;
        }
    }
    return true;
}

// checks if the king is in check on the board
// true if king is not in check and false if the king is in check
bool Pieces::inCheck(bool kingSelfCheck, Position kingEnd, int owner, Board* board) const {
    // Pseudocode:
    // check all 8 directions for opponent players
        // if there is an opponent player, check if it is a validMoveFinal from that player to my king
            // if there is one, return false
        // else return true
    // Implememtation:
    Position KingLoc{0,0};
    if (kingSelfCheck) {
        KingLoc = kingEnd;
    } else {
        if (owner == 1) {
            KingLoc = board->getWhiteKing();
        } else { //currPlayer is 2
            KingLoc = board->getBlackKing();
        }
    }
    Position nullPos{-1, -1};
    // check all 8 directions for opponent players
    // up column: make sure start != end to keep invariants
    Position upCol{KingLoc.file, 7};
    bool sameLocUp = checkSamePos(KingLoc, upCol);
    Position upColPiecePos;
    if (sameLocUp == false) { // make sure start != end to keep invariants
        upColPiecePos = board->checkColOpp(owner, KingLoc, upCol); 
        // upColPiecePos will be (-1, -1) if there is nothing in the way
        if (checkSamePos(upColPiecePos, nullPos) != true) { // there is a piece in the way
            Pieces* upColPiece = board->pieceAt(upColPiecePos);
            // check whether that piece can harm our king
            // call validMoveFinal for this piece with (start position end) and (end position the King's location)
            bool potentialKill = upColPiece->validMoveFinal(upColPiecePos, KingLoc, board);
            if (potentialKill == true) {
                return false;
            }
        }
    }
    // down column: make sure start != end to keep invariants
    Position downCol{KingLoc.file, 0};
    bool sameLocDown = checkSamePos(KingLoc, downCol);
    Position downColPiecePos;
    if (sameLocDown == false) { // make sure start != end to keep invariants
        downColPiecePos = board->checkColOpp(owner, KingLoc, downCol); 
        // downColPiecePos will be (-1, -1) if there is nothing in the way
        if (checkSamePos(downColPiecePos, nullPos) != true) { // there is a piece in the way
            Pieces* downColPiece = board->pieceAt(downColPiecePos);
            // check whether that piece can harm our king
            // call validMoveFinal for this piece with (start position end) and (end position the King's location)
            bool potentialKill = downColPiece->validMoveFinal(downColPiecePos, KingLoc, board);
            if (potentialKill == true) {
                return false;
            }
        }
    }
    // check the rows of the king to make sure the opponent's pieces potentially at these places can't harm the king
    // left side row: make sure start != end to keep invariants
    Position leftRow{0, KingLoc.rank};
    bool sameLocLeft = checkSamePos(KingLoc, leftRow);
    Position leftRowPiecePos;
    if (sameLocLeft == false) { // make sure start != end to keep invariants
        leftRowPiecePos = board->checkRowOpp(owner, KingLoc, leftRow); 
        // leftRowPiecePos will be (-1, -1) if there is nothing in the way
        if (checkSamePos(leftRowPiecePos, nullPos) != true) { // there is a piece in the way
            Pieces* leftRowPiece = board->pieceAt(leftRowPiecePos);
            // check whether that piece can harm our king
            // call validMoveFinal for this piece with (start position end) and (end position the King's location)
            bool potentialKill = leftRowPiece->validMoveFinal(leftRowPiecePos, KingLoc, board);
            if (potentialKill == true) {
                return false;
            }
        }
    }
    // right side row: make sure start != end to keep invariants
    Position rightRow{7, KingLoc.rank};
    bool sameLocRight = checkSamePos(KingLoc, rightRow);
    Position rightRowPiecePos;
    if (sameLocRight == false) { // make sure start != end to keep invariants
        rightRowPiecePos = board->checkRowOpp(owner, KingLoc, rightRow); 
        // rightRowPiecePos will be (-1, -1) if there is nothing in the way
        if (checkSamePos(rightRowPiecePos, nullPos) != true) { // there is a piece in the way
            Pieces* rightRowPiece = board->pieceAt(rightRowPiecePos);
            // check whether that piece can harm our king
            // call validMoveFinal for this piece with (start position end) and (end position the King's location)
            bool potentialKill = rightRowPiece->validMoveFinal(rightRowPiecePos, KingLoc, board);
            if (potentialKill == true) {
                return false;
            }
        }
    }
    // check the diagonals of the king to make sure the opponent's pieces potentially at these places can't harm the king
    // 1 = left up, 2 = left down, 3 = right up, 4 = right down
    Position leftUpPiecePos = board->checkDiagOpp(owner, KingLoc, 1);
    // leftUpPiecePos will be (-1, -1) if there is nothing in the way
    if (checkSamePos(leftUpPiecePos, nullPos) != true) { // there is a piece in the way
        Pieces* leftUpPiece = board->pieceAt(leftUpPiecePos);
        // check whether that piece can harm our king
        // call validMoveFinal for this piece with (start position end) and (end position the King's location)
        bool potentialKill = leftUpPiece->validMoveFinal(leftUpPiecePos, KingLoc, board);
        if (potentialKill == true) {
            return false;
        }
    }
    Position leftDownPiecePos = board->checkDiagOpp(owner, KingLoc, 2);
    // leftDownPiecePos will be (-1, -1) if there is nothing in the way
    if (checkSamePos(leftDownPiecePos, nullPos) != true) { // there is a piece in the way
        Pieces* leftDownPiece = board->pieceAt(leftDownPiecePos);
        // check whether that piece can harm our king
        // call validMoveFinal for this piece with (start position end) and (end position the King's location)
        bool potentialKill = leftDownPiece->validMoveFinal(leftDownPiecePos, KingLoc, board);
        if (potentialKill == true) {
            return false;
        }
    }
    Position rightUpPiecePos = board->checkDiagOpp(owner, KingLoc, 3);
    // rightUpPiecePos will be (-1, -1) if there is nothing in the way
    if (checkSamePos(rightUpPiecePos, nullPos) != true) { // there is a piece in the way
        Pieces* rightUpPiece = board->pieceAt(rightUpPiecePos);
        // check whether that piece can harm our king
        // call validMoveFinal for this piece with (start position end) and (end position the King's location)
        bool potentialKill = rightUpPiece->validMoveFinal(rightUpPiecePos, KingLoc, board);
        if (potentialKill == true) {
            return false;
        }
    }
    Position rightDownPiecePos = board->checkDiagOpp(owner, KingLoc, 4);
    // rightDownPiecePos will be (-1, -1) if there is nothing in the way
    if (checkSamePos(rightDownPiecePos, nullPos) != true) { // there is a piece in the way
        Pieces* rightDownPiece = board->pieceAt(rightDownPiecePos);
        // check whether that piece can harm our king
        // call validMoveFinal for this piece with (start position end) and (end position the King's location)
        bool potentialKill = rightDownPiece->validMoveFinal(rightDownPiecePos, KingLoc, board);
        if (potentialKill == true) {
            return false;
        }
    }
    // caseL for knights: true if an opponent knight is there and can kill us and false otherwise
    bool knightCheck = board->checkL(KingLoc);
    if (knightCheck == true) {
       return false;
    }
    return true;
}

// checks if the move for the player's piece places the player's King in check:
// false if this move is invalid and the king can go in check
// true if the move is valid and the king can't go in check
bool Pieces::myKingInCheck(Position start, Position end, Board* board) const {
    Position p{0,0};
    Board boardCopy = *board; // copy ctor for the board
    // we already know that the move is valid from the pieces perspective, 
    //   we just need to see if the king goes in check once that move is made
    // stimulate the move for the currPiece on the boardCopy
    Pieces* newPiece = boardCopy.pieceAt(start);
    int currPlayer = newPiece->getOwner();
    boardCopy.makeMove(newPiece, start, end);
    // call inCheck to see if this puts our king in check and return this value
    bool isCheck = newPiece->inCheck(false, p, currPlayer, &boardCopy);
    return isCheck;
}

// checks if the move for the player's piece places the Opponent's King in check
bool Pieces::opponentKingInCheck(Position start, Position end, Board* board) const {
    // get what piece is at our current location
    Board boardCopy = *board; // copy ctor for the board
    // make the move for the currPiece on the boardCopy
    // we already know that the move is valid from the pieces perspective, 
    //   we just need to see if the king goes in check once that move is made
    // stimulate the move for the currPiece on the boardCopy
    Pieces* newPiece = boardCopy.pieceAt(start);
    cout << newPiece->getId() << endl;
    cout << start.file << start.rank << endl;
    if(newPiece != nullptr){
        int currPlayer = newPiece->getOwner();
        boardCopy.makeMove(newPiece, start, end);
        if (currPlayer == 1) {
            // get location of the opponent's king
            Position opponentKingLoc = boardCopy.getBlackKing(); // white's opponent is black
            // call validMoveFinal for this piece with (start position end) and (end position the King's location)
            bool potentialKill = newPiece->validMoveFinal(end, opponentKingLoc, &boardCopy);
            // if validMoveFinal returns true, then the opponent king is now in check, else return false
            return potentialKill;
        } else { // currPlayer = 2
            // get location of the opponent's king
            Position opponentKingLoc = boardCopy.getWhiteKing();
            // call validMoveFinal for this piece with (start position end) and (end position the King's location)
            bool potentialKill = newPiece->validMoveFinal(end, opponentKingLoc, &boardCopy);
            // if validMoveFinal returns true, then the opponent king is now in check, else return false
            return potentialKill;
        }
    }
    return false;
}

// return whether the king is in check
bool Pieces::getInCheck() const {}

// return true if the opponent king has no more valid moves, i.e king can't escape
bool checkKingEscape(Pieces* currPiece, Pieces* oppKing, Position oppKingLoc, Board* board) {
    bool upCol = false;
    bool downCol = false;
    bool leftRow = false;
    bool rightRow = false;
    bool leftUpDiag = false;
    bool leftDownDiag = false;
    bool rightUpDiag = false;
    bool rightDownDiag = false;
    Position up{oppKingLoc.file, oppKingLoc.rank + 1};
    if (currPiece->checkBounds(up) == true) {
        upCol = oppKing->validMoveFinal(oppKingLoc, up, board);
    }
    Position down{oppKingLoc.file, oppKingLoc.rank - 1};
    if (currPiece->checkBounds(up) == true) {
        downCol = oppKing->validMoveFinal(oppKingLoc, down, board);
    }
    Position left{oppKingLoc.file - 1, oppKingLoc.rank};
    if (currPiece->checkBounds(up) == true) {
        leftRow = oppKing->validMoveFinal(oppKingLoc, left, board);
    }
    Position right{oppKingLoc.file + 1, oppKingLoc.rank};
    if (currPiece->checkBounds(up) == true) {
        rightRow = oppKing->validMoveFinal(oppKingLoc, right, board);
    }
    Position leftup{oppKingLoc.file - 1, oppKingLoc.rank + 1};
    if (currPiece->checkBounds(up) == true) {
        leftUpDiag = oppKing->validMoveFinal(oppKingLoc, leftup, board);
    }
    Position leftdown{oppKingLoc.file - 1, oppKingLoc.rank - 1};
    if (currPiece->checkBounds(up) == true) {
        leftDownDiag = oppKing->validMoveFinal(oppKingLoc, leftdown, board);
    }
    Position rightup{oppKingLoc.file + 1, oppKingLoc.rank + 1};
    if (currPiece->checkBounds(up) == true) {
        rightUpDiag = oppKing->validMoveFinal(oppKingLoc, rightup, board);
    }
    Position rightdown{oppKingLoc.file + 1, oppKingLoc.rank - 1};
    if (currPiece->checkBounds(up) == true) {
        rightDownDiag = oppKing->validMoveFinal(oppKingLoc, rightdown, board);
    }
    if (upCol == false && downCol == false && leftRow == false && rightRow == false && leftUpDiag == false
            && leftDownDiag == false && rightUpDiag == false && rightDownDiag == false) {
        return true;
    } else {
        return false;
    }
}

// checks if the move for the player's piece places the Opponent's King in checkmate
bool Pieces::opponentKingCheckmate(Position start, Position end, Board* board) const {
    // get what piece is at our current location
    Position p{0,0};
    Pieces* currPiece = board->pieceAt(start);
    int currPlayer = currPiece->getOwner();
    int oppPlayer = 0;
    Position oppKingLoc{0,0};
    if (currPlayer == 1) {
        oppKingLoc = board->getBlackKing();
        oppPlayer = 2;
    } else { //currPlayer is 2
        oppKingLoc = board->getWhiteKing();
        oppPlayer = 1;
    }
    Pieces* oppKing = board->pieceAt(oppKingLoc);
    // check if the opponent king is in check after this move is made
    // (only consider if this piece is going to put the king in check and not if its alr in check)
    Board boardCopy = *board; // invoke copy ctor for the board
    // we already know that the move is valid from the pieces perspective, 
    //   we just need to see if the king goes in check once that move is made
    // stimulate the move for the currPiece on the boardCopy
    Pieces* newPiece = boardCopy.pieceAt(start);
    boardCopy.makeMove(newPiece, start, end);
    // call inCheck to see if this puts opp's king in check and return this value
    bool isCheck = newPiece->inCheck(false, p, oppPlayer, &boardCopy);
    if (isCheck == false) { // checks if the opponent king is in check
        // return true if the opponent king has no more valid moves, i.e king can't escape
        bool checkKingMovement = checkKingEscape(currPiece, oppKing, oppKingLoc, board);
        // see if our piece can get captured instead: validMove to kill from any of the opp pieces to our piece
        vector<Position> oppPositions = boardCopy.getPiecePositions(oppPlayer);
        bool replaceCapture = false;
        for (auto it : oppPositions) {
            Pieces* oppPiece = boardCopy.pieceAt(it);
            if (oppPiece->validMoveFinal(it, end, &boardCopy) == true) {
                replaceCapture = true;
            }
        }
        // see if the check is blocked by another piece that can get in the way of our kill
        //   call moveGenerator here: 
        //   go thru all the oppPieces and generate moves for them
        //     go thru all these moves and see if, when these moves are completed, inCheck for the king is now false
        bool possibleBlock = false;
        for (auto it : oppPositions) {
            Pieces* oppPiece = boardCopy.pieceAt(it);
            vector<Position> possibleMoves = oppPiece->moveGenerator(it, &boardCopy);
            for (auto it2 : possibleMoves) {
                // new board for when these moves are stimulated
                Board boardCopy2 = boardCopy; // invoke copy ctor for the board
                // we already know that the move is valid from the pieces perspective, 
                //   we just need to see if the king goes in check once that move is made
                // stimulate the move for the currPiece on the boardCopy
                Pieces* newPiece2 = boardCopy2.pieceAt(it);
                boardCopy2.makeMove(newPiece2, it, it2);
                // call inCheck to see if this puts our king out of check and return this value
                bool isCheck2 = newPiece2->inCheck(false, p, oppPlayer, &boardCopy2);
                if (isCheck2 == true) {
                    Pieces* check1 = board->pieceAt(it);
                    Pieces* check2 = boardCopy2.pieceAt(it);
                    if (check1->getId() == check1->getId()) {
                        possibleBlock = true;
                    }
                }
            }
        }
        if (checkKingMovement == true && replaceCapture == false && possibleBlock == false) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

// checks if the move for the player's piece places the Opponent's King in stalemate
//   true if there is a stalemate and false otherwise
bool Pieces::opponentKingStalemate(Position start, Position end, Board* board) const {
    // get what piece is at our current location
    Pieces* currPiece = board->pieceAt(start);
    int currPlayer = currPiece->getOwner();
    int oppPlayer = 0;
    Position oppKingLoc{0,0};
    if (currPlayer == 1) {
        oppKingLoc = board->getBlackKing();
        oppPlayer = 2;
    } else { //currPlayer is 2
        oppKingLoc = board->getWhiteKing();
        oppPlayer = 1;
    }
    Pieces* oppKing = board->pieceAt(oppKingLoc);
    // oppKing should not be in check
    Position p{0,0};
    bool checkOppKingCheck = oppKing->inCheck(false, p, oppPlayer, board);
    // no legal moves shd be available for the oppKing
    //   go thru all the oppPieces and generate moves for them, keeping count
    int legalMoveCount = 0;
    Board boardCopy = *board; // invoke copy ctor for the board
    // we already know that the move is valid from the pieces perspective, 
    //   we just need to see if the king goes in check once that move is made
    // stimulate the move for the currPiece on the boardCopy
    Pieces* newPiece = boardCopy.pieceAt(start);
    boardCopy.makeMove(newPiece, start, end);
    vector<Position> oppPositions = board->getPiecePositions(oppPlayer);
    for (auto it : oppPositions) {
        Pieces* oppPiece = board->pieceAt(it);
        vector<Position> possibleMoves = oppPiece->moveGenerator(it, &boardCopy);
        legalMoveCount += possibleMoves.size();
    }
    if (checkOppKingCheck == true && legalMoveCount == 0) {
        return true;
    } else {
        return false;
    }
}

// return whether the king, rook has moved
bool Pieces::getMoved() const {}

// set whether the king, rook has moved
void Pieces::setMoved(bool newMoved) {}

// set whether it is the pawn's first move: controller responsible to set this to false after the pawn's first move
void Pieces::setFirstMove(bool newMove) {}

// return whether it is the pawn's first move: controller responsible to set this to false after the pawn's first move
bool Pieces::getFirstMove() const {}

// checks if there is a piece of the other player diagonal to the pawn
bool Pieces::potentialCapture(Position start, Position end, Board* board) const {}

// return whether castling was done
bool Pieces::getCastlingDone() const {}

// set whether castling was done
void Pieces::setCastlingDone(bool newCastling) {}

// set whether the king is in check
void Pieces::setInCheck(bool newCheck) {}

// return whether this pawn can get captured via en passant
bool Pieces::getSetupCaptureEnPassant() const {}

// set whether this pawn can get captured via en passant
void Pieces::setSetupCaptureEnPassant(bool newCheck) {}

// check if king, at loc, puts itself in check
// true if it puts itself in check and false if it doesn't
bool Pieces::kingSelfCheck(Position start, Position end, Board* board) const {
    Board boardCopy = *board; // copy ctor for the board
    // make the move for the currPiece on the boardCopy
    Pieces* newPiece = boardCopy.pieceAt(start);
    int currPlayer = newPiece->getOwner();
    // we already know that the move is valid from the pieces perspective, 
    //   we just need to see if the king goes in check once that move is made
    // stimulate the move for the currPiece on the boardCopy
    boardCopy.makeMove(newPiece, start, end);
    Position KingLoc{0,0};
    if (currPlayer == 1) {
        KingLoc = board->getWhiteKing();
    } else { //currPlayer is 2
        KingLoc = board->getBlackKing();
    }
    bool kingSelfCheck = true;
    // call inCheck to see if this puts our king in check and return the opposite value
    // true if king is not in check and false if the king is in check
    bool isCheck = newPiece->inCheck(kingSelfCheck, end, currPlayer, &boardCopy);
    if (isCheck == true) {
        return false;
    } else {
        return true;
    }
}

bool Pieces::isOppPawnAt(Position tempPos, int curOwner, Board* board) const {
    //check if the case is in bounds and that there is a piece that is of the opponent
    Pieces* potentialPiece = board->pieceAt(tempPos);
    if (board->pieceAt(tempPos) != nullptr) {
        if (potentialPiece->checkBounds(tempPos) && potentialPiece->getOwner() != curOwner) {
            //check if that piece is a pawn
            if(board->pieceAt(tempPos)->getId() == 'p' || board->pieceAt(tempPos)->getId() == 'P'){
                return true;
            }
        }
    } else {
        return false;
    }
}

bool Pieces::pawnCheckL(int owner, Position start, Board* board) const {
    Pieces* currPiece = board->pieceAt(start);
    Position tempPos{-1,-1};
    if (owner == 1) {
        // check right
        tempPos.file = start.file + 1;
        tempPos.rank = start.rank + 2;
        if (currPiece->checkBounds(tempPos) == true) {
            if (isOppPawnAt(tempPos, owner, board)) {
                return true;
            }
        }
        // check left
        tempPos.file = start.file - 1;
        tempPos.rank = start.rank + 2;
        if (currPiece->checkBounds(tempPos) == true) {
            if (isOppPawnAt(tempPos, owner, board)) {
                return true;
            }
        }
        return false;
    } else {
        // check right
        tempPos.file = start.file + 1;
        tempPos.rank = start.rank - 2;
        if (currPiece->checkBounds(tempPos) == true) {
            if (isOppPawnAt(tempPos, owner, board)) {
                return true;
            }
        }
        // check left
        tempPos.file = start.file - 1;
        tempPos.rank = start.rank - 2;
        if (currPiece->checkBounds(tempPos) == true) {
            if (isOppPawnAt(tempPos, owner, board)) {
                return true;
            }
        }
        return false;
    }
}

// check whether there is a setup for pawn enpassant
bool Pieces::potentialSetupCaptureEnPassant(Position start, Position end, Board* board) const {
    Pieces* currPiece = board->pieceAt(start);
    char currId = currPiece->getId();
    int currPlayer = currPiece->getOwner();
    // check whether the piece is a pawn and it is the first move for the pawn
    if ((currId == 'p' || currId == 'P') && currPiece->getFirstMove() == true) {
        // check whether there is an opponent pawn to the checkL left or right of this pawn
        bool isCapture = pawnCheckL(currPlayer, start, board); 
        if (isCapture == true) {
            // decides to move 2 squares forward to avoid capture
            if (currPlayer == 1) {
                // rank changes by 2, file must stay the same
                bool checkMove = false;
                int rankChange = end.rank - start.rank;
                if ((start.file == end.file) && (rankChange == 2)) {
                    // check that it doesn't jump over other pieces
                    Position midCheck{start.file, start.rank + 1};
                    if (currPiece->checkBounds(midCheck) == false) {
                        checkMove = false;
                    }
                    Pieces* middleCheck = board->pieceAt(midCheck);
                    if (middleCheck != nullptr) {
                        checkMove = false;
                    } else {
                        checkMove = true;
                    }
                }
                if (checkMove == true) {
                    //setSetupCaptureEnPassant(bool newCheck) to true and return true
                    currPiece->setSetupCaptureEnPassant(true);
                    return true;
                } else {
                    currPiece->setSetupCaptureEnPassant(false);
                    return false;
                }
            } else { // owner == 2
                // rank changes by -2, file must stay the same
                bool checkMove = false;
                int rankChange = end.rank - start.rank;
                if ((start.file == end.file) && (rankChange == -2)) {
                    // check that it doesn't jump over other pieces
                    Position midCheck{start.file, start.rank - 1};
                    if (currPiece->checkBounds(midCheck) == false) {
                        checkMove = false;
                    }
                    Pieces* middleCheck = board->pieceAt(midCheck);
                    if (middleCheck != nullptr) {
                        checkMove = false;
                    } else {
                        checkMove = true;
                    }
                }
                if (checkMove == true) {
                    //setSetupCaptureEnPassant(bool newCheck) to true and return true
                    currPiece->setSetupCaptureEnPassant(true);
                    return true;
                } else {
                    currPiece->setSetupCaptureEnPassant(false);
                    return false;
                }
            }
        } else {
            return false;
        }
    } else {
        return false;
    }
}

// check whether the pawn did a valid capture en passant
bool Pieces::validCaptureEnPassant(Position start, Position end, Board* board) const {
    // invariant: this method will only be called on a pawn at the start position
    Pieces* currPiece = board->pieceAt(start);
    int currPlayer = currPiece->getOwner();
    if (currPlayer == 1) {
        // make sure the pawn is trying to move diagonally
        // can be the left diagonal or the right diagonal
        // rank must be +1, file must be one of +1 or -1
        int rankChange = end.rank - start.rank;
        int fileChange = end.file - start.file;
        // make sure there is an opponent's pawn right next to this piece in the direction we're about to move 
        // 1. get that direction
        if (rankChange == 1 && fileChange == 1) {
            // 2. make sure an opponent's pawn is in that direction
            Position posCheck{start.file + 1, start.rank};
            // make sure posCheck is in bounds
            if (currPiece->checkBounds(posCheck)) {
                // get the piece at posCheck and check if it is an opponent's pawn
                Pieces* potentialPawn = board->pieceAt(posCheck);
                if (potentialPawn != nullptr && potentialPawn->getId() == 'p') {
                    // make sure its the move right after the potentialSetupCaptureEnPassant
                    //   i.e setupCaptureEnPassant == true for the pawn we are about to kill
                    if (potentialPawn->getSetupCaptureEnPassant() == true) {
                        return true;
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }
            }
        } else if (rankChange == 1 && fileChange == -1) {
            // 2. make sure an opponent's pawn is in that direction
            Position posCheck{start.file - 1, start.rank};
            // make sure posCheck is in bounds
            if (currPiece->checkBounds(posCheck)) {
                // get the piece at posCheck and check if it is an opponent's pawn
                Pieces* potentialPawn = board->pieceAt(posCheck);
                if (potentialPawn != nullptr && potentialPawn->getId() == 'p') {
                    // make sure its the move right after the potentialSetupCaptureEnPassant
                    //   i.e setupCaptureEnPassant == true for the pawn we are about to kill
                    if (potentialPawn->getSetupCaptureEnPassant() == true) {
                        return true;
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }
            }
        } else {
            return false;
        }
    } else {
        // can be the left diagonal or the right diagonal
        // rank must be -1, file must be one of +1 or -1
        int rankChange = end.rank - start.rank;
        int fileChange = end.file - start.file;
        // make sure there is an opponent's pawn right next to this piece in the direction we're about to move 
        // 1. get that direction
        if (rankChange == -1 && fileChange == 1) {
            // 2. make sure an opponent's pawn is in that direction
            Position posCheck{start.file + 1, start.rank};
            // make sure posCheck is in bounds
            if (currPiece->checkBounds(posCheck)) {
                // get the piece at posCheck and check if it is an opponent's pawn
                Pieces* potentialPawn = board->pieceAt(posCheck);
                if (potentialPawn != nullptr && potentialPawn->getId() == 'P') {
                    // make sure its the move right after the potentialSetupCaptureEnPassant
                    //   i.e setupCaptureEnPassant == true for the pawn we are about to kill
                    if (potentialPawn->getSetupCaptureEnPassant() == true) {
                        return true;
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }
            }
        } else if (rankChange == -1 && fileChange == -1) {
            // 2. make sure an opponent's pawn is in that direction
            Position posCheck{start.file - 1, start.rank};
            // make sure posCheck is in bounds
            if (currPiece->checkBounds(posCheck)) {
                // get the piece at posCheck and check if it is an opponent's pawn
                Pieces* potentialPawn = board->pieceAt(posCheck);
                if (potentialPawn != nullptr && potentialPawn->getId() == 'P') {
                    // make sure its the move right after the potentialSetupCaptureEnPassant
                    //   i.e setupCaptureEnPassant == true for the pawn we are about to kill
                    if (potentialPawn->getSetupCaptureEnPassant() == true) {
                        return true;
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }
            }
        } else {
            return false;
        }
    }
    return false;
}

