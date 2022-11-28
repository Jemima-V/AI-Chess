#ifndef COMPUTER_H
#define COMPUTER_H
#include <string.h>
#include "player.h"

using namespace std;

class Computer : public Player {
    //checks if the player has moved yet
    bool moved;

    public:
        //constructor 
        Computer(string name);

        //gets the player's name
        virtual string getName() = 0; 
        //checks if the king is on the board
        virtual bool kingIsThere() = 0; 
        //checks if the player has moved
        virtual bool hasMoved() = 0;
        //allows the player to make a valid move
        virtual void makeMove() = 0; 
        //gets the score of the player
        virtual int score() = 0;
        //captures opponent's piece
        virtual void capture(Piece *p) = 0; 
        //moves to a valid square on the board
        virtual Square moveTo() = 0;
        //reverses a player's move
        virtual void reverseMove() = 0;

        //destructor
        ~Computer();
};

#endif 
