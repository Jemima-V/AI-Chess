#ifndef PLAYER_H
#define PLAYER_H
#include <string.h>
#include <vector.h>
#include "game.h"
#include "pieces.h"

using namespace std; 

class Player : public Game {
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
        virtual void makeMove() = 0; 
        //gets the score of the player
        //virtual int score() = 0;
        //captures opponent's piece
        virtual void capture(Pieces *p) = 0; 
        //moves to a valid position on the board
        virtual Position moveTo() = 0;
        //reverses a player's move
        virtual void reverseMove() = 0;

        //destructor 
        ~Player();
};

#endif 
