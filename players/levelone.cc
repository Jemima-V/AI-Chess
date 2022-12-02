#include <string.h>
#include "player.h"
//#include "computer.h"
#include "levelone.h"
#include "textObserver.h"
#include "graphicsObserver.h"
#include "observer.h"

using namespace std; 

//constructor 
LevelOne::LevelOne(string name) : Player{name}, name{name} {}

//gets the player's name
string LevelOne::getName() {
    return name;
}

//checks if the king is on the board
bool LevelOne::kingIsThere() {
    return kingExists;
} 

//checks if the player has moved
bool LevelOne::hasMoved() {
    return moved;
}

//allows the player to make a valid move
void LevelOne::playerMove(Position s1, Position s2, Board *gameboard, Pieces *p, string turn) {
    //vector <Observer*> stack;
    if (p->validMoveFinal(s1, s2, gameboard) == true) {
        if (p->opponentKingInCheck(s1, s2, gameboard) == true) {
            cout << "White is in check." << endl;
            if (p->opponentKingCheckmate(s1, s2, gameboard) == true) {
                kingExists = false;
                cout << "Checkmate! Black wins!" << endl;
            }
        }
        gameboard->makeMove(p, s1, s2); 
        moved = true;
        gameboard->render();
    } 
    else {
        moved = false;
    }
    //delete stack
}

void LevelOne::setMoved(bool checkMoved) {
    moved = checkMoved;
}

//destructor
LevelOne::~LevelOne() {
    delete p;
}
