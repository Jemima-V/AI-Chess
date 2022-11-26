#ifndef GAME_H
#define GAME_H
#include "board.h"
#include "player.h"

class Game {
    //the entire gameboard
    Board *gameBoard; 

    //to track which player's turn it is
    Player turn;

    //to track the number of wins, loses and ties when several games are played 
    int wins;
    int loses;
    int ties;

    public:
        //constructor 
        Game(Board *gameBoard, Player turn);

        //initializes the gameboard
        void initializeBoard(Board *gameBoard);
        //gets the players turn
        Player getTurn(); 
        //gets final game result 
        int gameResult(int wins, int loses, int ties);
        
        //destructor
        ~Game();
};

#endif 
