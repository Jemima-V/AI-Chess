#ifndef LEVELFOUR_H
#define LEVELFOUR_H
#include <string.h>
#include "player.h"
#include "pieces.h"
#include "board.h"

class LevelFour : public Player {

    // A struct that stores s1, s2 and value of piece at s2
    struct PotentialCapture {
        Position start;
        Position end;
        int value;
    };

    //player name
    string name;

    //checks if the king exists on the board
    bool kingExists = true;

    //checks if the player has moved yet
    bool moved = false;

    bool inStalemate = false;

    public:
        //constructor 
        LevelFour(string name);

        //gets the player's name
        string getName() override; 
        //checks if the king is on the board
        bool kingIsThere() override; 
        //checks if the player has moved
        bool hasMoved() override;
        //allows the player to make a valid move considering game levels
        void playerMove(Position s1, Position s2, Board *gameboard, Pieces *p, string turn) override;
        //sets if the player has moved
        void setMoved(bool checkMoved) override;
        //creates a vector of all the pieces on the board for the specific player
        std::vector<Position> posOfPiecesOnBoard(Board* board, string turn) const;
        //makes the player's move
        void playerMakeMove(Position s1, Position s2, Board *gameboard, Pieces *p, string turn);
        //helper for playermove to avoid capture for making a move
        bool moveAvoidsCapture(Position s1, Position s2, Board *gameboard, Pieces *p, string turn);
        //helper for playermove to check opponent king when making a move
        bool moveChecksOpp(Position s1, Position s2, Board *gameboard, Pieces *p, string turn);
        //generates a random move
        void makeRandomMove(vector <Position> startPos, int startPosSize, Position s1, Position s2, Board *gameboard, Pieces *p, string turn);

        bool getInStalemate() override;

        void computerPawnPromo(Position s1, Position s2, Board *gameboard, Pieces *p, string turn);
        
        //destructor
        ~LevelFour();
};

#endif 
