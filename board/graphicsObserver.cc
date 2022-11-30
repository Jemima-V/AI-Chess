#include <iostream>
#include <string>
#include "observer.h"
#include "board.h"
#include "graphicsObserver.h"
#include "subject.h"

using namespace std;

addGraphics::addGraphics(Board *s): subject{s}{
  subject->attach(this);
  int files = 8;
  int ranks = 8;
  window = new Xwindow{10*files, 10*ranks};
}

addGraphics::~addGraphics() {
  subject->detach(this);
  delete window;
}

//render the graphic
void addGraphics::notify() {
int color;
int dimen = 8;
  
  //buffer line above board
  color = 0;
  for(int i = 0; i <=7; i++){
    window->fillRectangle(10*dimen, 10*dimen, 10, 10, color);
  }

  for (int i = 7; i >= 0; --i) {
    //cout << row << ' ';
    //row--;

    for (int j = 0; j <= 7; ++j) {
      char letter = subject->getState(j,i);
      //cout << "Check: "<< letter << endl;

      //null pointer at the location
      /*if(letter == 'X'){*/

        //white square => both coordinates are either even OR odd
        if( (i%2 == 0 && j%2 ==0) || (i%2 == 1 && j%2 == 1) ){
          color = 1;

        //black square => one coordinate is even, one coordinate is odd
        } else {
          color = 0;
        }

      //there is a piece at the location
      /*} else {
        
      }*/
      window->fillRectangle(10*dimen, 10*dimen, 10, 10, color);
    }
    
  }

  //buffer line below board
  color = 0;
  for(int i = 0; i <=7; i++){
    window->fillRectangle(10*dimen, 10*dimen, 10, 10, color);
  }

  string files = "  abcdefgh";
  window->drawString(10*dimen, 10*dimen, files);
  //cout << "\n  abcdefgh\n" << endl;
}

