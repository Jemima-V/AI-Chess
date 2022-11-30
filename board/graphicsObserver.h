#ifndef __GRAPHICSOBSERVER_H__
#define __GRAPHICSOBSERVER_H__
#include <string>
#include "observer.h"
#include "board.h"
#include "window.h"

class addGraphics: public Observer{
    Board *subject;
    Xwindow *window;

    public:
        addGraphics(Board *subject);
        ~addGraphics();
        void notify();
};

#endif
