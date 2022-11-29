#ifndef GAME_H
#define GAME_H
#include <string>
#include "board.h"
#include "player.h"

using namespace std;

class Player;

class Game {
    //the entire gameboard
    Board *gameBoard; 

    //Player 1
    Player *white;

    //Player 2
    Player *black;

    //to track which player's turn it is
    string turn;

    public:
        //constructor 
        Game(Board *gameBoard, Player *white, Player *black, string turn);

        //gets the players turn
        string getTurn(); 
        
        //destructor
        ~Game();
};

#endif 