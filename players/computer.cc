#include <string.h>
#include "player.h"
#include "computer.h"

using namespace std;


//constructor 
Computer::Computer(string name) : Player{name} {}

//destructor
Computer::~Computer() {
    delete p;
}
