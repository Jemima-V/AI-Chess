#ifndef HUMAN_H
#define HUMAN_H
#include <string.h>
#include "player.h"
#include "board.h"
#include "pieces.h"

using namespace std;

class Human : public Player {

    Player *p;

    //player name
    string name;

    //checks if the king exists on the board
    bool kingExists = true;

    //checks if the player has moved yet
    bool moved = false;

    bool inStalemate = false;

    //checks if black has a setup for en passant
    //bool blackSetupEnPassant;

    //checks if white has a setup for en passant
    //bool whiteSetupEnPassant;

    public:
        //constructor 
        Human(string name);

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

        bool getInStalemate() override;

        //checks if black has a setup for en passant
        //bool getBlackSetupEnPassant() const;
        //checks if black has a setup for en passant
        //void setBlackSetupEnPassant(bool newCheck);

        //checks if white has a setup for en passant
        //bool getWhiteSetupEnPassant() const;
        //checks if white has a setup for en passant
        //void setWhiteSetupEnPassant(bool newCheck);

        //destructor
        ~Human();
};

#endif 
