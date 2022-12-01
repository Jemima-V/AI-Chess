#include "board.h"
#include "player.h"
#include "game.h"

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
