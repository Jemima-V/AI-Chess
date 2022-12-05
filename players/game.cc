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



//destructor
Game::~Game() {
    delete gameBoard;
    delete white;
    delete black;
}
