#include <string.h>
#include <iostream>
#include "player.h"
#include "levelthree.h"

using namespace std;

//constructor 
LevelThree::LevelThree(string name) : Player{name}, name{name} {}

//gets the player's name
string LevelThree::getName() {
    return name;
}

//checks if the king is on the board
bool LevelThree::kingIsThere() {
    return kingExists;
} 

//checks if the player has moved
bool LevelThree::hasMoved() {
    return moved;
}

//creates a vector of all the pieces on the board for the specific player
std::vector<Position> LevelThree::posOfPiecesOnBoard(Board* board, string turn) const {
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

void LevelThree::playerMakeMove(Position s1, Position s2, Board *gameboard, Pieces *p, string turn) {
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
    gameboard->makeMove(p, s1, s2); 
    moved = true;
    gameboard->renderMove(s1.rank, s1.file, s2.rank, s2.file);
    if ((p->getId() == 'P') || (p->getId() == 'p')) {
        if (p->getFirstMove() == true) {
            p->setFirstMove(false);
        }
    }
}

bool LevelThree::moveAvoidsCapture(Position s1, Position s2, Board *gameboard, Pieces *p, string turn) {
    Board boardCopy = *gameboard;
    Pieces* newPiece = boardCopy.pieceAt(s1);
    //we moved the piece
    boardCopy.makeMove(newPiece, s1, s2);
    vector <Position> oppStartPos;
    if (turn == "white") {
        oppStartPos = posOfPiecesOnBoard(&boardCopy, "black");
    }
    else if (turn == "black") {
        oppStartPos = posOfPiecesOnBoard(&boardCopy, "white");
    }
    int oppStartPosSize = oppStartPos.size();
    for (int j = 0; j < oppStartPosSize; ++j) {
        Position oppS1 = oppStartPos[j];
        Pieces *opp = boardCopy.pieceAt(oppS1);
        vector <Position> oppEndPos;
        oppEndPos = opp->moveGenerator(oppS1, &boardCopy);
        int oppEndPosSize = oppEndPos.size();
        if (oppEndPosSize != 0) {
            for (int m = 0; m < oppEndPosSize; ++m) {
                if ((s2.file == oppEndPos[m].file) &&
                    (s2.rank == oppEndPos[m].rank)) {
                    return true;
                }
            }
        }
    }
    return false;
}
 
bool LevelThree::moveChecksOpp(Position s1, Position s2, Board *gameboard, Pieces *p, string turn) {
    if (p->opponentKingInCheck(s1, s2, gameboard) == true) {
        playerMakeMove(s1, s2, gameboard, p, turn);
        return true;
    }
    return false;
}

bool LevelThree::moveCanCapture(Position s1, Position s2, Board *gameboard, Pieces *p, string turn) {
    Pieces *capturePiece = gameboard->pieceAt(s2);
    if (capturePiece != nullptr) {
        playerMakeMove(s1, s2, gameboard, p, turn);
        return true;
    }
    return false;
}

void LevelThree::makeRandomMove(vector <Position> startPos, int startPosSize, Position s1, Position s2, Board *gameboard, Pieces *p, string turn) {
    while (moved != true) { 
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
            bool avoidsCapture = moveAvoidsCapture(s1, s2, gameboard, p, turn);
            if (avoidsCapture == false) {
                playerMakeMove(s1, s2, gameboard, p, turn);
            }
        }
        else {
            continue;
        }
    }
}

//allows the player to make a valid move
void LevelThree::playerMove(Position s1, Position s2, Board *gameboard, Pieces *p, string turn) {
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
                bool avoidsCapture = moveAvoidsCapture(s1, s2, gameboard, p, turn);
                bool checksOpp = moveChecksOpp(s1, s2, gameboard, p, turn);
                bool canCapture = moveCanCapture(s1, s2, gameboard, p, turn);
                if (avoidsCapture == false) {
                    if (checksOpp == true) {
                        return;
                    }
                    else if (canCapture == true) {
                        return;
                    }
                }
            }
        }
    }
    makeRandomMove(startPos, startPosSize, s1, s2, gameboard, p, turn);
}

void LevelThree::setMoved(bool checkMoved) {
    moved = checkMoved;
}

//destructor
LevelThree::~LevelThree() {
    delete p;
}
