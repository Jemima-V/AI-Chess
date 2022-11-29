#include <iostream>
#include <string.h>
#include <sstream>
#include "game.h"
//#include "computer.h"
#include "human.h"
//#include "levelfour.h"
//#include "levelone.h"
//#include "leveltwo.h"
//#include "levelthree.h"
#include "player.h"
#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "pieces.h"
#include "queen.h"
#include "rook.h"
#include "board.h"
//#include "graphicsObserver.h"
#include "textObserver.h"
#include "observer.h"
#include "subject.h"
#include "window.h"

using namespace std;

//converting a square into a position struct
Position convert(string square) {
    char file = square[0];
    char rank = square[1];
    int f;
    int r;
    if (file == 'a') {
        f = 1;
    }
    else if (file == 'b') {
        f = 2;
    }
    else if (file == 'c') {
        f = 3;
    }
    else if (file == 'd') {
        f = 4;
    }
    else if (file == 'e') {
        f = 5;
    }
    else if (file == 'f') {
        f = 6;
    }
    else if (file == 'g') {
        f = 7;
    }
    else if (file == 'h') {
        f = 8;
    }
    rank >> r;
    Position p{f, r};
    return p;
}

//returns the Promotion piece for pawn promotion
Pieces* promo(string player, char promoChar) {
    int id;
    if (player == "white") {
        id = 1;
    } else {
        id = 2;
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

//creates a player
Player* create(string player) {
    if (player == "human") {
        Player *h = new Human{player};
        return h;
    } 
    else if (player == "computer1") {
        Player *h = new Human{player}; //
        return h;
    } 
    else if (player == "computer2") {
        Player *h = new Human{player}; //
        return h;
    } 
    else if (player == "computer3") {
        Player *h = new Human{player}; //
        return h;
    }
    else if (player == "computer4") {
        Player *h = new Human{player}; //
        return h;
    }
}

int main() {
    //creates the game board
    Board *gameboard = new Board(); 

    //initializes the gameboard
    gameboard->initBoard();

    //checks if the game is running
    bool grunning;

    //white wins
    int white;

    //black wins
    int black;

    //for tie games
    int ties;

    //string to input player types 
    string s;

    Game *g = nullptr;
    
    while (true) {
        if (cin.eof()) {
            string w = to_string(white);
            string b = to_string(black);
            cout << "Final Score:" << endl;
            cout << "White" + w << endl;
            cout << "Black" + b << endl;
            break; 
        }
        else {
            cin >> s;
            Player *w = nullptr;
            Player *b = nullptr;
            if (s == "game") {
                string player1;
                string player2;
                cin >> player1 >> player2;
                Player *w = create(player1);
                Player *b = create(player2);
                //creates a new game 
                Game *g = new Game(gameboard, w, b, "white");
            }
            else if (s == "resign") {
                if (w->hasMoved() == false) { //if w has not moved, this means that it is w's turn so if they resign, it is b's point
                    ++black; 
                    cout << "Black Wins!" << endl;
                } 
                else {
                    ++white;
                    cout << "White Wins!" << endl;
                }
            }
            else if (s == "move") {
                string square1;
                string square2;
                char promotionChar;
                cin >> square1 >> square2 >> promotionChar;
                Position s1 = convert(square1);
                Position s2 = convert(square2);
                if ((gameboard->pieceAt(s1) != nullptr) && 
                    ((s1.file >= 1) && (s1.file <= 8)) && 
                    ((s1.rank >= 1) && (s1.rank <= 8)) && 
                    ((s2.file >= 1) && (s2.file <= 8)) &&
                    ((s2.rank >= 1) && (s2.rank <= 8)) && 
                    (s1.rank != s2.rank) && (s1.file != s2.file)) {
                    Pieces *p = gameboard->pieceAt(s1);
                    if (p->getOwner() == white) {
                        if (((s1.file == 5) && (s1.rank == 1)) &&
                            ((s2.file == 7) && (s2.rank == 1))) {
                                if (p->isValidCastling(s1, s2, gameboard, p) == true) {
                                    gameboard->makeMove(p, s1, s2); 
                                    Position rpos{8, 1};
                                    Position rnew{6, 1};
                                    Pieces *rook = gameboard->pieceAt(rpos);
                                    gameboard->makeMove(rook, rpos, rnew);
                                    if (p->opponentKingInCheck(s1, s2, gameboard) == true) {
                                        cout << "Black is in check." << endl;
                                        if (p->opponentKingCheckmate(s1, s2, gameboard) == true) {
                                            cout << "Checkmate! White wins!" << endl;
                                        }
                                    }
                                }
                        }
                        else if (((s1.file == 5) && (s1.rank == 1)) &&
                                ((s2.file == 3) && (s2.rank == 1))) {
                                    if (p->isValidCastling(s1, s2, gameboard, p) == true) {
                                        gameboard->makeMove(p, s1, s2); 
                                        Position rpos{1, 1};
                                        Position rnew{4, 1};
                                        Pieces *rook = gameboard->pieceAt(rpos);
                                        gameboard->makeMove(rook, rpos, rnew);
                                        if (p->opponentKingInCheck(s1, s2, gameboard) == true) {
                                            cout << "Black is in check." << endl;
                                            if (p->opponentKingCheckmate(s1, s2, gameboard) == true) {
                                                cout << "Checkmate! White wins!" << endl;
                                            }
                                        }
                                    }
                        }
                        else if (p->getId() == 'P') {
                            if (s1.rank == 7) {
                                if (p->validMove(s1, s2, gameboard) == true) {
                                    gameboard->makeMove(p, s1, s2); 
                                    Pieces *promoPiece = promo("white", promotionChar);
                                    gameboard->place(promoPiece, s2); //replace pawn with new promoPiece
                                    if (p->opponentKingInCheck(s1, s2, gameboard) == true) {
                                        cout << "Black is in check." << endl;
                                        if (p->opponentKingCheckmate(s1, s2, gameboard) == true) {
                                            cout << "Checkmate! White wins!" << endl;
                                        }
                                    }
                                }      
                            }
                        }
                        else if (p->validMove(s1, s2, gameboard) == true) {
                            gameboard->makeMove(p, s1, s2); 
                            if (p->opponentKingInCheck(s1, s2, gameboard) == true) {
                                cout << "Black is in check." << endl;
                                if (p->opponentKingCheckmate(s1, s2, gameboard) == true) {
                                    cout << "Checkmate! White wins!" << endl;
                                }
                            }
                        }
                        else {
                            continue;
                        }
                    }
                    else if (p->getOwner() == black) {
                        if (((s1.file == 5) && (s1.rank == 8)) &&
                            ((s2.file == 7) && (s2.rank == 8))) {
                                if (p->isValidCastling(s1, s2, gameboard, p) == true) {
                                    gameboard->makeMove(p, s1, s2); 
                                    Position rpos{8, 8};
                                    Position rnew{6, 8};
                                    Pieces *rook = gameboard->pieceAt(rpos);
                                    gameboard->makeMove(rook, rpos, rnew);
                                    if (p->opponentKingInCheck(s1, s2, gameboard) == true) {
                                        cout << "White is in check." << endl;
                                        if (p->opponentKingCheckmate(s1, s2, gameboard) == true) {
                                            cout << "Checkmate! Black wins!" << endl;
                                        }
                                    }
                                }
                        }
                        else if (((s1.file == 5) && (s1.rank == 8)) &&
                                ((s2.file == 3) && (s2.rank == 8))) {
                                    if (p->isValidCastling(s1, s2, gameboard, p) == true) {
                                        gameboard->makeMove(p, s1, s2); 
                                        Position rpos{1, 8};
                                        Position rnew{4, 8};
                                        Pieces *rook = gameboard->pieceAt(rpos);
                                        gameboard->makeMove(rook, rpos, rnew);
                                        if (p->opponentKingInCheck(s1, s2, gameboard) == true) {
                                            cout << "White is in check." << endl;
                                            if (p->opponentKingCheckmate(s1, s2, gameboard) == true) {
                                                cout << "Checkmate! Black wins!" << endl;
                                            }
                                        }
                                    }
                        }
                        else if (p->getId() == 'p') {
                            if (s1.rank == 2) {
                                if (p->validMove(s1, s2, gameboard) == true) {
                                    gameboard->makeMove(p, s1, s2); 
                                    Pieces *promoPiece = promo("black", promotionChar);
                                    gameboard->place(promoPiece, s2); //replace pawn with new promoPiece
                                    if (p->opponentKingInCheck(s1, s2, gameboard) == true) {
                                        cout << "White is in check." << endl;
                                        if (p->opponentKingCheckmate(s1, s2, gameboard) == true) {
                                            cout << "Checkmate! Black wins!" << endl;
                                        }
                                    }
                                }      
                            }
                        }
                        else if (p->validMove(s1, s2, gameboard) == true) {
                            gameboard->makeMove(p, s1, s2); 
                            if (p->opponentKingInCheck(s1, s2, gameboard) == true) {
                                cout << "White is in check." << endl;
                                if (p->opponentKingCheckmate(s1, s2, gameboard) == true) {
                                    cout << "Checkmate! Black wins!" << endl;
                                }
                            }
                        }
                        else {
                            continue;
                        }
                    }
                    else {
                        continue;
                    }
                } 
                else {
                    continue;
                }
            }
            else if (s == "setup") {
                if (grunning == false) {
                    string command;
                    while (true) {
                        cin >> command;
                        if (command == "done") {
                            break;
                        }
                        else if (command == "+") {
                            char piece;
                            string square;
                            cin >> piece >> square;
                            Pieces *piecePlace = nullptr;
                            if (piece == 'P') {
                                piecePlace = new Pawn{1, false, 'P', true}; //
                            }
                            else if (piece == 'K') {
                                piecePlace = new King{1, false, 'K'}; //
                            }
                            else if (piece == 'Q') {
                                piecePlace = new Queen{1, false, 'Q'}; //
                            }
                            else if (piece == 'B') {
                                piecePlace = new Bishop{1, false, 'B'}; //
                            }
                            else if (piece == 'R') {
                                piecePlace = new Rook{1, false, 'R'}; //
                            }
                            else if (piece == 'N') {
                                piecePlace = new Knight{1, false, 'P'}; //
                            }
                            //converting square into a position struct
                            Position p = convert(square); 
                            //if there is an exisiting piece at that position
                            if (gameboard->pieceAt(p) != nullptr) {
                                gameboard->place(piecePlace, p); //board handles case for replacing 
                            }
                            //if the position is a null pointer 
                            else {
                                gameboard->place(piecePlace, p);
                            }
                            //gameboard->display(); // how to display board
                        }
                        else if (command == "-") {
                            string square;
                            cin >> square;
                            //converting square into a position struct
                            Position p = convert(square);
                            if (gameboard->pieceAt(p) != nullptr) {
                                gameboard->removePiece(p); //board handles case for removing piece at position
                                //gameboard->display();
                            } 
                            else {
                                continue;
                            }
                        }
                        else if (command == "=") {
                            string colour;
                            cin >> colour;
                            //setPlayerTurn(colour); //implement this function in player class
                        } 
                        else {
                            continue; //continues with command loop if any command is misspelled
                        }
                    }
                }
            }
            else {
                continue; //continues with command loop if any command is misspelled 
            }
        }
    }
}

//delete pointers
