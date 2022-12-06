#include <iostream>
#include <string.h>
#include <sstream>
#include "game.h"
#include "player.h"
#include "board.h"
#include "human.h"
#include "levelone.h"
#include "leveltwo.h"
#include "levelthree.h"
#include "levelfour.h"
#include "textObserver.h"
#include "graphicsObserver.h"

using namespace std;

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

//creates a player
Player* Game::create(string player) {
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

//constructor 
Game::Game() {}

//gets the players turn
string Game::getTurn() {
    return turn;
}

//sets the players turn
void Game::setTurn(string t) {
    turn = t;
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

//starts a game
void Game::startGame(string player1, string player2, Board *gameboard) {

    if (((player1 == "human") || (player1 == "computer1")|| (player1 == "computer2") || (player1 == "computer3") || (player1 == "computer4")) &&
        ((player2 == "human") || (player2 == "computer1")|| (player2 == "computer2") || (player2 == "computer3") || (player2 == "computer4"))) {

        //creates players
        w = create(player1); //creates white player
        b = create(player2); //creates black player

        //stores players names in a string
        string p1 = w->getName();
        string p2 = b->getName();

        //sets up regular gameboard only if personalized setup is not done
        if (isSetup == false) {
            //initializes the gameboard
            gameboard->initBoard();
        }

        gameboard->render(); //displays text and graphics observers

        //creates a new game 
        turn = gameboard->getFirstTurn();

        //game is running now
        grunning = true;

        //if game is computer vs computer
        if (((p1 == "computer1") || (p1 == "computer2") || (p1 == "computer3") || (p1 == "computer4")) && 
            ((p2 == "computer1") || (p2 == "computer2") || (p2 == "computer3") || (p2 == "computer4"))) {
                //checks if the game is not in checkmate for either player
                while ((w->kingIsThere() != false) || (b->kingIsThere() != false)) {
                    if (cin.eof()) {
                        break;
                    }
                    computerMove(gameboard, w, b);
                }
            gameboard->setSetupDone(false);   
        }
        //if game is human vs computer
        else if ((p1 == "human") && ((p2 == "computer1") || (p2 == "computer2") || (p2 == "computer3") || (p2 == "computer4"))) {
            while ((w->kingIsThere() != false) || (b->kingIsThere() != false)) {
                if (cin.eof()) {
                    break;
                }
                if ((getTurn() == "white") && (w->hasMoved() == false)) {
                    string wantsMove;
                    cin >> wantsMove;
                    if (wantsMove == "move") {
                        humanMove(gameboard, w, b);
                    }
                    else if (wantsMove == "resign") {
                        endGame();
                        break;
                    }
                    else {
                        continue;
                    }
                }
                else if ((getTurn() == "black") && (b->hasMoved() == false)) {
                    computerMove(gameboard, w, b);
                }
            }
            gameboard->setSetupDone(false);  
        }
        //if game is computer vs human
        else if (((p1 == "computer1") || (p1 == "computer2") || (p1 == "computer3") || (p1 == "computer4")) && (p2 == "human")) {
            while ((w->kingIsThere() != false) || (b->kingIsThere() != false)) {
                if (cin.eof()) {
                    break;
                }
                if ((getTurn() == "white") && (w->hasMoved() == false)) {
                    computerMove(gameboard, w, b);
                }
                else if ((getTurn() == "black") && (b->hasMoved() == false)) {
                    string wantsMove;
                    cin >> wantsMove;
                    if (wantsMove == "move") {
                        humanMove(gameboard, w, b);
                    }
                    else if (wantsMove == "resign") {
                        endGame();
                        break;
                    }
                    else {
                        continue;
                    }
                }
            }
            gameboard->setSetupDone(false);  
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
                    humanMove(gameboard, w, b);
                }
                else if (wantsMove == "resign") {
                    endGame();
                    break;
                }
                else {
                    continue;
                }
            }
            gameboard->setSetupDone(false);  
        }
    }
}

//creates a personalized setup board
void Game::setupBoard(Board *gameboard) {
    if (grunning == false) {
        gameboard->boardSetup(gameboard);
        isSetup = true;
    }
}

void Game::showPoints() {
    //distributes draws
    int draws = ties / 2;
    white += draws;
    black += draws;
    //converts int to string
    string w = to_string(white);
    string b = to_string(black);
    //prints final results
    cout << "Final Score:" << endl;
    cout << "White 0" << endl;
    cout << "Black 0" << endl;
}

void Game::endGame() {
    if (w->hasMoved() == false) {
        ++black; 
        cout << "Black Wins!" << endl;
    } 
    else {
        ++white;
        cout << "White Wins!" << endl;
    }
    delete w;
    delete b;

    w = nullptr;
    b = nullptr;

    turn = "white";
    grunning = false;
    isSetup = false;
}

bool Game::getIsSetup() {
    return isSetup;
}

//destructor
Game::~Game() {
    //deletes pointers
    if (w != nullptr) {
        delete w;
    }
    if (b != nullptr) {
        delete b;
    }
}
