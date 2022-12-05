#include <iostream>
#include <string.h>
#include <sstream>
#include "game.h"
#include "human.h"
#include "levelfour.h"
#include "levelone.h"
#include "leveltwo.h"
#include "levelthree.h"
#include "player.h"
#include "pieces.h"
#include "board.h"
#include "graphicsObserver.h"
#include "textObserver.h"
#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"

using namespace std;

//converting a square into a position struct
Position convert(string square) {
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

//creates a player
Player* create(string player) {
    if (player == "human") {
        Player *h = new Human{player};
        return h;
    } 
    else if (player == "computer1") {
        Player *one = new LevelOne{player}; 
        return one;
    } 
    else if (player == "computer2") {
        Player *two = new LevelTwo{player};
        return two;
    } 
    else if (player == "computer3") {
        Player *three = new LevelThree{player}; 
        return three;
    }
    else if (player == "computer4") {
        Player *four = new LevelFour{player};
        return four;
    }
}

int main() {

    //white wins
    int white = 0;

    //black wins
    int black = 0;

    //for tie games
    int ties = 0;

    //checks if the player has done a personalized setup move
    bool setupDone = false;
    
    while (true) {
        //creates the game board
        Board *gameboard = new Board(); 

        //checks if the game is running
        bool grunning = false;

        //checks which player goes first when the game starts
        string firstTurn = "white";

        //for the game to begin 
        Game *g = nullptr;

        //sets up text observer
        Observer *t = nullptr;
        //sets up graphics observer
        Observer *gr = nullptr;

        //sets up player white
        Player *w = nullptr;
        //sets up player black
        Player *b = nullptr;

        //stack for storing observers
        std::vector<Observer*> stack;

        if (cin.eof() || cin.fail()) {
            //deletes pointers
            delete gameboard;
            delete g;
            delete w;
            delete b;
            //deletes observers
            for (auto &ob : stack) delete ob;
            //distributes draws
            int draws = ties / 2;
            white += draws;
            black += draws;
            //converts int to string
            string w = to_string(white);
            string b = to_string(black);
            //prints final results
            cout << "Final Score:" << endl;
            cout << "White " + w << endl;
            cout << "Black " + b << endl;
            break; 
        }
        else {
            //string to input player types 
            string s;

            cin >> s;

            if (s == "game") {
                //strings to store player1 and player2 names
                string player1;
                string player2;
                cin >> player1 >> player2;
                if (((player1 == "human") || (player1 == "computer1")|| (player1 == "computer2") || (player1 == "computer3") || (player1 == "computer4")) &&
                    ((player2 == "human") || (player2 == "computer1")|| (player2 == "computer2") || (player2 == "computer3") || (player2 == "computer4"))) {
                    //creates players
                    w = create(player1); //creates white player
                    b = create(player2); //creates black player

                    //stores players names in a string
                    string p1 = w->getName();
                    string p2 = b->getName();

                    //sets up regular gameboard only if personalized setup is not done
                    if (setupDone == false) {
                        //initializes the gameboard
                        gameboard->initBoard();
                    }

                    //creates a new game 
                    g = new Game(gameboard, w, b, firstTurn); //white moves first
                    //game is running now
                    grunning = true;

                    //creates observers
                    t = new addText{gameboard}; //text observer
                    gr = new addGraphics{gameboard}; //graphics observer

                    //pushes the observers onto the stack
                    stack.push_back(t);
                    stack.push_back(gr);

                    gameboard->render(); //displays text and graphics observers

                    //if game is computer vs computer
                    if (((p1 == "computer1") || (p1 == "computer2") || (p1 == "computer3") || (p1 == "computer4")) && 
                        ((p2 == "computer1") || (p2 == "computer2") || (p2 == "computer3") || (p2 == "computer4"))) {
                            //checks if the game is not in checkmate for either player
                            while ((w->kingIsThere() != false) || (b->kingIsThere() != false)) {
                                if (cin.eof()) {
                                    break;
                                }
                                g->computerMove(gameboard, w, b);
                            }
                        setupDone == false;   
                    }
                    //if game is human vs computer
                    else if ((p1 == "human") && ((p2 == "computer1") || (p2 == "computer2") || (p2 == "computer3") || (p2 == "computer4"))) {
                        while ((w->kingIsThere() != false) || (b->kingIsThere() != false)) {
                            if (cin.eof()) {
                                break;
                            }
                            if ((g->getTurn() == "white") && (w->hasMoved() == false)) {
                                string wantsMove;
                                cin >> wantsMove;
                                if (wantsMove == "move") {
                                    g->humanMove(gameboard, w, b);
                                }
                                else if (wantsMove == "resign") {
                                    if (w->hasMoved() == false) {
                                        ++black; 
                                        cout << "Black Wins!" << endl;
                                        break;
                                    } 
                                    else {
                                        ++white;
                                        cout << "White Wins!" << endl;
                                        break;
                                    }
                                }
                                else {
                                    continue;
                                }
                            }
                            else if ((g->getTurn() == "black") && (b->hasMoved() == false)) {
                                g->computerMove(gameboard, w, b);
                            }
                        }
                        setupDone == false;
                    }
                    //if game is computer vs human
                    else if (((p1 == "computer1") || (p1 == "computer2") || (p1 == "computer3") || (p1 == "computer4")) && (p2 == "human")) {
                        while ((w->kingIsThere() != false) || (b->kingIsThere() != false)) {
                            if (cin.eof()) {
                                break;
                            }
                            if ((g->getTurn() == "white") && (w->hasMoved() == false)) {
                                g->computerMove(gameboard, w, b);
                            }
                            else if ((g->getTurn() == "black") && (b->hasMoved() == false)) {
                                string wantsMove;
                                cin >> wantsMove;
                                if (wantsMove == "move") {
                                    g->humanMove(gameboard, w, b);
                                }
                                else if (wantsMove == "resign") {
                                    if (w->hasMoved() == false) {
                                        ++black; 
                                        cout << "Black Wins!" << endl;
                                        break;
                                    } 
                                    else {
                                        ++white;
                                        cout << "White Wins!" << endl;
                                        break;
                                    }
                                }
                                else {
                                    continue;
                                }
                            }
                        }
                        setupDone == false;
                    }
                    //if game is human vs computer
                    else if ((p1 == "human") && (p2 == "human")) {
                        while ((w->kingIsThere() != false) || (b->kingIsThere() != false)) {
                            if (cin.eof()) {
                                break;
                            }
                            string wantsMove;
                            cin >> wantsMove;
                            if (wantsMove == "move") {
                                g->humanMove(gameboard, w, b);
                            }
                            else if (wantsMove == "resign") {
                                if (w->hasMoved() == false) {
                                    ++black; 
                                    cout << "Black Wins!" << endl;
                                    break;
                                } 
                                else {
                                    ++white;
                                    cout << "White Wins!" << endl;
                                    break;
                                }
                            }
                            else {
                                continue;
                            }
                        }
                        setupDone == false;
                    }
                }
                else {
                    continue;
                }
            }
            else if (s == "move") {
                g->humanMove(gameboard, w, b);
            }
            else if (s == "resign") {
                if (w->hasMoved() == false) { //if w has not moved, this means that it is w's turn so if they resign, it is b's point
                    ++black; 
                    cout << "Black Wins!" << endl;
                    setupDone == false;
                } 
                else {
                    ++white;
                    cout << "White Wins!" << endl;
                    setupDone == false;
                }
            }
            else if (s == "setup") {
                if (grunning == false) {
                    while (true) {
                        string command;
                        cin >> command;
                        if (command == "done") {
                            setupDone = true;
                            break;
                        }
                        else if (command == "+") {
                            //cout << "adding piece" << endl;
                            char piece;
                            string square;
                            cin >> piece >> square;
                            Pieces *piecePlace = createPiece(piece);
                            //converting square into a position struct
                            Position p = convert(square); 
                            //if there is an exisiting piece at that position
                            if (gameboard->pieceAt(p) != nullptr) {
                                gameboard->place(piecePlace, p); //board handles case for replacing piece
                            }
                            //if the position is a null pointer 
                            else {
                                gameboard->place(piecePlace, p);
                            }
                            //cout << "piece added" << endl;
                            gameboard->render(); //displays board
                        }
                        else if (command == "-") {
                            string square;
                            cin >> square;
                            //converting square into a position struct
                            Position p = convert(square);
                            if (gameboard->pieceAt(p) != nullptr) {
                                gameboard->removePiece(p); //board handles case for removing piece at position
                                gameboard->render(); //displays board
                            } 
                            else {
                                continue; //if position is a nullptr
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
