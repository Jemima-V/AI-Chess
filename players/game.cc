#include <iostream>
#include <string.h>
#include <sstream>
#include "game.h"
#include "player.h"
#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "pieces.h"
#include "queen.h"
#include "rook.h"
#include "board.h"

using namespace std;

//constructor 
Game::Game(Board *gameBoard, Player *white, Player *black, string turn) : gameBoard{gameBoard}, white{white},
                                                                          black{black}, turn{turn} {}

//gets the players turn
string Game::getTurn() {
    return turn;
}

//sets the players turn
void Game::setTurn(string t) {
    turn = t;
}

//converting a square into a position struct
Position Game::convert(string square) {
    char file = square[0];
    char rank = square[1];
    int f;
    int r;
    if (file == 'a') {
        f = 0;
    }
    else if (file == 'b') {
        f = 1;
    }
    else if (file == 'c') {
        f = 2;
    }
    else if (file == 'd') {
        f = 3;
    }
    else if (file == 'e') {
        f = 4;
    }
    else if (file == 'f') {
        f = 5;
    }
    else if (file == 'g') {
        f = 6;
    }
    else if (file == 'h') {
        f = 7;
    }
    r = rank - '0';
    --r;
    Position p{f, r};
    return p;
}

//creates a human move
void Game::humanMove(Board *gameboard, Player *w, Player *b) {
    string square1;
    string square2;
    cin >> square1 >> square2;
    //converts square into a position struct 
    Position s1 = convert(square1);
    Position s2 = convert(square2);
    //checks if there is a piece at square 1
    if ((gameboard->pieceAt(s1) != nullptr) && 
        ((s1.file >= 0) && (s1.file <= 7)) && //checks if s1 file is within the bounds 1-8 
        ((s1.rank >= 0) && (s1.rank <= 7)) && //checks if s1 rank is within the bounds 1-8 
        ((s2.file >= 0) && (s2.file <= 7)) && //checks if s2 file is within the bounds 1-8
        ((s2.rank >= 0) && (s2.rank <= 7)) && //checks if s2 rank is within the bounds 1-8
        //checks if s1 does not equal to s2
        (((s1.rank != s2.rank) && (s1.file != s2.file)) || 
        ((s1.rank != s2.rank) && (s1.file == s2.file)) ||
        ((s1.rank == s2.rank) && (s1.file != s2.file)))) { 
        Pieces *p = gameboard->pieceAt(s1);
        //white
        if (p->getOwner() == 1) {
            if ((getTurn() == "white") && (w->hasMoved() == false)) {
                w->playerMove(s1, s2, gameboard, p, "white");
                if (w->hasMoved() == false) {
                    setTurn("white");
                }
                else {
                    setTurn("black");
                    b->setMoved(false);
                }
            }
        } 
        //black
        else if (p->getOwner() == 2) { 
            if ((getTurn() == "black") && (b->hasMoved() == false)) {
                b->playerMove(s1, s2, gameboard, p, "black");
                if (b->hasMoved() == false) {
                    setTurn("black");
                }
                else {
                    setTurn("white");
                    w->setMoved(false);
                }
            }
        } 
    } 
}

void Game::computerMove(Board *gameboard, Player *w, Player *b) {
    Position s1;
    Position s2;
    Pieces *p = nullptr;
    //checks if it is white's turn and if they have already moved
    if ((getTurn() == "white") && (w->hasMoved() == false)) {
        //makes move
        w->playerMove(s1, s2, gameboard, p, "white");
        //if valid move doesn't happen, it is still white's turn
        if (w->hasMoved() == false) {
            setTurn("white");
        }
        //if valid move does happen, it is black's turn
        else {
            setTurn("black");
            b->setMoved(false);
        }
    }
    //checks if it is black's turn and if they have already moved
    else if ((getTurn() == "black") && (b->hasMoved() == false)) {
        //makes move
        b->playerMove(s1, s2, gameboard, p, "black");
        //if valid move doesn't happen, it is still blacks's turn
        if (b->hasMoved() == false) {
            setTurn("black");
        }
        //if valid move does happen, it is white's turn
        else {
            setTurn("white");
            w->setMoved(false);
        }
    }
}

//destructor
Game::~Game() {
    delete gameBoard;
    delete white;
    delete black;
}
