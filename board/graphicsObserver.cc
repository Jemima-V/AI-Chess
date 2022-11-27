#include <iostream>
#include <string>
#include "observer.h"
#include "board.h"
#include "graphicsObserver.h"
#include "subject.h"

using namespace std;

addGraphics::addGraphics(Board *s, int top, int bottom, int left, int right): subject{s}, top{top}, bottom{bottom}, left{left}, right{right}{
  subject->attach(this);
  //int rows = bottom-top + 1;
  //int cols = right-left + 1;
  //window = new Xwindow{10*cols, 10*rows};
}

addGraphics::~addGraphics() {
  subject->detach(this);
  //delete window;
}

//render the graphic
void addGraphics::notify() {

}

