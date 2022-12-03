#include <iostream>
#include <string.h>
#include <sstream>
#include "game.h"
//#include "computer.h"
#include "human.h"
//#include "levelfour.h"
#include "levelone.h"
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
#include "graphicsObserver.h"
#include "textObserver.h"
#include "observer.h"
#include "subject.h"
#include "window.h"

using namespace std;

//creating a piece 
Pieces* createPiece(char piece) {
    if (piece == 'P') {
        return new Pawn{1, false, 'P', true}; //
    }
    else if (piece == 'K') {
        return new King{1, false, 'K'}; //
    }
    else if (piece == 'Q') {
        return new Queen{1, false, 'Q'}; //
    }
    else if (piece == 'B') {
        return new Bishop{1, false, 'B'}; //
    }
    else if (piece == 'R') {
        return new Rook{1, false, 'R'}; //
    }
    else if (piece == 'N') {
        return new Knight{1, false, 'N'}; //
    }
    else if (piece == 'p') {
        return new Pawn{2, false, 'p', true}; //
    }
    else if (piece == 'k') {
        return new King{2, false, 'k'}; //
    }
    else if (piece == 'q') {
        return new Queen{2, false, 'q'}; //
    }
    else if (piece == 'b') {
        return new Bishop{2, false, 'b'}; //
    }
    else if (piece == 'r') {
        return new Rook{2, false, 'r'}; //
    }
    else if (piece == 'n') {
        return new Knight{2, false, 'n'}; //
    }
}

//converting a square into a position struct
Position convert(string square) {
    char file = square[0];
    char rank = square[1];
    //cout << file << endl << rank << endl;
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
    //cout << p.file << endl << p.rank << endl;
    return p;
}

//creates a player
Player* create(string player) {
    //cout << "here" << endl;
    if (player == "human") {
        Player *h = new Human{player};
        //cout << "end" << endl;
        return h;
    } 
    else if (player == "computer1") {
        Player *one = new LevelOne{player}; //
        return one;
    } 
    else if (player == "computer2") {
        Player *two = new Human{player}; //
        return two;
    } 
    else if (player == "computer3") {
        Player *three = new Human{player}; //
        return three;
    }
    else if (player == "computer4") {
        Player *four = new Human{player}; //
        return four;
    }
}

int main() {
    //creates the game board
    Board *gameboard = new Board(); 

    //initializes the gameboard
    gameboard->initBoard();

    //checks if the game is running
    bool grunning = false;

    //white wins
    int white = 0;

    //black wins
    int black = 0;

    //for tie games
    int ties = 0;

    //string to input player types 
    //string s;

    //colour that goes first when the game starts
    string firstTurn = "white";

    Game *g = nullptr;

    Observer *t = nullptr;
    //Observer *gr = nullptr;

    Player *w = nullptr;
    Player *b = nullptr;

    std::vector<Observer*> stack;
    
    while (true) {
        if (cin.eof() || cin.fail()) {
            //cout << "test" << endl;
            int draws = ties / 2;
            white += draws;
            black += draws;
            string w = to_string(white);
            string b = to_string(black);
            cout << "Final Score:" << endl;
            cout << "White " + w << endl;
            cout << "Black " + b << endl;
            break; 
        }
        else {
            //string to input player types 
            string s;
            cin >> s;
            //cout << s << endl;
            if (s == "game") {
                string player1;
                string player2;
                cin >> player1 >> player2;
                //cout << "creating second set of players" << endl;
                w = create(player1); //creates white player
                b = create(player2); //creates black player
                string p1 = w->getName();
                string p2 = b->getName();
                cout << p1 << endl;
                cout << p2 << endl;
                //creates a new game 
                g = new Game(gameboard, w, b, firstTurn); //white moves first
                t = new addText{gameboard}; //text observer
                //gr = new addGraphics{gameboard}; //graphics observer
                stack.push_back(t);
                //stack.push_back(gr);
                gameboard->render(); //displays text and graphics observers 
                if (((p1 == "computer1") || (p1 == "computer2") || (p1 == "computer3") || (p1 == "computer4")) && 
                    ((p2 == "computer1") || (p2 == "computer2") || (p2 == "computer3") || (p2 == "computer4"))) {
                        //cout << p1 << endl;
                        //cout << p2 << endl;
                        cout << "comes to computer computer case" << endl;
                        while ((w->kingIsThere() != false) || (b->kingIsThere() != false)) {
                            cout << "comes in while" << endl;
                            Position s1;
                            Position s2;
                            Pieces *p = nullptr;
                            if ((g->getTurn() == "white") && (w->hasMoved() == false)) {
                                cout << "before playerMove" << endl;
                                w->playerMove(s1, s2, gameboard, p, "white");
                                cout << "after playerMove" << endl;
                                if (w->hasMoved() == false) {
                                    g->setTurn("white");
                                }
                                else {
                                    g->setTurn("black");
                                    b->setMoved(false);
                                }
                            }
                            else if ((g->getTurn() == "black") && (b->hasMoved() == false)) {
                                b->playerMove(s1, s2, gameboard, p, "black");
                                if (b->hasMoved() == false) {
                                    g->setTurn("black");
                                }
                                else {
                                    g->setTurn("white");
                                    w->setMoved(false);
                                }
                            }
                        }
                }
                else if ((p1 == "human") && ((p2 == "computer1") || (p2 == "computer2") || (p2 == "computer3") || (p2 == "computer4"))) {
                    continue; //add more
                }
                else if (((p1 == "computer1") || (p1 == "computer2") || (p1 == "computer3") || (p1 == "computer4")) && (p2 == "human")) {
                    continue; //add more
                }
                else if ((p1 == "human") && (p2 == "human")) {
                    continue;
                }
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
                cin >> square1 >> square2;
                //converts square into a position struct 
                Position s1 = convert(square1);
                Position s2 = convert(square2);
                cout << s1.file << "   ";
                cout << s1.rank << endl;
                cout << s2.file << "   ";
                cout << s2.rank << endl;
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
                    //cout << "comes in 1" << endl;
                    if (p->getOwner() == 1) {
                        //cout << "comes in 2" << endl;
                        if ((g->getTurn() == "white") && (w->hasMoved() == false)) { //while loop?
                            cout << "comes in 3" << endl;
                            w->playerMove(s1, s2, gameboard, p, "white");
                            //cout << "here" << endl;
                            if (w->hasMoved() == false) {
                                g->setTurn("white");
                                cout << "false" << endl;
                            }
                            else {
                                g->setTurn("black");
                                b->setMoved(false);
                                //cout << "true" << endl;
                            }
                        }
                        else {
                            continue;
                        }
                    } 
                    //black
                    else if (p->getOwner() == 2) { //while loop?
                        if ((g->getTurn() == "black") && (b->hasMoved() == false)) {
                            b->playerMove(s1, s2, gameboard, p, "black");
                            if (b->hasMoved() == false) {
                                g->setTurn("black");
                            }
                            else {
                                g->setTurn("white");
                                w->setMoved(false);
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
                            Pieces *piecePlace = createPiece(piece);
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
                            gameboard->render(); // how to display board
                        }
                        else if (command == "-") {
                            string square;
                            cin >> square;
                            //converting square into a position struct
                            Position p = convert(square);
                            if (gameboard->pieceAt(p) != nullptr) {
                                gameboard->removePiece(p); //board handles case for removing piece at position
                                gameboard->render(); // how to display board
                            } 
                            else {
                                continue;
                            }
                        }
                        else if (command == "=") {
                            string colour;
                            cin >> colour;
                            firstTurn = colour; 
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
    return 0;
}

//delete pointers
