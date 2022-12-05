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

void Human::playerMove(Position s1, Position s2, Board *gameboard, Pieces *p, string turn) {
    //white moves
    if (turn == "white") {
        //castling case 1
        if (((s1.file == 4) && (s1.rank == 0)) &&
            ((s2.file == 6) && (s2.rank == 0))) {
                if (p->isValidCastling(s1, s2, gameboard) == true) {
                    if (p->opponentKingInCheck(s1, s2, gameboard) == true) {
                        cout << "Black is in check." << endl;
                        if (p->opponentKingCheckmate(s1, s2, gameboard) == true) {
                            cout << "Checkmate! White wins!" << endl;
                        }
                    }
                    gameboard->makeMove(p, s1, s2); 
                    Position rpos{7, 0};
                    Position rnew{5, 0};
                    Pieces *rook = gameboard->pieceAt(rpos);
                    gameboard->makeMove(rook, rpos, rnew);
                    p->setMoved(true);
                    rook->setMoved(true);
                    moved = true;
                    gameboard->renderMove(s1.rank, s1.file, s2.rank, s2.file);
                }
        }
        //castling case 2
        else if (((s1.file == 4) && (s1.rank == 0)) &&
                ((s2.file == 2) && (s2.rank == 0))) {
                    if (p->isValidCastling(s1, s2, gameboard) == true) {
                        if (p->opponentKingInCheck(s1, s2, gameboard) == true) {
                            cout << "Black is in check." << endl;
                            if (p->opponentKingCheckmate(s1, s2, gameboard) == true) {
                                cout << "Checkmate! White wins!" << endl;
                            }
                        }
                        gameboard->makeMove(p, s1, s2); 
                        Position rpos{0, 0};
                        Position rnew{3, 0};
                        Pieces *rook = gameboard->pieceAt(rpos);
                        gameboard->makeMove(rook, rpos, rnew);
                        p->setMoved(true);
                        rook->setMoved(true);
                        moved = true;
                        gameboard->renderMove(s1.rank, s1.file, s2.rank, s2.file);
                    }
        }
        //pawn promotion case
        else if ((p->getId() == 'P') && (s1.rank == 6)) {
            char promotionChar;
            cin >> promotionChar; 
            if (p->validMoveFinal(s1, s2, gameboard) == true) {
                if (p->opponentKingInCheck(s1, s2, gameboard) == true) {
                    cout << "Black is in check." << endl;
                    if (p->opponentKingCheckmate(s1, s2, gameboard) == true) {
                        cout << "Checkmate! White wins!" << endl;
                    }
                }
                gameboard->makeMove(p, s1, s2); 
                Pieces *promoPiece = promo("white", promotionChar);
                gameboard->place(promoPiece, s2); //replace pawn with new promoPiece
                moved = true;
                gameboard->renderMove(s1.rank, s1.file, s2.rank, s2.file);
                if (p->getFirstMove() == true) {
                    p->setFirstMove(false);
                }
            }      
        }
        //en passant case 
        else if ((p->getId() == 'P') && (s1.rank == 2) && (s2.rank == 4) && (p->getFirstMove() == true)) {
            if (p->potentialSetupCaptureEnPassant(s1, s2, gameboard) == true) {
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
                }
            }
        }
        //regular move
        else if (p->validMoveFinal(s1, s2, gameboard) == true) {
            if (p->opponentKingInCheck(s1, s2, gameboard) == true) {
                cout << "Black is in check." << endl;
                if (p->opponentKingCheckmate(s1, s2, gameboard) == true) {
                    cout << "Checkmate! White wins!" << endl;
                }
            }
            gameboard->makeMove(p, s1, s2); 
            moved = true;
            gameboard->renderMove(s1.rank, s1.file, s2.rank, s2.file);
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
        //castling case 1
        if (((s1.file == 4) && (s1.rank == 7)) &&
            ((s2.file == 6) && (s2.rank == 7))) {
                if (p->isValidCastling(s1, s2, gameboard) == true) {
                    if (p->opponentKingInCheck(s1, s2, gameboard) == true) {
                        cout << "White is in check." << endl;
                        if (p->opponentKingCheckmate(s1, s2, gameboard) == true) {
                            cout << "Checkmate! Black wins!" << endl;
                        }
                    }
                    gameboard->makeMove(p, s1, s2); 
                    Position rpos{7, 7};
                    Position rnew{5, 7};
                    Pieces *rook = gameboard->pieceAt(rpos);
                    gameboard->makeMove(rook, rpos, rnew);
                    p->setMoved(true);
                    rook->setMoved(true);
                    moved = true;
                    gameboard->renderMove(s1.rank, s1.file, s2.rank, s2.file);
                }
        }
        //castling case 2
        else if (((s1.file == 4) && (s1.rank == 7)) &&
                ((s2.file == 2) && (s2.rank == 7))) {
                    if (p->isValidCastling(s1, s2, gameboard) == true) {
                        if (p->opponentKingInCheck(s1, s2, gameboard) == true) {
                            cout << "White is in check." << endl;
                            if (p->opponentKingCheckmate(s1, s2, gameboard) == true) {
                                cout << "Checkmate! Black wins!" << endl;
                            }
                        }
                        gameboard->makeMove(p, s1, s2); 
                        Position rpos{0, 7};
                        Position rnew{3, 7};
                        Pieces *rook = gameboard->pieceAt(rpos);
                        gameboard->makeMove(rook, rpos, rnew);
                        p->setMoved(true);
                        rook->setMoved(true);
                        moved = true;
                        gameboard->renderMove(s1.rank, s1.file, s2.rank, s2.file);
                    }
        }
        //pawn promotion case
        else if ((p->getId() == 'p') && (s1.rank == 1)) {
            char promotionChar;
            cin >> promotionChar;
            if (p->validMoveFinal(s1, s2, gameboard) == true) {
                if (p->opponentKingInCheck(s1, s2, gameboard) == true) {
                    cout << "White is in check." << endl;
                    if (p->opponentKingCheckmate(s1, s2, gameboard) == true) {
                        cout << "Checkmate! Black wins!" << endl;
                    }
                }
                gameboard->makeMove(p, s1, s2); 
                Pieces *promoPiece = promo("black", promotionChar);
                gameboard->place(promoPiece, s2); //replace pawn with new promoPiece
                moved = true;
                gameboard->renderMove(s1.rank, s1.file, s2.rank, s2.file);
                if (p->getFirstMove() == true) {
                    p->setFirstMove(false);
                }
            }      
        }
        //regular move
        else if (p->validMoveFinal(s1, s2, gameboard) == true) {
            if (p->opponentKingInCheck(s1, s2, gameboard) == true) {
                cout << "White is in check." << endl;
                if (p->opponentKingCheckmate(s1, s2, gameboard) == true) {
                    cout << "Checkmate! Black wins!" << endl;
                }
            }
            gameboard->makeMove(p, s1, s2); 
            moved = true;
            gameboard->renderMove(s1.rank, s1.file, s2.rank, s2.file);
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
