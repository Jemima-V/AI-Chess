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

        //sets the players turn
        void setTurn(string t);

        //creating a piece 
        //Pieces* createPiece(char piece);

        //converting a square into a position struct
        //Position convert(string square);

        //creates a player
        //Player* create(string player);
        
        //destructor
        ~Game();
};

#endif 
