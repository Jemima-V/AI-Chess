#ifndef __GRAPHICSOBSERVER_H__
#define __GRAPHICSOBSERVER_H__
#include <string>
#include "observer.h"
#include "board.h"
#include "window.h"

class addGraphics: public Observer{
    Board *subject;
    Xwindow *window;
    string type;

    public:
        addGraphics(Board *subject);
        ~addGraphics();
        void notify();
        int getType();
        void GCMove(int x1, int x2, int y1, int y2);
};

#endif
