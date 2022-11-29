#include <iostream>
#include <string.h>
#include <sstream>
#include "game.h"
#include "computer.h"
#include "human.h"
#include "levelfour.h"
#include "levelone.h"
#include "leveltwo.h"
#include "levelthree.h"
#include "player.h"
#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "pieces.h"
#include "queen.h"
#include "rook.h"
#include "board.h"
#include "graphicsObserver.h"
#include "textObserver.h"
#include "observer.h"
#include "subject.h"

using namespace std;

//converting a square into a position struct
Position convert(string square) {
    //length of the string square
    int n = square.length();
    //new char array
    char arr[n + 1];
    //copying individual chars from the string into the char arr
    strcpy(arr, s.c_str); // dont know if we are allowed to use this 
    char file;
    char rank;
    //extracting the file and rank
    for (int i = 0; i < n; ++i) {
        if (i == 0) {
            file = arr[i];
        }
        else if (i == 1) {
            rank = arr[i];
        }
    }
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
    return new Position{f, r};
}

//returns the Promotion piece for pawn promotion
Pieces promo(string player, char promoChar) {
    if (promoChar == 'Q') {
        if (player == "white") {
            return new Queen{player, false, 'Q'};
        }
        else {
            return new Queen{player, false, 'q'};
        }
    }
    else if (promoChar == 'R') {
        if (player == "white") {
            return new Rook{player, false, 'R'};
        }
        else {
            return new Rook{player, false, 'r'};
        }
    }
    else if (promoChar == 'K') {
        if (player == "white") {
            return new Knight{player, false, 'K'};
        }
        else {
            return new Knight{player, false, 'k'};
        }
    }
    else if (promoChar == 'B') {
        if (player == "white") {
            return new Bishop{player, false, 'B'};
        }
        else {
            return new Bishop{player, false, 'b'};
        }
    }
    //try catch?
}

//creates a player
Player* create(string player) {
    if (player == "human") {
        return new Human(player);
    } 
    else if (player == "computer1") {
        return new LevelOne(player);
    } 
    else if (player == "computer2") {
        return new LevelTwo(player);
    } 
    else if (player == "computer3") {
        return new LevelThree(player);
    }
    else if (player == "computer4") {
        return new LevelFour(player);
    }
}

