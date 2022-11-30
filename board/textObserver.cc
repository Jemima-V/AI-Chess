#include <iostream>
#include <string>
#include "observer.h"
#include "board.h"
#include "textObserver.h"

using namespace std;

addText::addText(Board *s): subject{s}{
  subject->attach(this);
}

addText::~addText() {
  subject->detach(this);
}

void addText::notify() {
  int row = 8;
  cout << endl;

  for (int i = 7; i >= 0; --i) {
    cout << row << ' ';
    row--;

    for (int j = 0; j <= 7; ++j) {
      char letter = subject->getState(j,i);
      //cout << "Check: "<< letter << endl;

      //null pointer at the location
      if(letter == 'X'){

        //white square => both coordinates are either even OR odd
        if( (i%2 == 0 && j%2 ==0) || (i%2 == 1 && j%2 == 1) ){
          cout << ' ';

        //black square => one coordinate is even, one coordinate is odd
        } else {
          cout << '_';
        }

      //there is a piece at the location
      } else {
        cout << letter;
      }
    }
    cout << '\n';
  }

  cout << "\n  abcdefgh\n" << endl;

}
