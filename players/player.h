#ifndef PLAYER_H
#define PLAYER_H
#include <string.h>
//#include <vector.h>
#include "game.h"
#include "board.h"
#include "pieces.h"

using namespace std; 

class Player {
    //player name
    string name; 

    //player score
    //int capturedScore; 

    //player's captures pieces
    //vector <Pieces*> capturedPieces; 

    //if the king is on the board
    bool kingExists; //maybe

    public:
        //constructor 
        Player(string name);

        //gets the player's name
        virtual string getName() = 0; 
        //checks if the king is on the board
        virtual bool kingIsThere() = 0; 
        //checks if the player has moved
        virtual bool hasMoved() = 0;
        //allows the player to make a valid move
        virtual void playerMove(Position s1, Position s2, Board *gameboard, Pieces *p, string turn) = 0; 
        //creates random moves for computer player
        //virtual void randGenerator();
        //sets if the player has moved
        virtual void setMoved(bool checkMoved) = 0;

        //destructor 
        ~Player();
};

#endif 
