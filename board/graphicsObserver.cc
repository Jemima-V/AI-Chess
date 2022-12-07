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

int addGraphics::getType(){
  return 2;
}

void addGraphics::GCMove(int file1, int rank1, int file2, int rank2){
  int dim = 60;
  int color;
  string pieceName;
  
  //draw rectangle over old and new positions
  
  //black square => both coordinates are either even OR odd
  if( (file1%2 == 0 && rank1%2 == 0) || (file1%2 == 1 && rank1%2 == 1) ){
    color = 9;

  //white square => one coordinate is even, one coordinate is odd
  } else {
    color = 0;
  }

  int x = 7-rank1;

  window->fillRectangle((dim*file1)+(2*dim)+5, (dim*x)+(2*dim)+5, dim-10, dim-10, color);

  //black square
  if( (file2%2 == 0 && rank2%2 ==0) || (file2%2 == 1 && rank2%2 == 1) ){
    color = 9;

  //white square
  } else {
    color = 0;
  }

  x = 7 - rank2;

  window->fillRectangle((dim*file2)+(2*dim)+5, (dim*x)+(2*dim)+5, dim-10, dim-10, color);
  
  char letter = subject->getState(file2,rank2);
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

  int adjustY =  7 - rank2;

  window->drawString((dim*file2)+(2*dim+(dim/5)), (dim*adjustY)+(2*dim+(dim/2)), pieceName);


}

//render the graphic
void addGraphics::notify() {
int color;
int row = 8;
int dim = 60;
int y; 
string pieceName;

window->drawString((dim*6)-(dim/2), dim - (dim/2), "MKJ CHESSERS");

  
  //print a blank board
  for (int i = 0; i <= 7; ++i) {
  
    window->drawString(dim+(dim/2), (dim*(i))+(dim*2+(dim/2)), to_string(row));
    row--;

    for (int j = 0; j <= 7; ++j) {
      //white square => both coordinates are either even OR odd
      if( (i%2 == 0 && j%2 ==0) || (i%2 == 1 && j%2 == 1) ){
        color = 0;

      //black square => one coordinate is even, one coordinate is odd
      } else {
        color = 9;
      }

      window->fillRectangle((dim*j)+(2*dim), (dim*i)+(2*dim), dim, dim, color);
    }    
  }


  //Print Pieces onto the board
  for (int i = 7; i >= 0; --i) {


    for (int j = 0; j <= 7; ++j) {
      char letter = subject->getState(j,i);


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
      
  
      //flip y-axis values for Xwindows Draw string
      y =  7 - i;

      window->drawString((dim*j)+(2*dim+(dim/5)), (dim*y)+(2*dim+(dim/2)), pieceName);
      //window->drawString((dim*j)+(2*dim+(dim/5))+(1/2), (dim*y)+(2*dim+(dim/2)), pieceName);

    }    
  }

  int x = 0;
  for (char i = 'A'; i <= 'H'; i++){
    string s(1, i);
    window->drawString((dim*x)+(dim*2+(dim/2)), dim*11-(dim/2), s);
    x++;
  }


  //draw frames into the board
  for(int i = 2; i < 11; i++){
    window->drawLine(2*dim, i*dim, 10*dim , i*dim);
    window->drawLine(2*dim, i*dim-1, 10*dim , i*dim-1);
  }

  for(int i = 2; i < 11; i++){
    window->drawLine(i*dim, 2*dim, i*dim , 10*dim);
    window->drawLine(i*dim-1, 2*dim, i*dim-1 , 10*dim);
  }

  window->drawLine(1*dim, 1*dim, 11*dim , 1*dim);
  window->drawLine(1*dim, 1*dim-1, 11*dim , 1*dim-1);

  window->drawLine(1*dim, 11*dim, 11*dim , 11*dim);
  window->drawLine(1*dim, 11*dim-1, 11*dim , 11*dim-1);

  window->drawLine(1*dim, 1*dim, 1*dim , 11*dim);
  window->drawLine(1*dim-1, 1*dim, 1*dim-1, 11*dim);

  window->drawLine(11*dim, 1*dim, 11*dim , 11*dim);
  window->drawLine(11*dim-1, 1*dim, 11*dim-1 , 11*dim);
  
}
