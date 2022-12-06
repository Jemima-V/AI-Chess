#include <iostream>
#include <string.h>
#include <sstream>
#include "game.h"

using namespace std;

int main() {

    //starts game
    Game g;

    //stack for storing observers
    std::vector<Observer*> stack;

    //the entire gameboard
    Board *gameboard = new Board(); 

    Observer *t;
    Observer *gr;

    while (true) {
        if (cin.eof()) {
            g.showPoints();
            break; 
        } 
        else {
            string s;
            cin >> s;
            if (s == "game") {
                if (g.getIsSetup() == false) {
                    //the entire gameboard
                    delete gameboard;
                    gameboard = new Board(); 

                    //sets up text observer
                    t = new addText{gameboard};
                    //sets up graphics observer
                    gr = new addGraphics{gameboard};

                    //pushes the observers onto the stack
                    stack.push_back(t);
                    stack.push_back(gr);
                }
                string player1;
                string player2;
                cin >> player1 >> player2;
                g.startGame(player1, player2, gameboard); 
            }
            else if (s == "setup") {
                delete gameboard;
                gameboard = new Board(); 

                //sets up text observer
                t = new addText{gameboard};
                //sets up graphics observer
                gr = new addGraphics{gameboard};

                //pushes the observers onto the stack
                stack.push_back(t);
                stack.push_back(gr);

                g.setupBoard(gameboard);
            }
            else {
                //cout << "Invalid input! Please re-enter your command" << endl;
                continue; //if command is misspelled 
            }    
        }
    }

    for (auto &ob : stack) delete ob;
    delete gameboard;
}
