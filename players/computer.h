#ifndef COMPUTER_H
#define COMPUTER_H
#include <string.h>
#include "player.h"
#include "board.h"
#include "pieces.h"

using namespace std;

class Computer : public Player {

    Player *p;

    //player name
    string name;

    //checks if the king exists on the board
    bool kingExists = true;

    //checks if the player has moved yet
    bool moved = false;

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
        virtual bool playerMove(Position s1, Position s2, Board *gameboard, Pieces *p) = 0; 

        //destructor
        ~Computer();
};

#endif 
