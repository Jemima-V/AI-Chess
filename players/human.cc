#include <string.h>
#include <iostream>
#include "player.h"
#include "human.h"
#include "textObserver.h"
#include "graphicsObserver.h"
#include "pieces.h"
#include "queen.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "observer.h"

using namespace std;

//checks if black has a setup for en passant
bool blackSetupEnPassant = false;

//checks if white has a setup for en passant
bool whiteSetupEnPassant = false;

//returns the Promotion piece for pawn promotion
Pieces* promo(string player, char promoChar) {
    //creates piece id
    int id;
    if (player == "white") {
        id = 1; //1 is white
    } else {
        id = 2; //2 is black
    }
    if (promoChar == 'Q') {
        if (player == "white") {
            Pieces *q = new Queen{id, false, 'Q'};
            return q;
        }
        else {
            Pieces *q = new Queen{id, false, 'q'};
            return q;
        }
    }
    else if (promoChar == 'R') {
        if (player == "white") {
            Pieces *r = new Rook{id, false, 'R'};
            return r;
        }
        else {
            Pieces *r = new Rook{id, false, 'r'};
            return r;
        }
    }
    else if (promoChar == 'K') {
        if (player == "white") {
            Pieces *k = new Knight{id, false, 'K'};
            return k;
        }
        else {
            Pieces *k = new Knight{id, false, 'k'};
            return k;
        }
    }
    else if (promoChar == 'B') {
        if (player == "white") {
            Pieces *b = new Bishop{id, false, 'B'};
            return b;
        }
        else {
            Pieces *b = new Bishop{id, false, 'b'};
            return b;
        }
    }
    //try catch?
}

//constructor 
Human::Human(string name) : Player{name}, name{name} {}

//gets the player's name
string Human::getName() {
    return name;
}

//checks if the king is on the board
bool Human::kingIsThere() {
    return kingExists;
} 

//checks if the player has moved
bool Human::hasMoved() {
    return moved;
}

void Human::setMoved(bool checkMoved) {
    moved = checkMoved;
}

//checks if black has a setup for en passant
//bool Human::getBlackSetupEnPassant() const {
  //  return blackSetupEnPassant;
//}
//checks if black has a setup for en passant
//void Human::setBlackSetupEnPassant(bool newCheck) {
  //  blackSetupEnPassant = newCheck;
//}

//checks if white has a setup for en passant
//bool Human::getWhiteSetupEnPassant() const {
  //  return whiteSetupEnPassant;
//}
//checks if white has a setup for en passant
//void Human::setWhiteSetupEnPassant(bool newCheck) {
  //  whiteSetupEnPassant = newCheck;
//}

bool Human::getInStalemate() {
    return inStalemate;
}

