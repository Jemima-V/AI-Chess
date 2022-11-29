#include <string.h>
#include "player.h"
#include "human.h"

using namespace std;

//constructor 
Human::Human(string name) : Player(name) {}

//gets the player's name
string Human::getName() {
    return name;
}

//checks if the king is on the board
bool Human::kingIsThere() {
    return kingExists;
} 

//checks if the player has moved
bool Human::hasMoved() {
    return moved;
}

//destructor
Human::~Human() {
    delete p;
}
