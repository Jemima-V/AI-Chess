#include <iostream>
#include <string.h>
#include <sstream>
#include "game.h"

using namespace std;

int main() {

    //starts game
    Game g;

    while (true) {
        if (cin.eof()) {
            g.showPoints();
            break; 
        } 
        else {
            string s;
            cin >> s;
            if (s == "game") {
                string player1;
                string player2;
                cin >> player1 >> player2;
                g.startGame(player1, player2); 
            }
            else if (s == "setup") {
                g.setupBoard();
            }
            else {
                continue; //if command is misspelled 
            }
        }
    }
}
