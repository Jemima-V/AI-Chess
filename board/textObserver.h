#ifndef __TEXTOBSERVER_H__
#define __TEXTOBSERVER_H__
#include <string>
#include "observer.h"
#include "board.h"

class addText: public Observer{
    Board *subject;
    
    public:
        addText(Board *subject);
        ~addText();
        void notify();
};

#endif
