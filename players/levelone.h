#ifndef LEVELONE_H
#define LEVELONE_H
#include <string.h>
#include "player.h"
//s#include "computer.h"
#include "pieces.h"
#include "board.h"

class LevelOne : public Player {

    Player *p;

    //player name
    string name;

    //checks if the king exists on the board
    bool kingExists = true;

    //checks if the player has moved yet
    bool moved = false;

    public:
        //constructor 
        LevelOne(string name);

        //gets the player's name
        string getName() override; 
        //checks if the king is on the board
        bool kingIsThere() override; 
        //checks if the player has moved
        bool hasMoved() override;
        //allows the player to make a valid move
        void playerMove(Position s1, Position s2, Board *gameboard, Pieces *p, string turn) override;
        //sets if the player has moved
        void setMoved(bool checkMoved) override;
        //creates a vector of all the pieces on the board for the specific player
        std::vector<Position> posOfPiecesOnBoard(Board* board, string turn) const;
        
        //destructor
        ~LevelOne();
};

#endif 
