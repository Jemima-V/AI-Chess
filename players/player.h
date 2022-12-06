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

    //if the king is on the board
    bool kingExists; 

    //checks if player has moved
    bool moved;

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
        //sets if the player has moved
        virtual void setMoved(bool checkMoved) = 0;

        virtual bool getInStalemate() = 0;

        //destructor 
        virtual ~Player() = 0;
};

#endif 
