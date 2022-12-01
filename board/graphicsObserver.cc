#include <iostream>
#include <string>
#include "observer.h"
#include "board.h"
#include "graphicsObserver.h"
#include "subject.h"

using namespace std;

addGraphics::addGraphics(Board *s): subject{s}{
  subject->attach(this);
  int dim = 60;
  window = new Xwindow{12*dim, 12*dim};
}

addGraphics::~addGraphics() {
  subject->detach(this);
  delete window;
}

//render the graphic
void addGraphics::notify() {
int color;
int row = 8;
int dim = 60;
string pieceName;

  //print a blank board
  for (int i = 0; i <= 7; ++i) {
    //cout << row << ' ';
    window->drawString(dim, (dim*(i))+(dim*2+(dim/2)), to_string(row));
    row--;

    for (int j = 0; j <= 7; ++j) {
      //black square => both coordinates are either even OR odd
      if( (i%2 == 0 && j%2 ==0) || (i%2 == 1 && j%2 == 1) ){
        color = 0;

      //white square => one coordinate is even, one coordinate is odd
      } else {
        color = 2;
      }

      window->fillRectangle((dim*j)+(2*dim), (dim*i)+(2*dim), dim, dim, color);
    }    
  }


  //Print Pieces onto the board
  for (int i = 0; i <= 7; ++i) {


    for (int j = 0; j <= 7; ++j) {
      char letter = subject->getState(j,i);
      //cout << "Check: "<< letter << endl;

      //null pointer at the location
      if(letter == 'X'){
        continue;

      //there is a piece at the location
      } else {

        if(letter == 'r'){
          pieceName = "rook";

        } else if (letter == 'n'){
          pieceName = "knight";

        } else if (letter == 'b'){
          pieceName = "bishop";
          
        } else if (letter == 'q'){
          pieceName = "queen";
          
        } else if (letter == 'k'){
          pieceName = "king";
          
        } else if (letter == 'p'){
          pieceName = "pawn";
          
        } else if (letter == 'R'){
          pieceName = "ROOK";
          
        } else if (letter == 'N'){
          pieceName = "KNIGHT";
          
        } else if (letter == 'B'){
          pieceName = "BISHOP";
          
        } else if (letter == 'Q'){
          pieceName = "QUEEN";
          
        } else if (letter == 'K'){
          pieceName = "KING";
          
        } else { //letter == 'P'
          pieceName = "PAWN";

        }
        
      }
      window->drawString((dim*j)+(2*dim+(dim/5)), (dim*i)+(2*dim+(dim/2)), pieceName);
    }    
  }

  int x = 0;
  for (char i = 'A'; i <= 'H'; i++){
    string s(1, i);
    window->drawString((dim*x)+(dim*2+(dim/2)), dim*11, s);
    x++;
  }
 
  
}