void Human::playerMove(Position s1, Position s2, Board *gameboard, Pieces *p, string turn) {
    bool checkPassantSetup = p->potentialSetupCaptureEnPassant(s1, s2, gameboard);
    //white moves
    if (turn == "white") {
        if (checkPassantSetup == true) {
            whiteSetupEnPassant = true;
        } else {
            whiteSetupEnPassant = false;
        }
        //castling case 1
        if (((s1.file == 4) && (s1.rank == 0)) &&
            ((s2.file == 6) && (s2.rank == 0))) {
                if (p->isValidCastling(s1, s2, gameboard) == true) {
                    bool inCheck = p->opponentKingInCheck(s1, s2, gameboard);
                    bool inCheckmate = p->opponentKingCheckmate(s1, s2, gameboard);
                    bool inStalemate = p->opponentKingStalemate(s1, s2, gameboard);
                    gameboard->makeMove(p, s1, s2); 
                    Position rpos{7, 0};
                    Position rnew{5, 0};
                    Pieces *rook = gameboard->pieceAt(rpos);
                    gameboard->makeMove(rook, rpos, rnew);
                    p->setMoved(true);
                    rook->setMoved(true);
                    moved = true;
                    gameboard->renderMove(s1.file, s1.rank, s2.file, s2.rank);
                    if (inCheck == true) {
                        cout << "Black is in check." << endl;
                        if (inCheckmate == true) {
                            kingExists = false;
                            cout << "Checkmate! White wins!" << endl;
                        }
                    }
                    if (inStalemate == true) {
                        inStalemate = true;
                        cout << "Stalemate!" << endl;
                    }
                }
        }
        //castling case 2
        else if (((s1.file == 4) && (s1.rank == 0)) &&
                ((s2.file == 2) && (s2.rank == 0))) {
                    if (p->isValidCastling(s1, s2, gameboard) == true) {
                        bool inCheck = p->opponentKingInCheck(s1, s2, gameboard);
                        bool inCheckmate = p->opponentKingCheckmate(s1, s2, gameboard);
                        bool inStalemate = p->opponentKingStalemate(s1, s2, gameboard);
                        gameboard->makeMove(p, s1, s2); 
                        Position rpos{0, 0};
                        Position rnew{3, 0};
                        Pieces *rook = gameboard->pieceAt(rpos);
                        gameboard->makeMove(rook, rpos, rnew);
                        p->setMoved(true);
                        rook->setMoved(true);
                        moved = true;
                        gameboard->renderMove(s1.file, s1.rank, s2.file, s2.rank);
                        if (inCheck == true) {
                            cout << "Black is in check." << endl;
                            if (inCheckmate == true) {
                                kingExists = false;
                                cout << "Checkmate! White wins!" << endl;
                            }
                        }
                        if (inStalemate == true) {
                            inStalemate = true;
                            cout << "Stalemate!" << endl;
                        }
                    }
        }
        //pawn promotion case
        else if ((p->getId() == 'P') && (s1.rank == 6)) {
            char promotionChar;
            cin >> promotionChar; 
            if (p->validMoveFinal(s1, s2, gameboard) == true) {
                bool inCheck = p->opponentKingInCheck(s1, s2, gameboard);
                bool inCheckmate = p->opponentKingCheckmate(s1, s2, gameboard);
                bool inStalemate = p->opponentKingStalemate(s1, s2, gameboard);
                gameboard->makeMove(p, s1, s2); 
                Pieces *promoPiece = promo("white", promotionChar);
                gameboard->place(promoPiece, s2); //replace pawn with new promoPiece
                moved = true;
                gameboard->renderMove(s1.file, s1.rank, s2.file, s2.rank);
                if (inCheck == true) {
                    cout << "Black is in check." << endl;
                    if (inCheckmate == true) {
                        kingExists = false;
                        cout << "Checkmate! White wins!" << endl;
                    }
                }
                if (inStalemate == true) {
                    inStalemate = true;
                    cout << "Stalemate!" << endl;
                }
            }      
        }
         else if (p->getId() == 'P' && blackSetupEnPassant == true) {
            if (p->validCaptureEnPassant(s1, s2, gameboard) == true) {
                // left diagonal or right diagonal
                int rankChange = s2.rank - s1.rank;
                int fileChange = s2.file - s1.file;
                Position posCheck{0,0};
                if (rankChange == 1 && fileChange == 1) {
                    posCheck.file = s1.file + 1;
                    posCheck.rank = s1.rank;
                } else { // rankChange == 1 && fileChange == -1
                    posCheck.file = s1.file - 1;
                    posCheck.rank = s1.rank;
                }
                bool inCheck = p->opponentKingInCheck(s1, s2, gameboard);
                bool inCheckmate = p->opponentKingCheckmate(s1, s2, gameboard);
                bool inStalemate = p->opponentKingStalemate(s1, s2, gameboard);
                gameboard->removePiece(posCheck);
                gameboard->makeMove(p, s1, s2);
                gameboard->renderMove(s1.file, s1.rank, s2.file, s2.rank);
                moved = true;
                if (inCheck == true) {
                    cout << "Black is in check." << endl;
                    if (inCheckmate == true) {
                        kingExists = false;
                        cout << "Checkmate! White wins!" << endl;
                    }
                }
                if (inStalemate == true) {
                    inStalemate = true;
                    cout << "Stalemate!" << endl;
                }
            }
            /*
            if (p->validCaptureEnPassant(s1, s2, gameboard) == true) {
                Position left{s1.file - 1, s1.rank + 2};
                Pieces *oppPawnL = gameboard->pieceAt(left);
                if (oppPawnL != nullptr) {
                    Position oppPawnNewPos{s1.file, s1.rank + 1};
                    gameboard->removePiece(s1);
                    gameboard->makeMove(oppPawnL, left, oppPawnNewPos);
                    //show render
                }
                else {
                    Position right{s1.file + 1, s1.rank + 2};
                    Pieces *oppPawnR = gameboard->pieceAt(right);
                    //add
                }
            }*/
        }
        //regular move
        else if (p->validMoveFinal(s1, s2, gameboard) == true) {
            bool inCheck = p->opponentKingInCheck(s1, s2, gameboard);
            bool inCheckmate = p->opponentKingCheckmate(s1, s2, gameboard);
            bool inStalemate = p->opponentKingStalemate(s1, s2, gameboard);
            gameboard->makeMove(p, s1, s2); 
            moved = true;
            gameboard->renderMove(s1.file, s1.rank, s2.file, s2.rank);
            if (inCheck == true) {
                cout << "Black is in check." << endl;
                if (inCheckmate == true) {
                    kingExists = false;
                    cout << "Checkmate! White wins!" << endl;
                }
            }
            if (inStalemate == true) {
                inStalemate = true;
                cout << "Stalemate!" << endl;
            }
            if (p->getId() == 'P') {
                if (p->getFirstMove() == true) {
                    p->setFirstMove(false);
                }
            }
        }
        else {
            moved = false;
            return;
        }
    }
    //black moves
    else if (turn == "black") {
        if (checkPassantSetup == true) {
            blackSetupEnPassant = true;
        } else {
            blackSetupEnPassant = false;
        }
        //castling case 1
        if (((s1.file == 4) && (s1.rank == 7)) &&
            ((s2.file == 6) && (s2.rank == 7))) {
                if (p->isValidCastling(s1, s2, gameboard) == true) {
                    bool inCheck = p->opponentKingInCheck(s1, s2, gameboard);
                    bool inCheckmate = p->opponentKingCheckmate(s1, s2, gameboard);
                    bool inStalemate = p->opponentKingStalemate(s1, s2, gameboard);
                    gameboard->makeMove(p, s1, s2); 
                    Position rpos{7, 7};
                    Position rnew{5, 7};
                    Pieces *rook = gameboard->pieceAt(rpos);
                    gameboard->makeMove(rook, rpos, rnew);
                    p->setMoved(true);
                    rook->setMoved(true);
                    moved = true;
                    gameboard->renderMove(s1.file, s1.rank, s2.file, s2.rank);
                    if (inCheck == true) {
                        cout << "White is in check." << endl;
                        if (inCheckmate == true) {
                            kingExists = false;
                            cout << "Checkmate! Black wins!" << endl;
                        }
                    }
                    if (inStalemate == true) {
                        inStalemate = true;
                        cout << "Stalemate!" << endl;
                    }
                }
        }
        //castling case 2
        else if (((s1.file == 4) && (s1.rank == 7)) &&
                ((s2.file == 2) && (s2.rank == 7))) {
                    if (p->isValidCastling(s1, s2, gameboard) == true) {
                        bool inCheck = p->opponentKingInCheck(s1, s2, gameboard);
                        bool inCheckmate = p->opponentKingCheckmate(s1, s2, gameboard);
                        bool inStalemate = p->opponentKingStalemate(s1, s2, gameboard);
                        gameboard->makeMove(p, s1, s2); 
                        Position rpos{0, 7};
                        Position rnew{3, 7};
                        Pieces *rook = gameboard->pieceAt(rpos);
                        gameboard->makeMove(rook, rpos, rnew);
                        p->setMoved(true);
                        rook->setMoved(true);
                        moved = true;
                        gameboard->renderMove(s1.file, s1.rank, s2.file, s2.rank);
                        if (inCheck == true) {
                            cout << "White is in check." << endl;
                            if (inCheckmate == true) {
                                kingExists = false;
                                cout << "Checkmate! Black wins!" << endl;
                            }
                        }
                        if (inStalemate == true) {
                            inStalemate = true;
                            cout << "Stalemate!" << endl;
                        }
                    }
        }
        //pawn promotion case
        else if ((p->getId() == 'p') && (s1.rank == 1)) {
            char promotionChar;
            cin >> promotionChar;
            if (p->validMoveFinal(s1, s2, gameboard) == true) {
                bool inCheck = p->opponentKingInCheck(s1, s2, gameboard);
                bool inCheckmate = p->opponentKingCheckmate(s1, s2, gameboard);
                bool inStalemate = p->opponentKingStalemate(s1, s2, gameboard);
                gameboard->makeMove(p, s1, s2); 
                Pieces *promoPiece = promo("black", promotionChar);
                gameboard->place(promoPiece, s2); //replace pawn with new promoPiece
                moved = true;
                gameboard->renderMove(s1.file, s1.rank, s2.file, s2.rank);
                if (inCheck == true) {
                    cout << "White is in check." << endl;
                    if (inCheckmate == true) {
                        kingExists = false;
                        cout << "Checkmate! Black wins!" << endl;
                    }
                }
                if (inStalemate == true) {
                    inStalemate = true;
                    cout << "Stalemate!" << endl;
                }
            }      
        }
        //en passant case 
        else if (p->getId() == 'p' && whiteSetupEnPassant == true) {
            if (p->validCaptureEnPassant(s1, s2, gameboard) == true) {
                // left diagonal or right diagonal
                int rankChange = s2.rank - s1.rank;
                int fileChange = s2.file - s1.file;
                Position posCheck{0,0};
                if (rankChange == -1 && fileChange == 1) {
                    posCheck.file = s1.file + 1;
                    posCheck.rank = s1.rank;
                } else { // rankChange == -1 && fileChange == -1
                    posCheck.file = s1.file - 1;
                    posCheck.rank = s1.rank;
                }
                bool inCheck = p->opponentKingInCheck(s1, s2, gameboard);
                bool inCheckmate = p->opponentKingCheckmate(s1, s2, gameboard);
                bool inStalemate = p->opponentKingStalemate(s1, s2, gameboard);
                gameboard->removePiece(posCheck);
                gameboard->makeMove(p, s1, s2);
                gameboard->renderMove(s1.file, s1.rank, s2.file, s2.rank);
                moved = true;
                if (inCheck == true) {
                    cout << "White is in check." << endl;
                    if (inCheckmate == true) {
                        kingExists = false;
                        cout << "Checkmate! Black wins!" << endl;
                    }
                }
                if (inStalemate == true) {
                    inStalemate = true;
                    cout << "Stalemate!" << endl;
                }
            }
            /*
            if (p->validCaptureEnPassant(s1, s2, gameboard) == true) {
                Position left{s1.file - 1, s1.rank + 2};
                Pieces *oppPawnL = gameboard->pieceAt(left);
                if (oppPawnL != nullptr) {
                    Position oppPawnNewPos{s1.file, s1.rank + 1};
                    gameboard->removePiece(s1);
                    gameboard->makeMove(oppPawnL, left, oppPawnNewPos);
                    //show render
                }
                else {
                    Position right{s1.file + 1, s1.rank + 2};
                    Pieces *oppPawnR = gameboard->pieceAt(right);
                    //add
                }
            }*/
        }
        //regular move
        else if (p->validMoveFinal(s1, s2, gameboard) == true) {
            bool inCheck = p->opponentKingInCheck(s1, s2, gameboard);
            bool inCheckmate = p->opponentKingCheckmate(s1, s2, gameboard);
            bool inStalemate = p->opponentKingStalemate(s1, s2, gameboard);
            gameboard->makeMove(p, s1, s2); 
            moved = true;
            gameboard->renderMove(s1.file, s1.rank, s2.file, s2.rank);
            if (inCheck == true) {
                cout << "White is in check." << endl;
                if (inCheckmate == true) {
                    kingExists = false;
                    cout << "Checkmate! Black wins!" << endl;
                }
            }
            if (inStalemate == true) {
                inStalemate = true;
                cout << "Stalemate!" << endl;
            }
            if (p->getId() == 'p') {
                if (p->getFirstMove() == true) {
                    p->setFirstMove(false);
                }
            }
        }
        else {
            moved = false;
            return;
        }
    } 
    //delete stack
}

//destructor
Human::~Human() {
    delete p;
}
