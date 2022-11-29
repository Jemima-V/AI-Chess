#include "queen.h"
#include "board.h"

// ctor
Queen::Queen(int owner, bool captured, char id): Pieces(owner, captured, id) {}

// dtor
Queen::~Queen() {}

bool Queen::validMove(Position start, Position end, Board* board) const {
    // combination of Rook's and Bishop's rules
    int rankChange = end.rank - start.rank;
    int fileChange = end.file - start.file;
    // covert rankChange to ABS
    int ABSrankChange = convertToABS(rankChange);
    // convert fileChange to ABS
    int ABSfileChange = convertToABS(fileChange);
    // Rook's rules: start and end files must be the same OR start and end ranks must be the same
    if ((start.rank == end.rank) || (start.file == end.file)) {
        return true;
    } else if (ABSrankChange == ABSfileChange) { 
        // Bishop's rules: a move is only diagonal if the ABSOLUTE change in rank is equal to the ABSOLUTE change in file
        return true;
    } else {
        return false;
    }
}
   