#include "bishop.h"

// ctor
Bishop::Bishop(int owner, bool captured, char id): Pieces(owner, captured, id) {}

// dtor
Bishop::~Bishop() {}

bool Bishop::validMove(Position start, Position end, Board* board) const {
    // a move is only diagonal if the ABSOLUTE change in rank is equal to the ABSOLUTE change in file
    int rankChange = end.rank - start.rank;
    int fileChange = end.file - start.file;
    // covert rankChange to ABS
    int ABSrankChange = convertToABS(rankChange);
    // convert fileChange to ABS
    int ABSfileChange = convertToABS(fileChange);
    // compare both ABSrankChange and ABSfileChange
    if (ABSrankChange == ABSfileChange) {
        return true;
    } else {
        return false;
    }
}
