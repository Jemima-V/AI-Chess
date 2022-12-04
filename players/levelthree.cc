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

//allows the player to make a valid move
void LevelThree::playerMove(Position s1, Position s2, Board *gameboard, Pieces *p, string turn) {
    cout << "before vector startPos" << endl;
    //stores possible starting positions for turn's pieces on curr board
    vector <Position> startPos;
    startPos = posOfPiecesOnBoard(gameboard, turn);
    cout << "after vector startPos" << endl;
    //gets size of vector startPos
    int startPosSize = startPos.size();
    cout << startPosSize << endl;
    bool canCapture = false;
    for (int i = 0; i < startPosSize; ++i) {
        s1 = startPos[i];
        cout << "after s1" << endl;
        //gets piece at start
        p = gameboard->pieceAt(s1);
        cout << p->getId() << endl;
        //stores possible ending positions for the random start position
        vector <Position> endPos;
        cout << "before moveGen" << endl;
        endPos = p->moveGenerator(s1, gameboard);
        cout << "after endPos" << endl;
        //gets size of vector endPos
        int endPosSize = endPos.size();
        cout << endPosSize << endl;
        if (endPosSize != 0) {
            for (int j = 0; j < endPosSize; ++j) {
                s2 = endPos[j];
                Pieces *capturePiece = gameboard->pieceAt(s2);
                if (capturePiece != nullptr) {
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
                    cout << s1.file << endl;
                    cout << s1.rank << endl;
                    cout << s2.file << endl;
                    cout << s2.rank << endl;
                    gameboard->makeMove(p, s1, s2); 
                    moved = true;
                    canCapture = true;
                    gameboard->render();
                    break;
                }
            }
        }
        else {
            continue;
        }
        if (moved == true) {
            break;
        }
    }
    if (canCapture == false) {
        while (moved != true) {
            cout << "in while" << endl;
            //creates a random index from the possible starting position
            int ranPiece = std::rand() % (startPosSize - 0 + 1) + 0; //int randNum = rand()%(max-min + 1) + min;
            cout << ranPiece << endl;
            //gets the random starting position
            s1 = startPos[ranPiece];
            cout << "after s1" << endl;
            //gets piece at start
            p = gameboard->pieceAt(s1);
            cout << p->getId() << endl;
            //stores possible ending positions for the random start position
            vector <Position> endPos;
            cout << "before moveGen" << endl;
            endPos = p->moveGenerator(s1, gameboard);
            cout << "after endPos" << endl;
            //gets size of vector endPos
            int endPosSize = endPos.size();
            cout << endPosSize << endl;
            if (endPosSize != 0) {
                //creates a random index from the possible ending position
                --endPosSize;
                int ranEndPos = std::rand() % (endPosSize - 0 + 1) + 0; //int randNum = rand()%(max-min + 1) + min;
                //gets the random starting position
                cout << ranEndPos << endl;
                s2 = endPos[ranEndPos];
                cout << "after s2" << endl;
                cout << s2.file << endl;
                cout << s2.rank << endl;
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
                cout << s1.file << endl;
                cout << s1.rank << endl;
                cout << s2.file << endl;
                cout << s2.rank << endl;
                gameboard->makeMove(p, s1, s2); 
                moved = true;
                gameboard->render();
            }
            else {
                continue;
            }
        }
    }
}

void LevelThree::setMoved(bool checkMoved) {
    moved = checkMoved;
}

//destructor
LevelThree::~LevelThree() {
    delete p;
}
