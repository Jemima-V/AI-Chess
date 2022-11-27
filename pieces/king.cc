#include "king.h"

// ctor
King::King(int owner, bool gotCaptured): Pieces(owner, gotCaptured) {}

// dtor
King::~King() {}

int convertToABS(int toConvert) {
    if (toConvert < 0) {
        return (-1 * toConvert);
    } else {
        return toConvert;
    }
}

bool King::validMove(Position start, Position end) const {
    // moves the same as the Queen but only one block at a time
    int rankChange = end.rank - start.rank;
    int fileChange = end.file - start.file;
    // covert rankChange to ABS
    int ABSrankChange = convertToABS(rankChange);
    // convert fileChange to ABS
    int ABSfileChange = convertToABS(fileChange);
    if (rankChange != 1 || rankChange != -1 || fileChange != 1 || fileChange != -1) {
        return false;
    } else if ((start.rank == end.rank) || (start.file == end.file)) { 
        // Rook's rules (refer to Rook.cc for implementation specific comments)
        return true;
    } else if (ABSrankChange == ABSfileChange) {
        // Bishop's rules (refer to Bishop.cc for implementation specific comments)
        return true;
    } else {
        return false;
    }
}
