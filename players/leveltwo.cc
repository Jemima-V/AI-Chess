#include <iostream>
#include <string.h>
#include "player.h"
#include "leveltwo.h"

using namespace std;

//constructor 
LevelTwo::LevelTwo(string name) : Player{name}, name{name} {}

//gets the player's name
string LevelTwo::getName() {
    return name;
}

//checks if the king is on the board
bool LevelTwo::kingIsThere() {
    return kingExists;
} 

//checks if the player has moved
bool LevelTwo::hasMoved() {
    return moved;
}

//creates a vector of all the pieces on the board for the specific player
std::vector<Position> LevelTwo::posOfPiecesOnBoard(Board* board, string turn) const {
    std::vector<Position> posOfPieces;
    int playerTurn;
    if (turn == "white") {
        playerTurn = 1;
    } 
    else if (turn == "black") {
        playerTurn = 2;
    }
    //creates a new location for the rook
    for (int i = 0; i <= 7; ++i) {
        for (int j = 0; j <= 7; ++j) {
            //new location that the rook is being moved to 
            Position loc{i, j};
            Pieces *p = board->pieceAt(loc); //could give seg fault?
            if (p != nullptr) {
                if (p->getOwner() == playerTurn) {
                    posOfPieces.push_back(loc);
                }
            }
        }
    }
    return posOfPieces;  
}

void LevelTwo::playerMakeMove(Position s1, Position s2, Board *gameboard, Pieces *p, string turn) {
    if (p->opponentKingInCheck(s1, s2, gameboard) == true) {
        if (turn == "black") {
            cout << "White is in check." << endl;
        }
        else if (turn == "white") {
            cout << "Black is in check." << endl;
        }
        if (p->opponentKingCheckmate(s1, s2, gameboard) == true) {
            kingExists = false;
            if (turn == "black") {
                cout << "Checkmate! Black wins!" << endl;
            }
            else if (turn == "white") {
                cout << "Checkmate! White wins!" << endl;
            }
        }
    }
    if (p->opponentKingStalemate(s1, s2, gameboard) == true) {
        cout << "Stalemate!" << endl;
    }
    gameboard->makeMove(p, s1, s2); 
    moved = true;
    gameboard->renderMove(s1.file, s1.rank, s2.file, s2.rank);
    if ((p->getId() == 'P') || (p->getId() == 'p')) {
        if (p->getFirstMove() == true) {
            p->setFirstMove(false);
        }
    }
}

bool LevelTwo::moveCanCapture(Position s1, Position s2, Board *gameboard, Pieces *p, string turn) {
    Pieces *capturePiece = gameboard->pieceAt(s2);
    if (capturePiece != nullptr) {
        playerMakeMove(s1, s2, gameboard, p, turn);
        return true;
    }
    return false;
}

void LevelTwo::makeRandomMove(vector <Position> startPos, int startPosSize, Position s1, Position s2, Board *gameboard, Pieces *p, string turn) {
    while ((moved != true) && (startPosSize != 0)) { 
        --startPosSize;
        //creates a random index from the possible starting position
        int ranPiece = std::rand() % (startPosSize - 0 + 1) + 0; //int randNum = rand()%(max-min + 1) + min;
        //gets the random starting position
        s1 = startPos[ranPiece];
        //gets piece at start
        p = gameboard->pieceAt(s1);
        //stores possible ending positions for the random start position
        vector <Position> endPos;
        endPos = p->moveGenerator(s1, gameboard);
        //gets size of vector endPos
        int endPosSize = endPos.size();
        if (endPosSize != 0) {
            //creates a random index from the possible ending position
            --endPosSize;
            int ranEndPos = std::rand() % (endPosSize - 0 + 1) + 0; //int randNum = rand()%(max-min + 1) + min;
            //gets the random starting position
            s2 = endPos[ranEndPos];
            playerMakeMove(s1, s2, gameboard, p, turn);
        }
        else {
            continue;
        }
    }
}

//allows the player to make a valid move
void LevelTwo::playerMove(Position s1, Position s2, Board *gameboard, Pieces *p, string turn) {
    //cout << "before vector startPos" << endl;
    //stores possible starting positions for turn's pieces on curr board
    vector <Position> startPos;
    startPos = posOfPiecesOnBoard(gameboard, turn);
    //cout << "after vector startPos" << endl;
    //gets size of vector startPos
    int startPosSize = startPos.size();
    //cout << startPosSize << endl;
    for(int i = 0; i < startPosSize; ++i) {
        s1 = startPos[i];
        p = gameboard->pieceAt(s1);
        vector <Position> endPos;
        endPos = p->moveGenerator(s1, gameboard);
        int endPosSize = endPos.size();
        if (endPosSize != 0) {
            for (int k = 0; k < endPosSize; ++k) {
                s2 = endPos[k];
                bool canCapture = moveCanCapture(s1, s2, gameboard, p, turn);
                if (canCapture == true) {
                    return;
                }
            }
        }
    }
    makeRandomMove(startPos, startPosSize, s1, s2, gameboard, p, turn);
}

void LevelTwo::setMoved(bool checkMoved) {
    moved = checkMoved;
}

//destructor
LevelTwo::~LevelTwo() {}