int main() {
    //creates the game board
    Board *gameboard; 

    //initializes the gameboard
    gameboard.initBoard();

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
                if (w.hasMoved() == false) { //if w has not moved, this means that it is w's turn so if they resign, it is b's point
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
                if ((pieceAt(s1) != nullptr) && 
                    ((s1.file >= 1) && (s1.file <= 8)) && 
                    ((s1.rank >= 1) && (s1.rank <= 8)) && 
                    ((s2.file >= 1) && (s2.file <= 8)) &&
                    ((s2.rank >= 1) && (s2.rank <= 8)) && 
                    (s1.rank != s2.rank) && (s1.file != s2.file)) {
                    Pieces *p = pieceAt(s1);
                    if (p.getOwner() == white) {
                        if (((s1.file == 5) && (s1.rank == 1)) &&
                            ((s2.file == 7) && (s2.rank == 1))) {
                                if (p->isValidCastling(p, s1, s2) == true) {
                                    makeMove(p, s1, s2); 
                                    Position rpos = new Position{8, 1};
                                    Position rnew = new Position{6, 1};
                                    Pieces *rook = pieceAt(rpos);
                                    makeMove(rook, rpos, rnew);
                                    if (opponentKingInCheck(s1, s2, gameboard) == true) {
                                        cout << "Black is in check." << endl;
                                        if (opponentKingCheckmate(s1, s2, gameboard) == true) {
                                            cout << "Checkmate! White wins!" << endl;
                                        }
                                    }
                                }
                        }
                        else if (((s1.file == 5) && (s1.rank == 1)) &&
                                ((s2.file == 3) && (s2.rank == 1))) {
                                    if (p->isValidCastling(p, s1, s2) == true) {
                                        makeMove(p, s1, s2); 
                                        Position rpos = new Position{1, 1};
                                        Position rnew = new Position{4, 1};
                                        Pieces *rook = pieceAt(rpos);
                                        makeMove(rook, rpos, rnew);
                                        if (opponentKingInCheck(s1, s2, gameboard) == true) {
                                            cout << "Black is in check." << endl;
                                            if (opponentKingCheckmate(s1, s2, gameboard) == true) {
                                                cout << "Checkmate! White wins!" << endl;
                                            }
                                        }
                                    }
                        }
                        else if (p->getId() == 'P') {
                            if (s1.rank == 7) {
                                if (p->validMove(s1, s2, gameboard) == true) {
                                    makeMove(p, s1, s2); 
                                    Pieces promoPiece = promo("white", promotionChar);
                                    place(promoPiece, s2); //replace pawn with new promoPiece
                                    if (opponentKingInCheck(s1, s2, gameboard) == true) {
                                        cout << "Black is in check." << endl;
                                        if (opponentKingCheckmate(s1, s2, gameboard) == true) {
                                            cout << "Checkmate! White wins!" << endl;
                                        }
                                    }
                                }      
                            }
                        }
                        else if (p->validMove(s1, s2, gameboard) == true) {
                            makeMove(p, s1, s2); 
                            if (opponentKingInCheck(s1, s2, gameboard) == true) {
                                cout << "Black is in check." << endl;
                                if (opponentKingCheckmate(s1, s2, gameboard) == true) {
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
                                if (p->isValidCastling(p, s1, s2) == true) {
                                    makeMove(p, s1, s2); 
                                    Position rpos = new Position{8, 8};
                                    Position rnew = new Position{6, 8};
                                    Pieces *rook = pieceAt(rpos);
                                    makeMove(rook, rpos, rnew);
                                    if (opponentKingInCheck(s1, s2, gameboard) == true) {
                                        cout << "White is in check." << endl;
                                        if (opponentKingCheckmate(s1, s2, gameboard) == true) {
                                            cout << "Checkmate! Black wins!" << endl;
                                        }
                                    }
                                }
                        }
                        else if (((s1.file == 5) && (s1.rank == 8)) &&
                                ((s2.file == 3) && (s2.rank == 8))) {
                                    if (p->isValidCastling(p, s1, s2) == true) {
                                        makeMove(p, s1, s2); 
                                        Position rpos = new Position{1, 8};
                                        Position rnew = new Position{4, 8};
                                        Pieces *rook = pieceAt(rpos);
                                        makeMove(rook, rpos, rnew);
                                        if (opponentKingInCheck(s1, s2, gameboard) == true) {
                                            cout << "White is in check." << endl;
                                            if (opponentKingCheckmate(s1, s2, gameboard) == true) {
                                                cout << "Checkmate! Black wins!" << endl;
                                            }
                                        }
                                    }
                        }
                        else if (p->getId() == 'p') {
                            if (s1.rank == 2) {
                                if (p->validMove(s1, s2, gameboard) == true) {
                                    makeMove(p, s1, s2); 
                                    Pieces promoPiece = promo("black", promotionChar);
                                    place(promoPiece, s2); //replace pawn with new promoPiece
                                    if (opponentKingInCheck(s1, s2, gameboard) == true) {
                                        cout << "White is in check." << endl;
                                        if (opponentKingCheckmate(s1, s2, gameboard) == true) {
                                            cout << "Checkmate! Black wins!" << endl;
                                        }
                                    }
                                }      
                            }
                        }
                        else if (p->validMove(s1, s2, gameboard) == true) {
                            makeMove(p, s1, s2); 
                            if (opponentKingInCheck(s1, s2, gameboard) == true) {
                                cout << "White is in check." << endl;
                                if (opponentKingCheckmate(s1, s2, gameboard) == true) {
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
                            string piece;
                            string square;
                            cin >> piece >> square;
                            //converting square into a position struct
                            Position p = convert(square); 
                            //if there is an exisiting piece at that position
                            if (gameboard.pieceAt(p) == true) {
                                place(piece, p); //board handles case for replacing 
                            }
                            //if the position is a null pointer 
                            else {
                                place(piece, p);
                            }
                            gameboard.display(); // how to display board
                        }
                        else if (command == "-") {
                            string square;
                            cin >> square;
                            //converting square into a position struct
                            Position p = convert(square);
                            if (gameboard.pieceAt(p) == true) {
                                removePiece(p); //board handles case for removing piece at position
                                gameboard.display();
                            } 
                            else {
                                continue;
                            }
                        }
                        else if (command == "=") {
                            string colour;
                            cin >> colour;
                            setPlayerTurn(colour); //implement this function in player class
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
