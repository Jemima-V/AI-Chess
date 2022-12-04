#include "subject.h"
#include "observer.h"

void Subject::attach(Observer *o) {
  observers.emplace_back(o);
}

void Subject::detach(Observer *o) {
  for (auto it = observers.begin(); it != observers.end(); ++it) {
    if (*it == o) {
      observers.erase(it);
      break;
    }
  }
}

void Subject::notifyObservers() {
  for (auto ob : observers) ob->notify();
}

void Subject::notifyMove(int x1, int x2, int y1, int y2){
  for (auto ob : observers){
    if(ob->getType() == 2){
      ob->GCMove(x1, x2, y1, y2);
    } else {
      ob->notify();
    }
  } 
}


