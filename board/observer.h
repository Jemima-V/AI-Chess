#ifndef _OBSERVER_H_
#define _OBSERVER_H_
class Subject;

class Observer {
 public:
  virtual void notify() = 0;
  virtual int getType() = 0;
  virtual void GCMove(int x1, int x2, int y1, int y2)=0;
  virtual ~Observer() = default;
};
#endif
