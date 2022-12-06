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
    //the entire gameboard
    Board *gameboard = new Board(); 

    //white wins
    int white = 0;

    //black wins
    int black = 0;

    //ties
    int ties = 0;

    //Player 1
    Player *w = nullptr;

    //Player 2
    Player *b = nullptr;

    //to track which player's turn it is
    string turn = "white";

    //stack for storing observers
    std::vector<Observer*> stack;

    //sets up text observer
    Observer *t = new addText{gameboard};
    //sets up graphics observer
    Observer *gr = new addGraphics{gameboard};

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
        void startGame(string player1, string player2);

        //creates a personalized setup board
        void setupBoard();

        //ends a running game
        void endGame();

        //shows total score
        void showPoints();

        //converts user move inputs into positions
        Position convert(string square);

        //creates a player
        Player* create(string player);
        
        //destructor
        ~Game();
};

#endif 
