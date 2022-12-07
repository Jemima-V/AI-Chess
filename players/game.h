#ifndef GAME_H
#define GAME_H
#include <string>
#include "board.h"
#include "player.h"
#include "textObserver.h"
#include "graphicsObserver.h"

using namespace std;

class Player;

class Game {

    //white wins
    double white = 0;

    //black wins
    double black = 0;

    //Player 1
    Player *w = nullptr;

    //Player 2
    Player *b = nullptr;

    //to track which player's turn it is
    string turn = "white";

    //checks if the game is running
    bool grunning = false;

    //checks if there is a personlized setup
    bool isSetup = false;

    public:
        //constructor 
        Game();

        //gets the players turn
        string getTurn(); 

        //sets the players turn
        void setTurn(string t);

        //creates a human move
        void humanMove(Board *gameboard, Player *w, Player *b);

        //creates a computer move
        void computerMove(Board *gameboard, Player *w, Player *b);

        //starts a game
        void startGame(string player1, string player2, Board *gameboard);

        //creates a personalized setup board
        void setupBoard(Board *gameboard);

        //ends a running game
        void endGame();

        //shows total score
        void showPoints();

        //converts user move inputs into positions
        Position convert(string square);

        //creates a player
        Player* create(string player);

        bool getIsSetup();
        
        //destructor
        ~Game();
};

#endif 
