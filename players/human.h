#ifndef HUMAN_H
#define HUMAN_H
#include <string.h>
#include "player.h"

using namespace std;

class Human : public Player {

    Player *p;

    //player name
    string name;

    //checks if the king exists on the board
    bool kingExists;

    //checks if the player has moved yet
    bool moved;

    public:
        //constructor 
        Human(Player *p);

        //gets the player's name
        string getName() override; 
        //checks if the king is on the board
        bool kingIsThere() override; 
        //checks if the player has moved
        bool hasMoved() override;

        //destructor
        ~Human();
};

#endif 
