#ifndef LEVELTWO_H
#define LEVELTWO_H
#include <string.h>
#include "player.h"
#include "computer.h"
#include "pieces.h"
#include "board.h"

class LevelTwo : public Computer {
    //checks if the player has moved yet
    bool moved;

    public:
        //constructor 
        LevelTwo(string name);

        //gets the player's name
        string getName() override; 
        //checks if the king is on the board
        bool kingIsThere() override; 
        //checks if the player has moved
        bool hasMoved() override;
        //allows the player to make a valid move
        void playerMove(Position s1, Position s2, Board *gameboard, Pieces *p) override;

        //destructor
        ~LevelTwo();
};

#endif 
