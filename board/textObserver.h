#ifndef __TEXTOBSERVER_H__
#define __TEXTOBSERVER_H__
#include <string>
#include "observer.h"
#include "board.h"

using namespace std;

class addText: public Observer{
    Board *subject;
    
    public:
        addText(Board *subject);
        ~addText();
        void notify();
        int getType();
        void GCMove(int x1, int x2, int y1, int y2);
};

#endif
